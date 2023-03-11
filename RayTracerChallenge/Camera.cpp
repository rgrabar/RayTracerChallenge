#include "Camera.h"
#include <ppl.h>
#include <thread>

using namespace concurrency;

Camera::Camera(int _hSize, int _vSize, double _fieldOfView) : hSize(_hSize), vSize(_vSize), fieldOfView(_fieldOfView) {
	auto halfView = tan(fieldOfView / 2.f);
	auto aspect = hSize / (double)vSize;

	if (aspect >= 1) {
		halfWidth = halfView;
		halfheight = halfView / aspect;
	}
	else {
		halfWidth = halfView * aspect;
		halfheight = halfView;
	}
	pixelSize = halfWidth * 2 / hSize;
}

Ray Camera::rayForPixel(double px, double py) {
	auto xOffset = (px + 0.5) * pixelSize;
	auto yOffset = (py + 0.5) * pixelSize;

	auto worldX = halfWidth - xOffset;
	auto worldY = halfheight - yOffset;

	auto pixel = *(transform.inverse()) * Tuple::point(worldX, worldY, -1);
	auto origin = *(transform.inverse()) * Tuple::point(0, 0, 0);
	auto direction = (pixel - origin).normalize();

	return Ray(origin, direction);
}

void Camera::splitArray(int start, int end, World* world, Canvas* image) {
	for (auto y = start; y < end; ++y) {
		for (auto x = 0; x < hSize; ++x) {

			auto pixelColor = Color(0, 0, 0);
			double u = y, v = x;
			bool isEdge = 0;

			if (aliasingSamples > 4 && aliasEdges) {

				// +-0.5 in canvas space moves the ray to the pixel edges
				double topLeftX = v - 0.5;
				double topLeftY = u - 0.5;

				double topRightX = v + 0.5;
				double topRightY = u + 0.5;

				double bottomLeftX = v - 0.5;
				double bottomLeftY = u + 0.5;

				double bottomRightX = v + 0.5;
				double bottomRightY = u - 0.5;

				auto rayTopLeft = rayForPixel(topLeftX, topLeftY);
				Color topLeft = world->colorAt(rayTopLeft);

				auto rayTopRight = rayForPixel(topRightX, topRightY);
				Color topRight = world->colorAt(rayTopRight);

				auto rayBottomLeft = rayForPixel(bottomLeftX, bottomLeftY);
				Color bottomLeft = world->colorAt(rayBottomLeft);

				auto rayBottomRight = rayForPixel(bottomRightX, bottomRightY);
				Color bottomRight = world->colorAt(rayBottomRight);

				auto rayCenter = rayForPixel(x, y);
				Color center = world->colorAt(rayCenter);

				if (std::abs(topLeft.r - center.r) > aliasingThreshold || std::abs(topLeft.g - center.g) > aliasingThreshold || std::abs(topLeft.b - center.b) > aliasingThreshold) {
					isEdge = 1;
				}

				if (std::abs(topRight.r - center.r) > aliasingThreshold || std::abs(topRight.g - center.g) > aliasingThreshold || std::abs(topRight.b - center.b) > aliasingThreshold) {
					isEdge = 1;
				}

				if (std::abs(bottomLeft.r - center.r) > aliasingThreshold || std::abs(bottomLeft.g - center.g) > aliasingThreshold || std::abs(bottomLeft.b - center.b) > aliasingThreshold) {
					isEdge = 1;
				}

				if (std::abs(bottomRight.r - center.r) > aliasingThreshold || std::abs(bottomRight.g - center.g) > aliasingThreshold || std::abs(bottomRight.b - center.b) > aliasingThreshold) {
					isEdge = 1;
				}

				if (isEdge) {
					for (int k = 0; k < aliasingSamples; ++k) {

						u = (y + random_double());
						v = (x + random_double());

						auto ray = rayForPixel(v, u);
						pixelColor = pixelColor + world->colorAt(ray);
					}
					if (edgeAliasHighlights) {
						image->writePixel(x, y, Color(1, 1, 1));
					}
					else
						image->writePixel(x, y, pixelColor / aliasingSamples);
				}
				else if (edgeAliasHighlights) {
					auto ray = rayForPixel(v, u);
					pixelColor = pixelColor + world->colorAt(ray);
					image->writePixel(x, y, pixelColor / 2);
				}
				else {
					auto ray = rayForPixel(v, u);
					pixelColor = pixelColor + world->colorAt(ray);
					image->writePixel(x, y, pixelColor);
				}
			}
			else if (aliasingSamples != 0) {
				for (int k = 0; k < aliasingSamples; ++k) {

					u = (y + random_double());
					v = (x + random_double());

					auto ray = rayForPixel(v, u);
					pixelColor = pixelColor + world->colorAt(ray);
				}
				image->writePixel(x, y, pixelColor / aliasingSamples);
			}
			else {
				auto ray = rayForPixel(v, u);
				pixelColor = pixelColor + world->colorAt(ray);
				image->writePixel(x, y, pixelColor);
			}

			pixelCount++;

			if (pixelCount % next == 0) {
				int pos = 70 * pixelCount / ((double)hSize * vSize);
				std::cout << "[";

				for (int i = 0; i < 70; ++i) {

					if (i < pos)
						std::cout << "=";
					else if (i == pos)
						std::cout << ">";
					else
						std::cout << " ";
					//std::cout << pixelCount / ((double)hSize * vSize) << "\n";
				}
				std::cout << "] " << (int)(pixelCount / ((double)hSize * vSize) * 100) << " %\r";
				std::cout.flush();
			}
		}
	}
}

Canvas Camera::render(World& world) {
	Canvas image(hSize, vSize);

	next = hSize * vSize * 0.05;

	float totalSize = (float)(vSize * hSize);
	int increment5 = 0.05 * totalSize; // how many iterations does 5% represent ? 
	int countdown = increment5;   // decrement countdown instead of modulo
	int percent5 = 0;  // number of elements in the progress bar (1 means 5%)

	const unsigned n = std::thread::hardware_concurrency();

	std::cout << "USING : " << n << " THREADS\n";

	unsigned batch_size = vSize / n;
	unsigned batch_remainder = (vSize) % n;

	std::vector<std::thread> threads;
	for (int i = 0; i < n; ++i) {
		int start = i * batch_size;
		threads.push_back(std::thread(&Camera::splitArray, this, start, start + batch_size, &world, &image));
	}

	int start = n * batch_size;
	threads.push_back(std::thread(&Camera::splitArray, this, start, start + batch_remainder, &world, &image));

	for (auto i = 0; i < n + 1; ++i) {
		threads[i].join();
	}

	std::cout << "\nCOMPLETED\n";
	return image;
}

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
	for(auto y = start; y < end; ++y){
		for (auto x = 0; x < hSize; ++x) {
			auto ray = rayForPixel(x, y);
			auto color = world->colorAt(ray);
			image->writePixel(x, y, color);
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

	std::cout << "\n";

	//image.canvasToImage();
	return image;
}
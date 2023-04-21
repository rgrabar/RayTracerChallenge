#include "Camera.h"

#include <algorithm>
#include <random>
#include <thread>

#ifndef FOR_TEST
namespace Raylib {
	#include "raylib.h"
};
#endif //FOR_TEST

int Camera::numOfThreads = std::thread::hardware_concurrency();
bool Camera::noPPM = false;

Camera::Camera(int _hSize, int _vSize, double _fieldOfView) : hSize(_hSize), vSize(_vSize), fieldOfView(_fieldOfView) {
	double halfView;
	if (epsilonEqual(apertureRadius, 0)) {
		halfView = tan(fieldOfView / 2.f);
	}
	else
		halfView = tan(fieldOfView / 2.f) * focalLenght;

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
	//std::cout << pixelSize << "\n";
}

const Tuple Camera::aperturePoint() const {
	//https://stackoverflow.com/questions/5837572/generate-a-random-point-within-a-circle-uniformly/50746409#50746409
	auto r = apertureRadius * sqrt(random_double());
	auto phi = random_double() * 2 * 3.1415926536;
		//std::cout << cos(phi) << "\n";

	auto x = r * cos(phi);
	auto y = r * sin(phi);

	//std::cout << x << " " << y << "\n";

	return Tuple::point(x, y, 0);
}

Ray Camera::rayForPixel(double px, double py) {
	auto xOffset = (px + 0.5) * pixelSize;
	auto yOffset = (py + 0.5) * pixelSize;

	auto worldX = halfWidth - xOffset;
	auto worldY = halfheight - yOffset;

	if (epsilonEqual(apertureRadius, 0)) {
	
		auto pixel = *(transform.inverse()) * Tuple::point(worldX, worldY, -1);
		auto origin = *(transform.inverse()) * Tuple::point(0, 0, 0);
		auto direction = (pixel - origin).normalize();

		return Ray(origin, direction);
	}	
	else {
		auto pixel = *(transform.inverse()) * Tuple::point(worldX, worldY, -focalLenght);
		auto origin = *(transform.inverse()) * aperturePoint(); 
		auto direction = (pixel - origin).normalize();

		return Ray(origin, direction);
	}
}

void Camera::splitArray(World* world, Canvas* image) {	
	//for (auto y = start; y < end; ++y) {
	//	for (auto x = 0; x < hSize; ++x) {
	int curIndex = 0;
	while (shuffleIndex < (int)shufflePoints.size()) {

		curIndex = shuffleIndex++;
		
		//m.unlock();

		int x = shufflePoints[curIndex].first;
		int y = shufflePoints[curIndex].second;

		auto pixelColor = Color(0, 0, 0);
		double u = y, v = x;
		bool isEdge = 0;

		if (aliasingSamples > 4 && (aliasEdges || edgeAliasHighlights)) {

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

					u = (y + random_double() - 0.5);
					v = (x + random_double() - 0.5);

					auto ray = rayForPixel(v, u);
					pixelColor += world->colorAt(ray);
				}
				if (edgeAliasHighlights) {
					image->writePixel(x, y, Color(1, 1, 1));
				}
				else
					image->writePixel(x, y, pixelColor / aliasingSamples);
			}
			else if (edgeAliasHighlights) {
				auto ray = rayForPixel(v, u);
				pixelColor += world->colorAt(ray);
				image->writePixel(x, y, pixelColor / 2);
			}
			else {
				auto ray = rayForPixel(v, u);
				pixelColor += world->colorAt(ray);
				image->writePixel(x, y, pixelColor);
			}
		}
		else if (aliasingSamples != 0) {
			for (int k = 0; k < aliasingSamples; ++k) {

				u = (y + random_double() - 0.5);
				v = (x + random_double() - 0.5);

				auto ray = rayForPixel(v, u);
				pixelColor += world->colorAt(ray);
			}
			image->writePixel(x, y, pixelColor / aliasingSamples);
		}
		else {
			for (int i = 0; i < 8; ++i) {
				auto ray = rayForPixel(v, u);
				pixelColor += world->colorAt(ray);
			}
			image->writePixel(x, y, pixelColor / 8);
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
	//	}
	//}
}

#ifndef FOR_TEST

void Camera::drawRayImage(Canvas* image) {

	Raylib::InitWindow(image->w, image->h, "Ray tracer");
	Raylib::SetTargetFPS(30);
	Raylib::SetTraceLogLevel(4);

		//Raylib::DrawText("Congrats! You created your first window!", 190, 200, 20, Raylib::Color(100, 100, 100, 255));
	while (!Raylib::WindowShouldClose())
	{
		//Raylib::ClearBackground(Raylib::Color(255, 255, 255, 255));
		Raylib::BeginDrawing();
		//x, y, Raylib::Color(image->scaleColor(pixelColor.r), image->scaleColor(pixelColor.g), image->scaleColor(pixelColor.b), 255)
		auto rayTexture = Raylib::LoadTextureFromImage(image->rayImage);
		Raylib::DrawTexture(rayTexture, 0, 0, Raylib::Color{ 255, 255, 255, 255 });
		Raylib::EndDrawing();
		Raylib::UnloadTexture(rayTexture);
	}
	Raylib::CloseWindow();

}

#endif //FOR_TEST

using namespace std::chrono_literals;

//TODO: this is ugly
#ifndef FOR_TEST
void Camera::render(World& world) {
#else
Canvas Camera::render(World& world) {
#endif

	Canvas image(hSize, vSize);

	for (auto y = 0; y < vSize; ++y) {
		for (auto x = 0; x < hSize; ++x) {
			shufflePoints.emplace_back(x, y);
		}
	}

	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(shufflePoints), std::end(shufflePoints), rng);

	next = hSize * vSize * 0.05;
	// transfrom before any calculations to avoid thread racing in matrix inverse
	transform.inverse();

	// TODO: this is dumb but is done for the same reason as above
	for (auto object : world.objects) {
		object->transform.inverse();
	}

	std::cout << "USING : " << numOfThreads << " THREADS\n";

#ifndef FOR_TEST
	std::thread rayThread(&Camera::drawRayImage, this, &image);

	while (!Raylib::IsWindowReady()) {
		// wait for window
	}
#endif //FOR_TEST

	std::vector<std::thread> threads;
	for (int i = 0; i < (int)numOfThreads; ++i) {
#ifndef FOR_TEST
		// give a bit of time for each tread to start otherwise some pixels get skipped
		Raylib::WaitTime(0.001);
#endif //FOR_TEST
		threads.push_back(std::thread(&Camera::splitArray, this, &world, &image));
	}

#ifndef FOR_TEST
	rayThread.join();
#endif //FOR_TEST

	for (auto& thread:threads) {
		thread.join();
	}


	std::cout << "\nCOMPLETED\n";
	if (noPPM == false) {
		std::cout << "SAVING TO PPM \n";
		image.canvasToImage();
	}
#ifdef FOR_TEST
	return image;
#endif
}

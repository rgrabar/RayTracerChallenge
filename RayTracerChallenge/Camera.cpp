#include "Camera.h"
#include <ppl.h>

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

	auto pixel = transform.inverse() * Tuple::point(worldX, worldY, -1);
	auto origin = transform.inverse() * Tuple::point(0, 0, 0);
	auto direction = (pixel - origin).normalize();

	return Ray(origin, direction);
}

// TODO: maybe replace with something 
// https://stackoverflow.com/questions/36246300/parallel-loops-in-c

Canvas Camera::render(const World& world) {
	Canvas image(hSize, vSize);

	float totalSize = (float)(vSize * hSize);
	int increment5 = 0.05 * totalSize; // how many iterations does 5% represent ? 
	int countdown = increment5;   // decrement countdown instead of modulo
	int percent5 = 0;  // number of elements in the progress bar (1 means 5%)

	parallel_for(0, vSize, [&](size_t y) {
		for (auto x = 0; x < hSize; ++x) {
			auto ray = rayForPixel(x, y);
			auto color = world.colorAt(ray);
			image.writePixel(x, y, color);

			if (--countdown == 0) {
				percent5++;
				std::cout << "\r" << std::string(percent5, '|') << percent5 * 5 << "%";
				countdown = increment5;
				std::cout.flush();
			}
		}
	});
	std::cout << "\n";

	//image.canvasToImage();
	return image;
}
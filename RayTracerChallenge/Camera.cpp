#include "Camera.h"

Camera::Camera(int _hSize, int _vSize, float _fieldOfView) : hSize(_hSize), vSize(_vSize), fieldOfView(_fieldOfView) {
	auto halfView = tan(fieldOfView / 2.f);
	auto aspect = hSize / (float)vSize;

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

Ray Camera::rayForPixel(float px, float py) {
	auto xOffset = (px + 0.5) * pixelSize;
	auto yOffset = (py + 0.5) * pixelSize;

	auto worldX = halfWidth - xOffset;
	auto worldY = halfheight - yOffset;

	auto pixel = transform.inverse() * Tuple::point(worldX, worldY, -1);
	auto origin = transform.inverse() * Tuple::point(0, 0, 0);
	auto direction = (pixel - origin).normalize();

	return Ray(origin, direction);
}

Canvas Camera::render(const World& world) {
	Canvas image(hSize, vSize);
	
	for (auto y = 0; y < vSize; ++y) {
		for (auto x = 0; x < hSize; ++x) {
			auto ray = rayForPixel(x, y);
			auto color = world.colorAt(ray);
			image.writePixel(x, y, color);
		}
	}
	//image.canvasToImage();
	return image;
}
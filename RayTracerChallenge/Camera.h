#pragma once
#include <iostream>

#include "World.h"
#include "Canvas.h"
#include "Color.h"
#include "Matrix.h"
#include "Ray.h"

class Camera {
public:
	int hSize;
	int vSize;
	float fieldOfView;
	float halfWidth;
	float halfheight;
	float pixelSize;

	// TODO: use this as default?
	Matrix transform = identityMatrix(4);

	Camera(int _hSize, int _vSize, float _fieldOfView);
	Ray rayForPixel(float px, float py);

	Canvas render(const World& world);
};
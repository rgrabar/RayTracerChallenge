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
	double fieldOfView;
	double halfWidth;
	double halfheight;
	double pixelSize;

	// TODO: use this as default?
	Matrix transform = identityMatrix(4);

	Camera(int _hSize, int _vSize, double _fieldOfView);
	Ray rayForPixel(double px, double py);

	Canvas render(const World& world);
};
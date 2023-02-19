#pragma once
#include <iostream>
#include <mutex>
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
	std::mutex mutex_;

	int aliasingSamples = 0;
	double aliasingThreshold = 0.3;
	bool aliasEdges = 0;


	std::atomic_int pixelCount = 0;
	std::atomic_int next = 5;

	// TODO: use this as default?
	Matrix transform = identityMatrix(4);

	Camera(int _hSize, int _vSize, double _fieldOfView);
	Ray rayForPixel(double px, double py);

	Canvas render(World& world);

	void splitArray(int start, int end, World* world, Canvas* image);
};
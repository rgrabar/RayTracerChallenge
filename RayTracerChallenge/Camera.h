#pragma once
#include "Canvas.h"
#include "Ray.h"
#include "World.h"

#include <atomic>
#include <mutex>

struct Camera {
	int hSize;
	int vSize;
	double fieldOfView;
	double halfWidth;
	double halfheight;
	double pixelSize;

	int aliasingSamples = 0;
	double aliasingThreshold = 0.3;
	bool aliasEdges = 0;
	bool edgeAliasHighlights = 0;

	std::atomic_int pixelCount = 0;
	std::atomic_int next = 5;

	static int numOfThreads;
	static bool noPPM;

	// TODO: use this as default?
	Matrix transform = identityMatrix(4);

	Camera(int _hSize, int _vSize, double _fieldOfView);
	Ray rayForPixel(double px, double py);

#ifndef FOR_TEST
	void render(World& world);
#else
	Canvas render(World& world);
#endif


	void splitArray(World* world, Canvas* image);

#ifndef FOR_TEST
	void drawRayImage(Canvas* image);
#endif //FOR_TEST

	std::vector<std::pair<int, int>> shufflePoints;
	std::atomic_int shuffleIndex = 0;
};
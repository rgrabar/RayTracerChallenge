#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
#include "Tuple.h"
#include "Matrix.h"
#include "Transformations.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Normal.h"
#include "Arena.h"
#include "World.h"
#include "Camera.h"
#include "Plane.h"
#include <cstdio>
#include "StripePattern.h"
#include "GradientPattern.h"
#include "RingPattern.h"
#include "CheckerPattern.h"
#include "BlendedPattern.h"
#include "RadialGradientPattern.h"
#include "NestedPattern.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Groups.h"
#include "scenes/scenes.h"

#include <chrono>
using namespace std::chrono;


int main() {

	auto start = high_resolution_clock::now();

	//drawProjectile();
	//drawClock();
	//drawRedCircle();
	//drawShadowPatternsReflection();
	//drawBadSmiley();
	//drawRefractiveSphere();
	//drawAllShapes();
	drawHexagon();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	std::cout << duration.count() << std::endl;

	std::cout << "SAVING TO PPM \n";

	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);

	std::cout << duration.count() << std::endl;


	std::getchar();
	return 0;
}
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

	

	/*
	
	auto corner = Sphere();
	corner.transform = translate(0, 0, -1) * scale(0.25, 0.25, 0.25);

	auto edge = Cylinder();
	edge.minimum = 0;
	edge.maximum = 1;
	edge.transform = translate(0, 0, -1) * rotationY(-TEST_PI / 6) * rotationZ(-TEST_PI / 2) * scale(0.25, 1, 0.25);


	auto side = Group();
	side.addChild(edge);
	side.addChild(corner);
	side.transform = rotationY(0);


	auto corner1 = Sphere();
	corner1.transform = translate(0, 0, -1) * scale(0.25, 0.25, 0.25);

	auto edge1 = Cylinder();
	edge1.minimum = 0;
	edge1.maximum = 1;
	edge1.transform = translate(0, 0, -1) * rotationY(-TEST_PI / 6) * rotationZ(-TEST_PI / 2) * scale(0.25, 1, 0.25);
	
	auto side1 = Group();
	side1.addChild(edge1);
	side1.addChild(corner1);
	side1.transform = rotationY(TEST_PI / 3);

	auto corner2 = Sphere();
	corner2.transform = translate(0, 0, -1) * scale(0.25, 0.25, 0.25);

	auto edge2 = Cylinder();
	edge2.minimum = 0;
	edge2.maximum = 1;
	edge2.transform = translate(0, 0, -1) * rotationY(-TEST_PI / 6) * rotationZ(-TEST_PI / 2) * scale(0.25, 1, 0.25);

	auto side2 = Group();
	side2.addChild(edge2);
	side2.addChild(corner2);
	side2.transform = rotationY(2 * TEST_PI / 3);


	auto corner3 = Sphere();
	corner3.transform = translate(0, 0, -1) * scale(0.25, 0.25, 0.25);

	auto edge3 = Cylinder();
	edge3.minimum = 0;
	edge3.maximum = 1;
	edge3.transform = translate(0, 0, -1) * rotationY(-TEST_PI / 6) * rotationZ(-TEST_PI / 2) * scale(0.25, 1, 0.25);

	auto side3 = Group();
	side3.addChild(corner3);
	side3.addChild(edge3);
	side3.transform = rotationY(3 * TEST_PI / 3);


	auto corner4 = Sphere();
	corner4.transform = translate(0, 0, -1) * scale(0.25, 0.25, 0.25);

	auto edge4 = Cylinder();
	edge4.minimum = 0;
	edge4.maximum = 1;
	edge4.transform = translate(0, 0, -1) * rotationY(-TEST_PI / 6) * rotationZ(-TEST_PI / 2) * scale(0.25, 1, 0.25);

	auto side4 = Group();
	side4.addChild(corner4);
	side4.addChild(edge4);
	side4.transform = rotationY(4 * TEST_PI / 3);


	auto corner5 = Sphere();
	corner5.transform = translate(0, 0, -1) * scale(0.25, 0.25, 0.25);

	auto edge5 = Cylinder();
	edge5.minimum = 0;
	edge5.maximum = 1;
	edge5.transform = translate(0, 0, -1) * rotationY(-TEST_PI / 6) * rotationZ(-TEST_PI / 2) * scale(0.25, 1, 0.25);

	auto side5 = Group();
	side5.addChild(corner5);
	side5.addChild(edge5);
	side5.transform = rotationY(5 * TEST_PI / 3);


	auto world = World();
	//world.light = Light(Color(1, 1, 1), Tuple::point(-5, 10, -10));
	world.light = Light(Color(1, 1, 1), Tuple::point(4, 5, -4.1));
	world.objects.emplace_back(&side);
	world.objects.emplace_back(&side1);
	world.objects.emplace_back(&side2);
	world.objects.emplace_back(&side3);
	world.objects.emplace_back(&side4);
	world.objects.emplace_back(&side5);


	Camera cam(1920, 1580, TEST_PI / 3);
	cam.transform = viewTransformation(Tuple::point(0, 3.5, -5.5), Tuple::point(0.0, 0.7, 0.0), Tuple::vector(0, 1, 0));
	auto ans = cam.render(world);

	ans.canvasToImage();
	*/

	//drawProjectile();
	//drawClock();
	//drawRedCircle();
	//drawShadowPatternsReflection();
	//drawBadSmiley();
	//drawRefractiveSphere();
	drawAllShapes();


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
#include <chrono>
#include <iostream>
#include "scenes/Scenes.h"

using namespace std::chrono;


int main() {
	
	auto start = high_resolution_clock::now();

	//drawProjectile();
	//drawClock();
	//drawRedCircle();
	//drawShadowPatternsReflection();
	//drawBadSmiley();
	//drawRefractiveSphere();
	drawAllShapes();
	//drawHexagon();
	//sphereCube();
	//sphereCubeDivide();
	//drawTeapot();
	//drawAstronaut();
	//drawDragon();
	//drawCSKnife();
	//CSGScene();
	//areaLightScene();
	//spotLightScene();
	//aliasingScene();
	//testScene();
	//drawAxes();
	
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
#include <chrono>
#include <iostream>
#include "scenes/Scenes.h"
#include <stdio.h>
#include <string.h>
#include <time.h> 

using namespace std::chrono;


int main(int argc, char* argv[]) {
	
	auto start = high_resolution_clock::now();

	srand(time(NULL));
/*
	printf("You have entered %d arguments:\n", argc);

	//scena, image size, aliasing, load random obj

	std::string scene = argv[1];
	int n = argc;
	int aliasing = 16;
	int width = 1920;
	int height = 1080;

	for (int i = 2; i < n; ++i) {
		if (strcmp(argv[i], "-a") == 0) {
			aliasing = atoi(argv[i + 1]);
			i++;
		}else if (strcmp(argv[i], "-s") == 0) {
			width = atoi(argv[i + 1]);
			i++;
			height = atoi(argv[i + 1]);
			i++;
		}
	}

	std::cout << "aliasing: " << aliasing << " width " << width << " height " << height << " scene " << scene << "\n";
	*//*
	if(scene == "Projectile")
		drawProjectile();
	else if(scene == "Clock")
		drawClock();
	else if(scene == "RedCircle")
		drawRedCircle();
	else if(scene == "Shadows")
		drawShadowPatternsReflection();
	else if(scene == "BadSmiley")
		drawBadSmiley();
	else if(scene == "RefractiveSphere")
		drawRefractiveSphere();
	else if(scene == "AllShapes")
		drawAllShapes();
	else if(scene == "Hexagon")
		drawHexagon();
	else if(scene == "Spheres")
		sphereCube();
	else if(scene == "SpheresDivide")
		sphereCubeDivide();
	else if(scene == "CSG")
		CSGScene();
	else if(scene == "AreaLight")
		areaLightScene();
	else if(scene == "SpotLight")
		spotLightScene();
	else if(scene == "Aliasing")
		aliasingScene();
	*/

	//drawProjectile();
	//drawClock();
	//drawRedCircle();
	//drawShadowPatternsReflection();
	//drawBadSmiley();
	//drawRefractiveSphere();
	//drawAllShapes();
	//drawHexagon();
	//sphereCube();
	//sphereCubeDivide();
	CSGScene();
	//areaLightScene();
	//spotLightScene();
	//aliasingScene();
	//drawTeapot();
	//drawAstronaut();
	//drawDragon();
	//drawCSKnife();
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
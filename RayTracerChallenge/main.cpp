#include <chrono>
#include <iostream>
#include <time.h> 
#include <string.h>

#include "scenes/Scenes.h"

using namespace std::chrono;


int main(int argc, char* argv[]) {
	
	auto start = high_resolution_clock::now();

	srand(time(NULL));

	printf("You have entered %d arguments:\n", argc);

	//scena, image size, aliasing, load random obj

	int n = argc;
	std::string scene = "Shadows";
	std::string path = "assets/smoothTriangles.obj";
	
	int width = 900;
	int height = 900;
	
	int aliasing = 0;
	int highlights = 0;
	int edge = 0;
	double threshold = 0.3;

	double focalLenght = 1;
	double apertureRadius = 0;
	int apertureSamples = 1;


	if (n != 1) {
		if (strcmp(argv[1], "--help") == 0) {
			std::cout << "[Scene name] [--option]\n";
			std::cout << "\t--aliasing\t\t [int] number of samples per pixel\n";
			std::cout << "\t--size\t\t\t [int, int] width height\n";
			std::cout << "\t--edge\t\t\t 0/1 if enabled antialiasing will only be applied to edges\n";
			std::cout << "\t--highlights\t\t 0/1, if enabled previews what will be antialiased when using the --edge option\n";
			std::cout << "\t--threshold\t\t float [0, 1], if --edge is enabeld set the threshold for edge detection\n";
			std::cout << "\t\t\t\t it checks for the difference in color beween the center of the pixel and it's edges\n";
			std::cout << "\t--path\t\t\t sets the path to the custom .obj file (can be used only with LoadOBJ scene)\n\n";

			std::cout << "Other options: \n";
			std::cout << "\t --threads [int], number of threads to use\n";
			std::cout << "\t --no-ppm [bool], if true the ppm image of the scene won't be created\n\n";

			std::cout << "Available scenes:\n";
			std::cout << "\tProjectile\n";
			std::cout << "\tClock\n";
			std::cout << "\tRedCircle\n";
			std::cout << "\tShadows\n";
			std::cout << "\tBadSmiley\n";
			std::cout << "\tRefractiveSphere\n";
			std::cout << "\tAllShapes\n";
			std::cout << "\tHexagon\n";
			std::cout << "\tSpheres\n";
			std::cout << "\tSpheresDivide\n";
			std::cout << "\tTeapot\n";
			std::cout << "\tCS\n";
			std::cout << "\tDragon\n";
			std::cout << "\tAstronaut\n";
			std::cout << "\tCSG\n";
			std::cout << "\tAreaLight\n";
			std::cout << "\tSpotLight\n";
			std::cout << "\tAliasing\n";
			std::cout << "\tCubeTest\n";
			std::cout << "\tEarth\n";
			std::cout << "\tLoadOBJ\n";

			std::cout << "E.g. Aliasing --aliasing 16 --size 400 400 --highlights 1 --edge 1 --threshold 0.005";
			return 0;
		}
		scene = argv[1];
	}

	for (int i = 2; i < n; ++i) {
		if (strcmp(argv[i], "--aliasing") == 0) {
			aliasing = atoi(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--size") == 0) {
			width = atoi(argv[i + 1]);
			i++;
			height = atoi(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--highlights") == 0) {
			highlights = atoi(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--edge") == 0) {
			edge = atoi(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--threshold") == 0) {
			threshold = atof(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--path") == 0) {
			path = argv[i + 1];
			i++;
		}
		else if (strcmp(argv[i], "--threads") == 0) {
			Camera::numOfThreads = atoi(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--no-ppm") == 0) {
			Camera::noPPM = atoi(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--focal-length") == 0) {
			focalLenght = atof(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--aperture-radius") == 0) {
			apertureRadius = atof(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--aperture-samples") == 0) {
			apertureSamples = atoi(argv[i + 1]);
			i++;
		}
	}

	std::cout << "Settings: \n";
	std::cout << "scene: " << scene << "\n";
	std::cout << "width: " << width << "\n";
	std::cout << "height: " << height << "\n";
	std::cout << "aliasing samples: " << aliasing << "\n";
	std::cout << "alias edges: " << edge << "\n";
	std::cout << "highlight edges: " << highlights << "\n";
	std::cout << "threshold: " << threshold << "\n";

	if (scene == "Projectile")
		drawProjectile();
	else if (scene == "Clock")
		drawClock();
	else if (scene == "RedCircle")
		drawRedCircle();
	else if (scene == "Shadows")
		drawShadowPatternsReflection(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "BadSmiley")
		drawBadSmiley(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "RefractiveSphere")
		drawRefractiveSphere(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "AllShapes")
		drawAllShapes(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "Hexagon")
		drawHexagon(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "Spheres")
		sphereCube(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "SpheresDivide")
		sphereCubeDivide(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "Teapot")
		drawTeapot(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "CS")
		drawCSKnife(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "Dragon")
		drawDragon(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "Astronaut")
		drawAstronaut(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "CSG")
		CSGScene(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "AreaLight")
		areaLightScene(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "SpotLight")
		spotLightScene(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "Aliasing")
		aliasingScene(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "CubeTest")
		cubeTest(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "Earth")
		earth(aliasing, width, height, highlights, edge, threshold, focalLenght, apertureRadius, apertureSamples);
	else if (scene == "LoadOBJ")
		loadOBJ(path);
	else if (scene == "Test")
		testScene();
	
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	std::cout << duration.count() << std::endl;
	
//	std::getchar();
	
	
	return 0;
}
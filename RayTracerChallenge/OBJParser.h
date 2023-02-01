#pragma once

#include <string>
#include <vector>
#include "Tuple.h"
#include "Triangle.h"

class OBJParser{
public:
	OBJParser(std::string path);
	int skippedLines = 0;
	std::vector<Tuple> vertices;
	std::vector<Triangle*> triangles;
	std::vector<int> faceIndex;
	int currVertice = 0;
};
#pragma once

#include <string>
#include <vector>
#include "Tuple.h"
#include "Triangle.h"
#include "Groups.h"
#include <map>

class OBJParser{
public:
	bool saveToNewGroup = 0;
	std::string name;
	std::map<std::string, Group*> namedGroup;

	OBJParser(std::string path);
	int skippedLines = 0;
	std::vector<Tuple> vertices;
	std::vector<Tuple> normals;
	std::vector<Triangle*> triangles;
	std::vector<SmoothTriangle*> smoothTriangles;
	std::vector<int> faceIndex;
	std::vector<int> normalIndex;
	int currVertice = 0;

	Group* ObjToGroup();


	Group g;
};
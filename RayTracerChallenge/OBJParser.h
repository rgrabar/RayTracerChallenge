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
	char name[100];
	std::map<std::string, Group*> namedGroup;

	OBJParser(std::string path);
	int skippedLines = 0;
	std::vector<Tuple> vertices;
	std::vector<Triangle*> triangles;
	std::vector<int> faceIndex;
	int currVertice = 0;

	Group g;
};
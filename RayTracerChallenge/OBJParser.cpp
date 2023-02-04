#include "OBJParser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>


OBJParser::OBJParser(std::string path) {

	std::ifstream myfile(path);

	std::string line;
	double n1, n2, n3, n4;

	while (std::getline(myfile, line)) {

		if (line[0] == 'v' && line[1] == 'n') {

			sscanf_s(line.c_str(), "%*s %lf %lf %lf", &n1, &n2, &n3);

			normals.push_back(Tuple::vector(n1, n2, n3));
		}

		else if (line[0] == 'v') {
		
			sscanf_s(line.c_str(), "%*s %lf %lf %lf", &n1, &n2, &n3);

			vertices.push_back(Tuple::point(n1, n2, n3));
		}
		else if (line[0] == 'f') {

			int matches = sscanf_s(line.c_str(), "%*s %lf %lf %lf %lf", &n1, &n2, &n3, &n4);

			if(matches == 3) {
				if (!saveToNewGroup) {
					auto tmp = new Triangle(vertices[(int)--n1], vertices[(int)--n2], vertices[(int)--n3]);
					triangles.emplace_back(tmp);
					faceIndex.clear();
					g.addChild(tmp);
				}
				else {
					auto tmp = new Triangle(vertices[(int)--n1], vertices[(int)--n2], vertices[(int)--n3]);
					triangles.emplace_back(tmp);
					faceIndex.clear();
					namedGroup[name]->addChild(tmp);
					saveToNewGroup = 0;
				}
			}
			else {
				std::stringstream ss(line);

				std::string s;
				while (std::getline(ss, s, ' ')) {
					if (s[0] != 'f') {
						int tmp = std::stoi(s) - 1;
						faceIndex.emplace_back(tmp);
					}
				}

				for (int i = 1; i < vertices.size() - 1; ++i) {
					auto tmp = new Triangle(vertices[faceIndex[0]], vertices[faceIndex[i]], vertices[faceIndex[i + 1]]);
					triangles.emplace_back(tmp);
					g.addChild(tmp);
				}
			}
		}
		else if (line[0] == 'g') {

			int spac = line.find(" ", 0);
			name = line.substr(spac + 1);

			namedGroup[name] = new Group();

			saveToNewGroup = 1;
		}

		else
			skippedLines++;
	}
}

Group* OBJParser::ObjToGroup() {
	auto gr = new Group();
	for (auto x : namedGroup) {
		gr->addChild(x.second);
	}

	gr->addChild(&g);

	return gr;
}
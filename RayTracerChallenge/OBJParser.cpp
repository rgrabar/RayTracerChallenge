#include "OBJParser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>


// TODO: FAILS FOR ASTRONAUT OBJ

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

				auto found = line.find("//");
				auto found1 = line.find("/");

				if (found == std::string::npos && found1 == std::string::npos) {

					while (std::getline(ss, s, ' ')) {
						if (s[0] != 'f') {
							int tmp = std::stoi(s) - 1;
							faceIndex.emplace_back(tmp);
						}
					}

					for (int i = 1; i < faceIndex.size() - 1; ++i) {
						auto tmp = new Triangle(vertices[faceIndex[0]], vertices[faceIndex[i]], vertices[faceIndex[i + 1]]);
						triangles.emplace_back(tmp);
						g.addChild(tmp);
					}
					faceIndex.clear();
					continue;
				}
				
				else if (found != std::string::npos) {
					while (std::getline(ss, s, ' ')) {
						if (s[0] != 'f') {
							int a, b;
							sscanf_s(s.c_str(), "%d//%d", &a, &b);
							faceIndex.push_back(--a);
							normalIndex.push_back(--b);
						}
					}
				}
				else {
					while (std::getline(ss, s, ' ')) {
						if (s[0] != 'f' && s[0]>= 48 && s[0] <= 57) {
							int a, b;
							sscanf_s(s.c_str(), "%d/%*d/%d", &a, &b);
							faceIndex.push_back(--a);
							normalIndex.push_back(--b);
						}
					}
				}
				for (int i = 0; i < faceIndex.size() - 2; ++i) {
					// TODO group names
					auto tmp = new SmoothTriangle(vertices[faceIndex[0]], vertices[faceIndex[i + 1]], vertices[faceIndex[i + 2]],
												  normals[normalIndex[0]], normals[normalIndex[i + 1]], normals[normalIndex[i + 2]]);
					smoothTriangles.emplace_back(tmp);
					g.addChild(tmp);
				}
				
				faceIndex.clear();
				normalIndex.clear();
				
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
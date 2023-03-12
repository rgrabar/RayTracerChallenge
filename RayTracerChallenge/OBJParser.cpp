#include "OBJParser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>

#ifdef __linux__
#define sscanf_s sscanf
#endif

OBJParser::OBJParser(std::string path) {

	std::ifstream myfile(path);

	std::string line;
	double n1, n2, n3;
	int f1, f2, f3;

	while (std::getline(myfile, line)) {

		if (line[0] == '#') {
			continue;
		}
		if (line[0] == 'v' && line[1] == 'n') {
			sscanf_s(line.c_str(), "%*s %lf %lf %lf", &n1, &n2, &n3);
			normals.emplace_back(Tuple::vector(n1, n2, n3));
		}

		else if (line[0] == 'v' && line[1] != 't') {
			sscanf_s(line.c_str(), "%*s %lf %lf %lf", &n1, &n2, &n3);
			vertices.emplace_back(Tuple::point(n1, n2, n3));
		}

		else if (line[0] == 'g' || line[0] == 'f') {
			if (!isNormalized) {
				// this assumes that all vertices are defined before any groups and faces
				// normalize vertices from (-1, -1, -1) to (1, 1, 1)
				auto bbox = BoundingBox();

				for (const auto& x : vertices) {
					bbox.addPoint(x);
				}

				auto sx = bbox.boxMax.x - bbox.boxMin.x;
				auto sy = bbox.boxMax.y - bbox.boxMin.y;
				auto sz = bbox.boxMax.z - bbox.boxMin.z;

				auto scale = (double)std::max({ sx, sy, sz }) / (double)2;

				for (Tuple& normalized : vertices) {
					normalized.x = (normalized.x - (bbox.boxMin.x + sx / (double)2)) / scale;
					normalized.y = (normalized.y - (bbox.boxMin.y + sy / (double)2)) / scale;
					normalized.z = (normalized.z - (bbox.boxMin.z + sz / (double)2)) / scale;
				}
				isNormalized = true;
			}

			int f4;
			volatile int matches = sscanf_s(line.c_str(), "%*s %d %d %d %d", &f1, &f2, &f3, &f4);

			auto found = line.find("//");
			auto found1 = line.find("/");

			if (found == std::string::npos && found1 == std::string::npos)
			{

				if (matches == 3) {
					if (line[0] == 'f') {
						auto tmp = new Triangle(vertices[--f1], vertices[--f2], vertices[--f3]);

						if (saveToNewGroup)
							namedGroup[name]->addChild(tmp);
						else
							g.addChild(tmp);
#ifdef DEBUG
						triangles.emplace_back(tmp);
#endif // DEBUG
					}
				}
				else if (matches == 4) {
					std::stringstream ss(line);
					std::string s;
					while (std::getline(ss, s, ' ')) {
						if (s[0] >= '0' && s[0] <= '9') {
							int tmp = std::stoi(s) - 1;
							faceIndexExtended.emplace_back(tmp);
						}
					}
				}
			}

			if (found != std::string::npos) {
				std::stringstream ss(line);
				std::string s;
				while (std::getline(ss, s, ' ')) {
					int a, b;
					int matches = sscanf_s(s.c_str(), "%d//%d", &a, &b);
					if (matches == 2) {
						faceIndex.emplace_back(--a);
						normalIndex.emplace_back(--b);
					}
				}
				auto tmp = new SmoothTriangle(vertices[faceIndex[0]], vertices[faceIndex[1]], vertices[faceIndex[2]],
					normals[normalIndex[0]], normals[normalIndex[1]], normals[normalIndex[2]]);
				if (saveToNewGroup)
					namedGroup[name]->addChild(tmp);
				else
					g.addChild(tmp);
#ifdef DEBUG
				smoothTriangles.emplace_back(tmp);
#endif // DEBUG
				faceIndex.clear();
				normalIndex.clear();
			}

			else if (found1 != std::string::npos) {
				std::stringstream ss(line);
				std::string s;
				while (std::getline(ss, s, ' ')) {
					int a, b;
					int matches = sscanf_s(s.c_str(), "%d/%*d/%d", &a, &b);
					if (matches == 2) {
						faceIndex.emplace_back(--a);
						normalIndex.emplace_back(--b);
					}
				}
				auto tmp = new SmoothTriangle(vertices[faceIndex[0]], vertices[faceIndex[1]], vertices[faceIndex[2]],
					normals[normalIndex[0]], normals[normalIndex[1]], normals[normalIndex[2]]);
#ifdef DEBUG
				smoothTriangles.emplace_back(tmp);
#endif // DEBUG
				if (saveToNewGroup)
					namedGroup[name]->addChild(tmp);
				else
					g.addChild(tmp);
				faceIndex.clear();
				normalIndex.clear();
			}
			else if (line[0] == 'g') {

				int spac = line.find(" ", 0);
				name = line.substr(spac + 1);

				if (namedGroup.find(name) == namedGroup.end()) {
					namedGroup[name] = new Group();
				}
				saveToNewGroup = 1;
			}
		}
		else
			skippedLines++;

		if (faceIndexExtended.size() > 0) {

			for (int i = 1; i < (int)faceIndexExtended.size() - 1; ++i) {
				auto tmp = new Triangle(vertices[faceIndexExtended[0]], vertices[faceIndexExtended[i]], vertices[faceIndexExtended[i + 1]]);
				if (saveToNewGroup)
					namedGroup[name]->addChild(tmp);
				else
					g.addChild(tmp);
#ifdef DEBUG
				triangles.emplace_back(tmp);
#endif // DEBUG
			}
			
		}
	}

	if (!isNormalized) {
		auto bbox = BoundingBox();

		for (const auto& x : vertices) {
			bbox.addPoint(x);
		}

		auto sx = bbox.boxMax.x - bbox.boxMin.x;
		auto sy = bbox.boxMax.y - bbox.boxMin.y;
		auto sz = bbox.boxMax.z - bbox.boxMin.z;

		auto scale = (double)std::max({ sx, sy, sz }) / (double)2;

		for (Tuple& normalized : vertices) {
			normalized.x = (normalized.x - (bbox.boxMin.x + sx / (double)2)) / scale;
			normalized.y = (normalized.y - (bbox.boxMin.y + sy / (double)2)) / scale;
			normalized.z = (normalized.z - (bbox.boxMin.z + sz / (double)2)) / scale;
		}
		isNormalized = true;
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
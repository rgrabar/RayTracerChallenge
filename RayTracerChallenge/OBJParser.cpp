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
	double n1, n2, n3;

	while (std::getline(myfile, line)) {

		if (line[0] == 'v') {
			
			std::cout << "vertex\n";
			char str[3];

			sscanf_s(line.c_str(), "%*s %lf %lf %lf", &n1, &n2, &n3);

			vertices.push_back(Tuple::point(n1, n2, n3));

		}
		else if (line[0] == 'f') {

			if (line.length() == 7) {

				std::stringstream ss(line);

				std::string s;
				while (std::getline(ss, s, ' ')) {
					std::cout << s << "\n";
					if (s[0] != 'f') {
						int tmp = std::stoi(s) - 1;
						faceIndex.emplace_back(tmp);
						currVertice++;
						if (currVertice == 3) {
							triangles.emplace_back(new Triangle(vertices[faceIndex[0]], vertices[faceIndex[1]], vertices[faceIndex[2]]));
							currVertice = 0;
							faceIndex.clear();
						}
					}
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
					triangles.emplace_back(new Triangle(vertices[faceIndex[0]], vertices[faceIndex[i]], vertices[faceIndex[i + 1]]));
				}
			}
		}

		else
			skippedLines++;
	}
	std::cout << skippedLines << "\n";

}
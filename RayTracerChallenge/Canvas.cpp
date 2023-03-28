#include "Canvas.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string> 
#include <vector>
#include <fstream>
#include <sstream>

Canvas::Canvas(int _w, int _h): w(_w), h(_h) {
	canvas = (Color*)calloc(w * h, sizeof(Color));

	if (canvas) {
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				canvas[i * w + j] = Color(0, 0, 0);
			}
		}
	}
	else {
		std::cout << "Can't allocate memory";
		exit(0);
	}
};

void Canvas::writePixel(int x, int y, const Color& c)const {
	// TODO: don't be dumb
	if(y * w + x < w * h)
		canvas[y * w + x] = c;
}

int Canvas::scaleColor(double c)const {
	if (c < 0)
		return 0;
	else if (c > 1)
		return 255;
	else
		return (int)(255 * c);
}

void Canvas::canvasToImage()const {

	// TODO: limit amount of characters per row below <70

	std::ofstream writer;
	writer.open("canvas.ppm");
	// PPM flavoir identifier
	writer << "P3\n";
	writer << std::to_string(w) << " " << std::to_string(h) << "\n";
	// maximum color value
	writer << "255\n";
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			writer << scaleColor(canvas[i * w + j].r) << " " 
				   << scaleColor(canvas[i * w + j].g) << " " 
				   << scaleColor(canvas[i * w + j].b) << " ";
		}
		writer << "\n";
	}

	writer.close();
}

Canvas canvasFromPPM(const std::string& fileName) {
    std::ifstream ppmFile(fileName);
    std::string line;
    std::vector<int> numbers;
    std::string flavor;
    int width, height, scale;

    // TODO: check if file exists

    while (std::getline(ppmFile, line)) {
        if (line[0] != '#') { // skip comment lines
            break;
        }
    }
    // trim the string
    std::stringstream trimmer;
    trimmer << line;
    line.clear();
    trimmer >> line;

    flavor = line;
    if (flavor != "P3") {
        // TODO: some assert?
        std::cout << "Wrong PPM format\n";
    }


    while (std::getline(ppmFile, line)) {
        if (line[0] != '#') { // skip comment lines
            break;
        }
    }

    std::stringstream ss(line);
    ss >> width >> height;

    while (std::getline(ppmFile, line)) {
        if (line[0] == '#') { // skip comment lines
            continue;
        }
        std::stringstream ss(line);
        int n;
        while (ss >> n) {
            numbers.push_back(n);
        }
    }

    scale = numbers[0];

    auto canvas = Canvas(width, height);

    int cur = 0;

    for (int i = 3; i < numbers.size(); i += 3) {
        canvas.canvas[cur++] = Color(numbers[i - 2] / (double)scale, numbers[i - 1] / (double)scale, numbers[i] / (float)scale);
    }

	return canvas;
}
#include "Canvas.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

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
#ifndef FOR_TEST
    rayImage = Raylib::GenImageColor(w, h, Raylib::Color{ 0, 0, 0, 255 });
#endif //FOR_TEST
};

void Canvas::writePixel(int x, int y, const Color& c) {
	// TODO: don't be dumb
	if(y * w + x < w * h)
		canvas[y * w + x] = c;
#ifndef FOR_TEST
    Raylib::ImageDrawPixel(&rayImage, x, y, Raylib::Color{ scaleColor(c.r), scaleColor(c.g), scaleColor(c.b), 255 });
#endif //FOR_TEST
}

unsigned char Canvas::scaleColor(double c)const {
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
			writer << (int)scaleColor(canvas[i * w + j].r) << " " 
				   << (int)scaleColor(canvas[i * w + j].g) << " " 
				   << (int)scaleColor(canvas[i * w + j].b) << " ";
		}
		writer << "\n";
	}

	writer.close();
}

Canvas canvasFromPPM(const std::string& fileName) {
    std::ifstream ppmFile(fileName, std::ios::binary);

    if (ppmFile.fail()){
        std::cout << "File does't exist!\n";
        assert(0);
    }

    std::string line;
    std::vector<int> numbers;
    std::string flavor;
    int width, height, scale;

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
    if (flavor != "P3" && flavor != "P6") {
        std::cout << "Wrong PPM format\n";
#ifndef FOR_TEST
        assert(0);
#endif //FOR_TEST
    }

   
    while (std::getline(ppmFile, line)) {
        if (line[0] != '#') { // skip comment lines
            break;
        }
    }

    std::stringstream ss(line);
    ss >> width >> height;

    if (flavor == "P3") {

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

        for (int i = 3; i < (int)numbers.size(); i += 3) {
            canvas.canvas[cur++] = Color(numbers[i - 2] / (double)scale, numbers[i - 1] / (double)scale, numbers[i] / (float)scale);
        }

        return canvas;
    }
    else {
        const int num_pixels = width * height;
        std::vector<unsigned char>data(num_pixels * 3);
        int max_value;
        ppmFile >> max_value;

        ppmFile.read(reinterpret_cast<char*>(data.data()), num_pixels * 3);

        int cur = 0;
        auto canvas = Canvas(width, height);
        for (int i = 0; i < num_pixels; ++i) {
            canvas.canvas[cur++] = Color(static_cast<int>(data[i * 3 + 1]) / (double)max_value, static_cast<int>(data[i * 3 + 2]) / (double)max_value, static_cast<int>(data[i * 3]) / (double)max_value);
        }

        // Close the file
        ppmFile.close();
        return canvas;
    }
}
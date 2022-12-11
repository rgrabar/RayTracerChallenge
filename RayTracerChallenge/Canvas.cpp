#include "Canvas.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string> 



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

int Canvas::scaleColor(float c) const{
	if (c < 0)
		return 0;
	else if (c > 1)
		return 255;
	else
		return (int)(255 * c);
}

void Canvas::canvasToImage() const{

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
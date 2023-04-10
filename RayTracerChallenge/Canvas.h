#pragma once
#include"Color.h"

#include <string> 

#ifndef FOR_TEST

namespace Raylib {
	#include "raylib.h"
};

#endif //FOR_TEST

class Canvas {
public:
	Canvas(int _w, int _h);
	int w, h;
	Color* canvas;
	void writePixel(int x, int y, const Color& c)const;
	void canvasToImage()const;
	unsigned char scaleColor(double c)const;
#ifndef FOR_TEST
	mutable Raylib::Image rayImage;
#endif //FOR_TEST
};

Canvas canvasFromPPM(const std::string& fileName);
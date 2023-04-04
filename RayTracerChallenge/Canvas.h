#pragma once
#include"Color.h"

#include <string> 

namespace Raylib {
	#include "raylib.h"
};

class Canvas {
public:
	Canvas(int _w, int _h);
	int w, h;
	Color* canvas;
	void writePixel(int x, int y, const Color& c)const;
	void canvasToImage()const;
	unsigned char scaleColor(double c)const;
	mutable Raylib::Image rayImage;
};

Canvas canvasFromPPM(const std::string& fileName);
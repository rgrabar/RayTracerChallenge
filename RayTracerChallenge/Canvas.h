#pragma once
#include"Color.h"

#include <string> 

#ifndef DEBUG

namespace Raylib {
	#include "raylib.h"
};

#endif

class Canvas {
public:
	Canvas(int _w, int _h);
	int w, h;
	Color* canvas;
	void writePixel(int x, int y, const Color& c)const;
	void canvasToImage()const;
	unsigned char scaleColor(double c)const;
#ifndef DEBUG
	mutable Raylib::Image rayImage;
#endif
};

Canvas canvasFromPPM(const std::string& fileName);
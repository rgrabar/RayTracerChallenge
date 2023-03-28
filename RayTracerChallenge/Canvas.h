#pragma once
#include"Color.h"

class Canvas {
public:
	Canvas(int _w, int _h);
	int w, h;
	Color* canvas;
	void writePixel(int x, int y, const Color& c)const;
	void canvasToImage()const;
	int scaleColor(double c)const;
};

Canvas canvasFromPPM();
#pragma once
#include<vector>
#include"Color.h"

class Canvas {
public:
	Canvas(int _w, int _h);
	int h, w;
	Color* canvas;
	void writePixel(int x, int y, Color c);
	void canvasToImage()const ;
	int scaleColor(float c)const;
};
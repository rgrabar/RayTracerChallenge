#pragma once


struct Color {
public:
	Color(float r, float g, float b);
	float r, g, b;


};

bool operator==(const Color& firstColor, const Color& secondColor);
Color operator+(const Color& firstColor, const Color& secondColor);
Color operator-(const Color& firstColor, const Color& secondColor);
Color operator*(const Color& color, float scalar);
Color operator*(const Color& firstColor, const Color& secondColor);
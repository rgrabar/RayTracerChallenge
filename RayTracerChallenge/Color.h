#pragma once


struct Color {
public:
	Color(double r, double g, double b);
	double r, g, b;
};

bool operator==(const Color& firstColor, const Color& secondColor);
Color operator+(const Color& firstColor, const Color& secondColor);
Color operator-(const Color& firstColor, const Color& secondColor);
Color operator*(const Color& color, double scalar);
Color operator*(const Color& firstColor, const Color& secondColor);
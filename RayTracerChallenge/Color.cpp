#include "Color.h"
#include "Helper.h"

Color::Color(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {};

Color operator+(const Color& firstColor, const Color& secondColor) {
	return Color(firstColor.r + secondColor.r, firstColor.g + secondColor.g, firstColor.b + secondColor.b);
}

Color operator-(const Color& firstColor, const Color& secondColor) {
	return Color(firstColor.r - secondColor.r, firstColor.g - secondColor.g, firstColor.b - secondColor.b);
}

Color operator*(const Color& c, const double scalar) {
	return Color(c.r * scalar, c.g * scalar, c.b * scalar);
}

Color operator/(const Color& c, const double scalar) {
	return Color(c.r / scalar, c.g / scalar, c.b / scalar);
}

Color operator*(const Color& firstColor, const Color& secondColor) {
	return Color(firstColor.r * secondColor.r, firstColor.g * secondColor.g, firstColor.b * secondColor.b);
}

bool operator==(const Color& firstColor, const Color& secondColor) {
	return epsilonEqual(firstColor.r, secondColor.r) && 
		   epsilonEqual(firstColor.g, secondColor.g) && 
		   epsilonEqual(firstColor.b, secondColor.b);
}
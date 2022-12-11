#include "Color.h"
#include "Helper.h"

Color::Color(float x, float y, float z) : r(x), g(y), b(z) {};



Color operator+(const Color& firstColor, const Color& secondColor) {
	return Color(firstColor.r + secondColor.r, firstColor.g + secondColor.g, firstColor.b + secondColor.b);
}

Color operator-(const Color& firstColor, const Color& secondColor) {
	return Color(firstColor.r - secondColor.r, firstColor.g - secondColor.g, firstColor.b - secondColor.b);
}

Color operator*(const Color& c, const float scalar) {
	return Color(c.r * scalar, c.g * scalar, c.b * scalar);
}

Color operator*(const Color& firstColor, const Color& secondColor) {
	return Color(firstColor.r * secondColor.r, firstColor.g * secondColor.g, firstColor.b * secondColor.b);
}

bool operator==(const Color& firstColor, const Color& secondColor) {
	return epsilonEqual(firstColor.r, secondColor.r) && 
		   epsilonEqual(firstColor.g, secondColor.g) && 
		   epsilonEqual(firstColor.b, secondColor.b);
}
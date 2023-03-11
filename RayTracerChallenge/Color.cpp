#include "Color.h"
#include "Helper.h"

Color::Color(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {};

Color Color::operator*(const double scalar)const {
	return Color(r * scalar, g * scalar, b * scalar);
}

Color Color::operator*(const Color& secondColor)const {
	return Color(r * secondColor.r, g * secondColor.g, b * secondColor.b);
}

Color& Color::operator*=(const double scalar) {
	r *= scalar; g *= scalar; b *= scalar; return *this;
}

Color& Color::operator*=(const Color& secondColor) {
	r *= secondColor.r; g *= secondColor.g; b *= secondColor.b; return *this;
}

Color Color::operator/(const double scalar)const {
	return operator*(1 / scalar);
}

Color Color::operator+(const Color& secondColor)const {
	return Color(r + secondColor.r, g + secondColor.g, b + secondColor.b);
}

Color Color::operator+=(const Color& secondColor) {
	r += secondColor.r; g += secondColor.g; b += secondColor.b; return *this;
}

Color Color::operator-(const Color& secondColor)const {
	return Color(r - secondColor.r, g - secondColor.g, b - secondColor.b);
}

bool Color::operator==(const Color& secondColor)const {
	return epsilonEqual(r, secondColor.r) && 
		   epsilonEqual(g, secondColor.g) && 
		   epsilonEqual(b, secondColor.b);
}
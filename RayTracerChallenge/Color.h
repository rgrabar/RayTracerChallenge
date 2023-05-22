#pragma once


struct Color {

	Color(double r, double g, double b);
	double r, g, b;
	Color operator*(double scalar)const;
	Color& operator*=(const double scalar);
	Color operator/(double scalar)const;

	Color operator*(const Color& secondColor)const;
	Color& operator*=(const Color& secondColor);
	Color operator+(const Color& secondColor)const;
	Color& operator+=(const Color& secondColor);
	Color operator-(const Color& secondColor)const;
	
	bool operator==(const Color& secondColor)const;
	bool operator!=(const Color& secondColor)const;
};

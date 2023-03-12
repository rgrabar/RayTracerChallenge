#pragma once
#include <math.h>

struct Tuple {

	Tuple(double x, double y, double z, double w);

	static Tuple point(double x, double y, double z) {
		return Tuple(x, y, z, 1.f);
	}

	static Tuple vector(double x, double y, double z) {
		return Tuple(x, y, z, 0.f);
	}

	bool isPoint();
	bool isVector();
	double magnitude()const;
	Tuple normalize()const;
	double dotProduct(const Tuple& v)const;
	Tuple crossProduct(const Tuple& v)const;
	Tuple reflect(const Tuple& normal);
	double x, y, z, w;
	
	Tuple operator*(double scalar)const;
	Tuple& operator*=(const double scalar);
	Tuple operator/(double scalar)const;

	Tuple& operator+=(const Tuple& rhs);
	Tuple operator-(const Tuple& rhs)const;
	Tuple operator-()const;
	bool operator==(const Tuple& rhs)const;
	bool operator!=(const Tuple& rhs)const;
};

// TODO: why does this not work when it's a member variable
Tuple operator+(Tuple lhs, const Tuple& rhs);
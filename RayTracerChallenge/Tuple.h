#pragma once
#include <math.h>

struct Tuple {

	Tuple(float x, float y, float z, float w);

	static Tuple point(float x, float y, float z) {
		return Tuple(x, y, z, 1.f);
	}

	static Tuple vector(float x, float y, float z) {
		return Tuple(x, y, z, 0.f);
	}


	bool isPoint();
	bool isVector();
	float magnitude();
	Tuple normalize();
	float dotProduct(const Tuple& v) const;
	Tuple crossProduct(const Tuple& v) const;

	float x, y, z, w;
};

bool operator==(const Tuple& lhs, const Tuple& rhs);
Tuple operator+(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& negate);
Tuple operator*(const Tuple& negate, float scalar);
Tuple operator/(const Tuple& negate, float scalar);
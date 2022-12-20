#include "Tuple.h"
#include "Helper.h"

Tuple::Tuple(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {
};

bool Tuple::isPoint() {
	return epsilonEqual(1.0, w);
}

bool Tuple::isVector() {
	return epsilonEqual(0.0, w);
}

double Tuple::magnitude()const{
	return std::sqrt(x * x + y * y + z * z + w + w);
}

Tuple Tuple::normalize()const {
	double mag = magnitude();
	return Tuple(x / mag, y / mag, z / mag, w / mag);
}

double Tuple::dotProduct(const Tuple& v)const {
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

Tuple Tuple::crossProduct(const Tuple& v)const {
	return Tuple::vector(y * v.z - z * v.y, z * v.x - x *v.z, x * v.y - y * v.x);
}

bool operator==(const Tuple& lhs, const Tuple& rhs) {
	return epsilonEqual(lhs.x, rhs.x) &&
		   epsilonEqual(lhs.y, rhs.y) &&
		   epsilonEqual(lhs.z, rhs.z) &&
		   epsilonEqual(lhs.w, rhs.w);
}

Tuple operator+(const Tuple& lhs, const Tuple& rhs) {
	return Tuple(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Tuple operator-(const Tuple& lhs, const Tuple& rhs) {
	return Tuple(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

Tuple operator-(const Tuple& negate) {
	return Tuple(-negate.x, -negate.y, -negate.z, -negate.w);
}

Tuple operator*(const Tuple& tuple, double scalar) {
	return Tuple(tuple.x * scalar, tuple.y * scalar, tuple.z * scalar, tuple.w * scalar);
}

Tuple operator/(const Tuple& tuple, double scalar) {
	return Tuple(tuple.x / scalar, tuple.y / scalar, tuple.z / scalar, tuple.w / scalar);
}
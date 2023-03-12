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

Tuple Tuple::reflect(const Tuple& normal) {
	return *this - normal * 2 * dotProduct(normal);
}





Tuple Tuple::operator*(double scalar)const {
	return Tuple(x * scalar, y * scalar, z * scalar, w * scalar);
}

Tuple& Tuple::operator*=(const double scalar) {
	x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this;
}

Tuple Tuple::operator/(double scalar)const {
	return operator*(1 / scalar);
}

Tuple& Tuple::operator+=(const Tuple& rhs) {
	x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this;
}

Tuple operator+(Tuple lhs, const Tuple& rhs) {
	return lhs += rhs;
}

Tuple Tuple::operator-(const Tuple& rhs)const {
	return Tuple(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Tuple Tuple::operator-()const {
	return Tuple(-x, -y, -z, -w);
}

bool Tuple::operator==(const Tuple& rhs)const {
	return epsilonEqual(x, rhs.x) &&
		   epsilonEqual(y, rhs.y) &&
		   epsilonEqual(z, rhs.z) &&
		   epsilonEqual(w, rhs.w);
}

bool Tuple::operator!=(const Tuple& rhs)const {
	return !operator==(rhs);
}

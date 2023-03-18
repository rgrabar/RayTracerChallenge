#include "Triangle.h"

Triangle::Triangle(const Tuple& _p1, const Tuple _p2, const Tuple _p3) : p1(_p1), p2(_p2), p3(_p3), e1(_p2 - _p1), e2(_p3 - _p1), normal(e2.crossProduct(e1).normalize()) {}

 Tuple Triangle::objectNormal(const Tuple& worldPoint, const Intersection* hit = nullptr)const {
	return normal;
}

Intersections Triangle::intersect(const Ray& ray)const {

	auto dirCrossE2 = ray.direction.crossProduct(e2);
	auto det = e1.dotProduct(dirCrossE2);

	if (std::abs(det) < EPSILON)
		return {};

	auto f = 1.0 / det;
	auto p1ToOrigin = ray.origin - p1;
	auto u = f * p1ToOrigin.dotProduct(dirCrossE2);

	if ((u < 0) || (u > 1) || epsilonEqual(0, u) || epsilonEqual(1, u))
		return {};

	auto originCrossE1 = p1ToOrigin.crossProduct(e1);

	auto v = f * ray.direction.dotProduct(originCrossE1);

	if ((v < 0) || (u + v > 1))
		return {};


	auto t = f * e2.dotProduct(originCrossE1);

	Intersection* i1 = new Intersection(t, this);

	Intersections inter;
	inter.intersections.insert(i1);

	return inter;
}

BoundingBox Triangle::boundsOf(bool update = false) {
	auto box = BoundingBox();

	box.addPoint(p1);
	box.addPoint(p2);
	box.addPoint(p3);

	return box;
}

void Triangle::divide(int threashold = 1) {}

bool Triangle::includes(const Shape* s)const {
	return this == s;
}

void Triangle::setMaterial(const Material& s) {
	material = s;
}

// SMOOTH TRIANGLE

SmoothTriangle::SmoothTriangle(const Tuple& _p1, const Tuple _p2, const Tuple _p3, const Tuple _n1, const Tuple _n2, const Tuple _n3) :
	p1(_p1), p2(_p2), p3(_p3), n1(_n1), n2(_n2), n3(_n3), e1(_p2 - _p1), e2(_p3 - _p1) {

}

Tuple SmoothTriangle::objectNormal(const Tuple& worldPoint, const Intersection* hit = nullptr)const {
	return n2 * hit->u + n3 * hit->v + n1 * (1 - hit->u - hit->v);
}

Intersections SmoothTriangle::intersect(const Ray& ray)const {

	auto dirCrossE2 = ray.direction.crossProduct(e2);
	auto det = e1.dotProduct(dirCrossE2);

	if (std::abs(det) < EPSILON)
		return {};

	auto f = 1.0 / det;
	auto p1ToOrigin = ray.origin - p1;
	auto u = f * p1ToOrigin.dotProduct(dirCrossE2);

	if ((u < 0) || (u > 1) || epsilonEqual(0, u) || epsilonEqual(1, u))
		return {};

	auto originCrossE1 = p1ToOrigin.crossProduct(e1);

	auto v = f * ray.direction.dotProduct(originCrossE1);

	if ((v < 0) || (u + v > 1))
		return {};


	auto t = f * e2.dotProduct(originCrossE1);

	Intersection* i1 = new Intersection(t, this, u, v);

	Intersections inter;
	inter.intersections.insert(i1);

	return inter;
}

BoundingBox SmoothTriangle::boundsOf(bool update = false) {
	auto box = BoundingBox();

	box.addPoint(p1);
	box.addPoint(p2);
	box.addPoint(p3);

	return box;
}

void SmoothTriangle::divide(int threashold = 1) {}

bool SmoothTriangle::includes(const Shape* s)const {
	return this == s;
}

void SmoothTriangle::setMaterial(const Material& s) {
	material = s;
}
#include "Sphere.h"

Sphere::Sphere() : Shape(Tuple::point(0, 0, 0)) {}

bool Sphere::operator==(const Sphere& o) const {
	//TODO: CHECK TRANSFORM
	return o.origin == origin;
}

Intersections Sphere::intersect(const Ray& ray)const {

	auto shapeToRay = ray.origin - Tuple::point(0, 0, 0);
	auto a = ray.direction.dotProduct(ray.direction);
	auto b = 2 * ray.direction.dotProduct(shapeToRay);
	auto c = shapeToRay.dotProduct(shapeToRay) - 1;

	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return {};

	double t1 = (-b - sqrt(discriminant)) / (2 * a);
	double t2 = (-b + sqrt(discriminant)) / (2 * a);

	Intersection* i1 = new Intersection(t1, this);
	Intersection* i2 = new Intersection(t2, this);

	Intersections inter;
	inter.intersections.insert(i1);
	inter.intersections.insert(i2);

	/*std::vector<Intersection> retInter;
	retInter.emplace_back(t1, s);
	retInter.emplace_back(t2, s);
	*/
	return inter;
}
Tuple Sphere::objectNormal(const Tuple& objectPoint, const Intersection* hit = nullptr)const {
	return objectPoint - Tuple::point(0, 0, 0);
}

BoundingBox Sphere::boundsOf(bool update = false) {
	return BoundingBox(Tuple::point(-1, -1, -1), Tuple::point(1, 1, 1));
}

inline void Sphere::divide(int threashold = 1) {
	return;
}

inline bool Sphere::includes(const Shape* s)const {
	return this == s;
}

inline void Sphere::setMaterial(const Material& s) {
	material = s;
}
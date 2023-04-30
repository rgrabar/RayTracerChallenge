#include "Sphere.h"

Sphere::Sphere() : Shape(Point(0, 0, 0)) {}

bool Sphere::operator==(const Sphere& o) const {
	//TODO: CHECK TRANSFORM
	return o.origin == origin;
}

Intersections Sphere::intersect(const Ray& ray)const {

	auto shapeToRay = ray.origin - Point(0, 0, 0);
	auto a = ray.direction.dotProduct(ray.direction);
	auto b = 2.0 * ray.direction.dotProduct(shapeToRay);
	auto c = shapeToRay.dotProduct(shapeToRay) - 1.0;

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
Tuple Sphere::objectNormal(const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit)const {
	return objectPoint - Point(0, 0, 0);
}

BoundingBox Sphere::boundsOf([[maybe_unused]] bool update) {
	return BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));
}

void Sphere::divide([[maybe_unused]] int threashold) {
	return;
}

bool Sphere::includes(const Shape* s)const {
	return this == s;
}

void Sphere::setMaterial(const Material& s) {
	material = s;
}

void Sphere::UVmap(const Tuple& p, double* u, double* v) const {
	auto theta = atan2(p.x, p.z);

	Tuple vec = Vector(p.x, p.y, p.z);
	auto radius = vec.magnitude();

	auto phi = acos(p.y / radius);
	auto rawU = theta / (2.0 * acos(-1));

	*u = 1.0 - (rawU + 0.5);
	*v = 1.0 - (phi / acos(-1));
}
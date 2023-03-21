#pragma once
#include <string>
#include "Shape.h"

class CSGShape : public Shape{
public:
	std::string operation;
	Shape* left;
	Shape* right;
	BoundingBox m_bounds;

	CSGShape(std::string _operation, Shape* _left, Shape* _right);
	bool intersectionAllowed(std::string op, bool lhit, bool inl, bool inr)const;
	Intersections filterIntersections(const Intersections& xs)const;

	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal([[maybe_unused]] const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit = nullptr)const override;
	// TODO: cache bounds?
	BoundingBox boundsOf([[maybe_unused]] bool update = false) override;
	void divide([[maybe_unused]] int threashold = 1)override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;
};
#pragma once

#include "BoundingBox.h"
#include "Intersection.h"
#include "Tuple.h"
#include "Shape.h"
#include <vector>

struct Group : public Shape {

	std::vector<Shape*> children;
	BoundingBox m_bounds;
	bool is_m_bounds_set = 0;

	~Group();

	void addChild(Shape* s);
	void partitionChildren(Group& leftG, Group& rightG);
	void makeSubgroup(Group& sub);

	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal([[maybe_unused]] const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf(bool update = false)override;
	void divide(int threashold = 1)override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;
};
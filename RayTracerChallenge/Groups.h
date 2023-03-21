#pragma once
#include "Shape.h"
#include <vector>

class Group : public Shape {
public:
	//TODO: materials for groups

	std::vector<Shape*> children;
	BoundingBox m_bounds;

	~Group();

	//TODO: passing a local group variable as child
	// breaks everything yay
	void addChild(Shape* s);
	// TODO: do this better
	void partitionChildren(Group& leftG, Group& rightG);
	void makeSubgroup(Group& sub);

	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal([[maybe_unused]] const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf(bool update = false)override;
	void divide(int threashold = 1)override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;
};
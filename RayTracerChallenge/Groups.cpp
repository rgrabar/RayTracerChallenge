#include "Groups.h"

Group::~Group() {
	for (auto child : children) {
		if (dynamic_cast<Group*>(child)) {
			// cast only to avoid warning
			delete (Group*)child;
		}
	}
}

//TODO: passing a local group variable as child
// breaks everything yay
void Group::addChild(Shape* s) {
	children.emplace_back(s);
	s->parent = this;

	// TODO: update bounds if needed
	boundsOf(true);
}

// TODO: do this better
void Group::partitionChildren(Group& leftG, Group& rightG) {
	BoundingBox left, right;

	auto bounds = m_bounds;
	bounds.splitBounds(&left, &right);

	std::vector<Shape*> newChildren;

	for (auto child : children) {
		auto childBounds = child->parentSpaceBoundsOf();
		if (left.contains(childBounds)) {
			leftG.addChild(child);
		}
		else if (right.contains(childBounds)) {
			rightG.addChild(child);
		}
		else
			newChildren.emplace_back(child);
	}
	children = newChildren;
}

void Group::makeSubgroup(Group& sub) {
	auto g = new Group();
	for (auto s : sub.children) {
		g->addChild(s);
	}
	addChild(g);
}


Intersections Group::intersect(const Ray& ray)const {

	if (!m_bounds.intersect(ray)) {
		return {};
	}

	Intersections i;

	for (auto shape : children) {
		// TODO: do this somehow else, overload intersect to take a vector?
		auto v = shape->shapeIntersect(ray);
		for (auto objectIntersect : v.intersections)
			i.intersections.insert(objectIntersect);
	}
	return i;
}

Tuple Group::objectNormal(const Tuple& objectPoint, const Intersection* hit)const {
	return Tuple::vector(0, 0, 0);
}

BoundingBox Group::boundsOf(bool update) {
	// TODO: cache the box, don't update if not needed
	if (update) {
		auto box = BoundingBox();

		for (auto shape : children) {
			auto cbox = shape->parentSpaceBoundsOf();
			box.mergeBox(cbox);
		}

		m_bounds = box;
	}
	return m_bounds;
}


bool Group::includes(const Shape* s)const {
	return std::find(children.begin(), children.end(), s) != children.end();
}


void Group::divide(int threashold) {

	if (threashold <= (int)children.size()) {
		auto left = Group();
		auto right = Group();

		partitionChildren(left, right);
		if (left.children.size() != 0) {
			makeSubgroup(left);
		}
		if (right.children.size() != 0) {
			makeSubgroup(right);
		}
	}

	for (auto child : children) {
		child->shapeDivide(threashold);
	}
}

void Group::setMaterial(const Material& s) {
	for (auto child : children) {
		child->setMaterial(s);
	}
}
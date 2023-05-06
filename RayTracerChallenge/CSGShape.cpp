#include "CSGShape.h"

CSGShape::CSGShape(CSGOperation::OPERATION _operation, Shape* _left, Shape* _right) : operation(_operation), left(_left), right(_right) {
	left->parent = this;
	right->parent = this;
}

bool CSGShape::intersectionAllowed(CSGOperation::OPERATION op, bool lhit, bool inl, bool inr)const {
	if (op == CSGOperation::OPERATION::UNION) {
		return (lhit && !inr) || (!lhit && !inl);
	}
	else if (op == CSGOperation::OPERATION::INTERSECTION) {
		return (lhit && inr) || (!lhit && inl);
	}
	else if (op == CSGOperation::OPERATION::DIFFERENCE) {
		return (lhit && !inr) || (!lhit && inl);
	}

	return false;
}

Intersections CSGShape::filterIntersections(const Intersections& xs)const {
	auto inl = false;
	auto inr = false;

	auto result = Intersections();

	for (auto intersection : xs.intersections) {

		// TODO: page 235 implement Group and CSG serach
		auto lhit = left->includes((Shape*)intersection->s);

		if (intersectionAllowed(operation, lhit, inl, inr)) {
			result.intersections.insert(intersection);
		}
		if (lhit) {
			inl = !inl;
		}
		else {
			inr = !inr;
		}
	}

	return result;
}

Intersections CSGShape::intersect(const Ray& ray)const {
	if (!m_bounds.intersect(ray)) {
		return {};
	}
	auto leftxs = left->shapeIntersect(ray);
	auto rightxs = right->shapeIntersect(ray);

	auto xs = Intersections();

	xs.intersections.insert(leftxs.intersections.begin(), leftxs.intersections.end());
	xs.intersections.insert(rightxs.intersections.begin(), rightxs.intersections.end());

	return filterIntersections(xs);
}

Tuple CSGShape::objectNormal([[maybe_unused]] const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit)const {
	// CSG returns normal of primitive shape, this shouldn't happen
	return Vector(0, 0, 0);
}

BoundingBox CSGShape::boundsOf([[maybe_unused]] bool update) {
	// TODO: cache the box, don't update if not needed
	// TODO: check if it works
	auto box = BoundingBox();

	auto rBox = right->parentSpaceBoundsOf();
	auto lBox = left->parentSpaceBoundsOf();

	box.mergeBox(rBox);
	box.mergeBox(lBox);

	m_bounds = box;

	return m_bounds;
}
// TODO: cache bounds?
void CSGShape::divide([[maybe_unused]] int threashold) {
	right->divide();
	left->divide();
}

bool CSGShape::includes(const Shape* s)const {
	return left->includes(s) || right->includes(s);
}

void CSGShape::setMaterial(const Material& s) {
	right->material = s;
	left->material = s;
}
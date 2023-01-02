#include "BlendedPattern.h"

Color BlendedPattern::patternColorAt(const Tuple& point) {

	// TODO: this works but is it even correct? the transform part shouldn't it be transformed?

	auto patternPointA = *(a->transform.inverse()) * point;
	auto patternPointB = *(b->transform.inverse()) * point;

	Color aCol = a->patternColorAt(patternPointA);
	Color bCol = b->patternColorAt(patternPointB);

	return (aCol + bCol) / 2.f;
}
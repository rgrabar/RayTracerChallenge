#pragma once
#include "Pattern.h"

class RingPattern : public Pattern {
public:
	RingPattern() {}
	RingPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}

	Color patternColorAt(const Tuple& point)const;

};
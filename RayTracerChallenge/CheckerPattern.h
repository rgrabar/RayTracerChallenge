#pragma once
#include "Pattern.h"

class CheckerPattern : public Pattern {
public:
	CheckerPattern() {}
	CheckerPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}

	Color patternColorAt(const Tuple& point)const;

};

#pragma once
#include "Pattern.h"

class StripePattern :public Pattern {
public:
	StripePattern() {}
	StripePattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}

	Color patternColorAt(const Tuple& point);
};
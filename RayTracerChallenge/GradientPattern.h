#pragma once
#include "Pattern.h"


class GradientPattern : public Pattern{
public:
	GradientPattern() {}
	GradientPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}

	Color patternColorAt(const Tuple& point);
};
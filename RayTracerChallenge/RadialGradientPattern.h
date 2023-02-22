#pragma once
#include "Pattern.h"

class RadialGradientPattern : public Pattern{
public:

	int type = 0;

	RadialGradientPattern() {}
	RadialGradientPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}
	RadialGradientPattern(const Color& _a, const Color& _b, int _type) : Pattern(_a, _b),  type(_type) {}

	Color patternColorAt(const Tuple& point)const override;
};
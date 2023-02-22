#pragma once
#include "Pattern.h"

class BlendedPattern :public Pattern {
public:
	BlendedPattern() {}
	BlendedPattern(Pattern* _a, Pattern* _b) : a(_a), b(_b) {}

	Color patternColorAt(const Tuple& point)const override;

	Pattern* a = nullptr;
	Pattern* b = nullptr;
};
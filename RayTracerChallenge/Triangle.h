#pragma once
#include "Tuple.h"

class Triangle{
	
public:

	Tuple p1;
	Tuple p2;
	Tuple p3;

	Tuple e1;
	Tuple e2;

	// TODO: default constructor for tuples
	Tuple normal;

	Triangle(const Tuple& _p1, const Tuple _p2, const Tuple _p3) : p1(_p1), p2(_p2), p3(_p3), e1(_p2 - _p1), e2(_p3 - _p1), normal(e2.crossProduct(e1).normalize()) {

	}

};
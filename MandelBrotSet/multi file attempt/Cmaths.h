#pragma once
#include "Complex.h"

class Cmaths {
public:
	Complex multiply(Complex a, Complex b);
	Complex add(Complex a, Complex b);

	long double magintude_squared(Complex a);
};
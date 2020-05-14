#include "Cmaths.h"

Complex Cmaths::multiply(Complex a, Complex b) {
	Complex num(a.real * b.real - a.imaginary * b.imaginary,
		a.real * b.imaginary + b.real * a.imaginary);

	return num;
};
Complex Cmaths::add(Complex a, Complex b) {
	Complex num(a.real + b.real, a.imaginary + b.imaginary);
	return num;
}

long double Cmaths::magintude_squared(Complex a) {
	return a.real * a.real + a.imaginary * a.imaginary;
};
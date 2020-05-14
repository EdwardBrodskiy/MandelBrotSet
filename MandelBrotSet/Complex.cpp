#include "Complex.h"

Complex::Complex(long double real_in , long double imaginary_in) {
	real = real_in;
	imaginary = imaginary_in;
}

Complex::Complex() {
	real = 0;
	imaginary = 0;
}



Complex Complex::operator*(Complex other) {
	Complex num(real * other.real - imaginary * other.imaginary,
		real * other.imaginary + other.real * imaginary);

	return num;
}

Complex Complex::operator+(Complex other) {
	Complex num(real + other.real, imaginary + other.imaginary);
	return num;
}

long double Complex::magintude_squared() {
	return real * real + imaginary * imaginary;
}

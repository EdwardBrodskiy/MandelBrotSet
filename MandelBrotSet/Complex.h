#pragma once

struct Complex {

	long double real, imaginary;

	Complex(long double real_in, long double imaginary_in);

	Complex();

	Complex operator*(Complex other);

	Complex operator+(Complex other);

	long double magintude_squared(); 


};
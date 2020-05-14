#include "common_maths_func.h"

float modulus(float num) {
	if (num > 0) {
		return num;
	}
	else {
		return -num;
	}
}
float mod(float num, float divisor) {
	while (num > divisor) {
		num -= divisor;
	}
	return num;
}
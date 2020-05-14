# include "Grid.h"

Grid::Grid(int width, int height) {
	points = new sf::Uint8[width * height * 4];
}

Grid::~Grid() {
	delete points;
}

sf::Uint8* Grid::get_full() {
	return points;
}

void Grid::set_colour_to_point(int index, int r, int g, int b, int brightness) {
	points[index * 4] = r;
	points[index * 4 + 1] = g;
	points[index * 4 + 2] = b;
	points[index * 4 + 3] = brightness;
};

void Grid::set_colour_by_hue(int index, float hue) {
	// light is set to 0.5 and saturation is set to 1 so we only need to get x
	float c = 1;

	float x = c * (1.0 - modulus(mod(hue / 60.0, 2.0) - 1.0));

	float m = 0;

	float icolour[3];


	if (hue < 60.0) {
		icolour[0] = c; icolour[1] = x; icolour[2] = 0;
	}
	else if (hue < 120.0) {
		icolour[0] = x; icolour[1] = c; icolour[2] = 0;
	}
	else if (hue < 180.0) {
		icolour[0] = 0; icolour[1] = c; icolour[2] = x;
	}
	else if (hue < 240.0) {
		icolour[0] = 0; icolour[1] = x; icolour[2] = c;
	}
	else if (hue < 300.0) {
		icolour[0] = x; icolour[1] = 0; icolour[2] = c;
	}
	else if (hue < 360.0) {
		icolour[0] = c; icolour[1] = 0; icolour[2] = x;
	}

	for (int i = 0; i < 3; i++) {
		points[index * 4 + i] = int((icolour[i] + m) * 255 + 0.5);
	}
	points[index * 4 + 3] = 255;

}

int Grid::r(int index) {
	return points[index * 4];
}
int Grid::g(int index) {
	return points[index * 4 + 1];
}
int Grid::b(int index) {
	return points[index * 4 + 2];
}
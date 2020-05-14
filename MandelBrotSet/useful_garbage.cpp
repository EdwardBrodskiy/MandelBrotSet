/* Useful Grabge

###Has all the shit for hsl to rgb conversion 
struct Point {
	int colour[3];

void set_colour_by_hsl(float hue, float sat, float light) {
	float c = (1.0 - modulus(2.0 * light - 1.0)) * sat;

	float x = c * (1.0 - modulus(mod(hue / 60.0, 2.0) - 1.0));

	float m = light - c / 2.0;

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
		colour[i] = int((icolour[i] + m) * 255 + 0.5);
	}
}
};
### Old no large array render version
int* colour;
if (time != -1) {
	colour = set_colour_by_hue(time % 360);
	
}else{
	colour = new int[3]{0};
}
shape.setFillColor(sf::Color(colour[0], colour[1], colour[2]));
delete colour;
shape.setPosition(sf::Vector2f((float)i, (float)j));
window.draw(shape);

### sfml shit

#include <SFML\Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	sf::CircleShape shape(0.5f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(sf::Vector2f(20.f, 40.f));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

}
### Old render method

point_index = pixel_column + pixel_row * width;
long double real = pixel_column * 2 * scale / width - scale + center_x;
long double imaginary = pixel_row * 2 * scale / height - scale + center_y;
Complex c(real, imaginary);
int time = itterations_to_escape(c, itterations);


if (time != -1) {
	pixels.set_colour_by_hue(point_index, time % 360);
}
else {
	pixels.set_colour_to_point(point_index, 0, 0, 0);
}

pixel_column++;
if (not (pixel_column < width)) {
	pixel_column = 0;
	pixel_row++;
	if (not (pixel_row < height)) {
		pixel_row = 0;
		rendering = false;
		displaying = true;
	}
}

### the full main before integrating the Mandelbrot object

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Complex.h"
#include "Grid.h"

Complex mandelbrot_eq(Complex z, Complex c);

int itterations_to_escape(Complex c, int limit);

void add_to_buddah_brot(int i, int limit ,Complex z);

int main() {
	int height = 900;
	int width = 1400;

	float w_to_h_ratio = (float)height / (float)width;


	Grid pixels(width, height);

	//Grid buddah(width, height);

	sf::RenderWindow window(sf::VideoMode(width, height), "MandelBrotSet", sf::Style::Close | sf::Style::Titlebar);

	sf::Texture image;
	sf::Sprite sprite;
	image.create(width, height);
	sprite.setTexture(image);
	sprite.setPosition(0, 0);

	// First render settings
	long double center_x = (long double)0;
	long double center_y = (long double)0;
	long double scale = (long double)2;
	int itterations = 720;

	// Inner loop variables
	int pixel_column = 0;
	int pixel_row = 0;
	int point_index = 0;
	sf::Vector2i mouse_pos;

	bool displaying = false;
	bool pre_rendering = false;
	bool rendering = true;

	window.clear();
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
			}

		}

		if (displaying) {

			image.update(pixels.points);
			window.draw(sprite);
			window.display();
			displaying = false;
		}
		else if (pre_rendering) {
			point_index = pixel_column + pixel_row * width;
			Grid temp(width / 2, height / 2);

			pixels.set_colour_to_point(point_index, 100, 100, 100);


			pixel_column++;
			if (not (pixel_column < width)) {
				pixel_column = 0;
				pixel_row++;
				if (not (pixel_row < height)) {
					pixel_row = 0;
					pre_rendering = false;
					displaying = true;
					rendering = true;

				}
			}
		}
		else if (rendering) {
			for (int pixel_column = 0; pixel_column < width; pixel_column++) {
				for (int pixel_row = 0; pixel_row < height; pixel_row++) {
					point_index = pixel_column + pixel_row * width;
					long double real = pixel_column * 2 * scale / width - scale + center_x;
					long double imaginary = (pixel_row * 2 * scale  / height - scale + center_y) * w_to_h_ratio;
					Complex c(real, imaginary);
					int time = itterations_to_escape(c, itterations);


					if (time != -1) {
						pixels.set_colour_by_hue(point_index, time % 360);
					}
					else {
						pixels.set_colour_to_point(point_index, 0, 0, 0);
					}
				}
			}

			rendering = false;
			displaying = true;



		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			mouse_pos = sf::Mouse::getPosition(window);
			if ((0 <= mouse_pos.x) and mouse_pos.x <= width and 0 <= mouse_pos.y and mouse_pos.y <= height) {
				center_x = mouse_pos.x * 2.f * scale / width - scale + center_x;
				center_y = mouse_pos.y * 2.f * scale / height - scale + center_y;
				scale = scale / 2;
				rendering = true;
				window.clear();
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			mouse_pos = sf::Mouse::getPosition(window);
			if ((0 <= mouse_pos.x) and mouse_pos.x <= width and 0 <= mouse_pos.y and mouse_pos.y <= height) {
				center_x = mouse_pos.x * 2.f * scale / width - scale + center_x;
				center_y = mouse_pos.y * 2.f * scale / height - scale + center_y;
				scale = scale * 2;
				rendering = true;
				window.clear();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
			itterations += 360;
			rendering = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
			itterations -= 360;
			rendering = true;
		}



	}
}



Complex mandelbrot_eq(Complex z, Complex c) {
	return z * z + c;
};

int itterations_to_escape(Complex c, int limit) {
	Complex z(0, 0);
	for (int i = 0; i < limit; i++) {
		if (z.magintude_squared() > 4) {
			return i;
		};
		z = mandelbrot_eq(z, c);
		//add_to_buddah_brot(i,limit, z);
	};
	return -1;
};

void add_to_buddah_brot(int i, int limit, Complex z) {
	if (i < limit/ 3) {

	}
}
*/
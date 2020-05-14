#include <iostream>
#include <SFML\Graphics.hpp>
#include "Complex.h"


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



Complex mandelbrot_eq(Complex z, Complex c) {
	return z.multiply(z).add(c);
};

int itterations_to_escape(Complex c, int limit) {
	Complex z(0,0);
	for (int i = 0; i < limit; i++) {
		if (z.magintude_squared() > 4) {
			return i;
		};
		z = mandelbrot_eq(z, c);
	};
	return -1;
};



struct Grid {

	sf::Uint8* points;

	Grid(int width, int height) {
		points = new sf::Uint8[width * height * 4];
	}
	void set_colour_to_point(int index, int r, int g, int b, int brightness = 255) {
		points[index * 4 ] = r;
		points[index * 4 + 1] = g;
		points[index * 4 + 2] = b;
		points[index * 4 + 3] = brightness;
	};

	void set_colour_by_hue(int index ,float hue) {
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

	int r(int index) {
		return points[index * 4];
	}
	int g(int index) {
		return points[index * 4 + 1];
	}
	int b(int index) {
		return points[index * 4 + 2];
	}

};

int main(){
	int width = 10000;
	int height = 10000;

	

	Grid pixels(width, height);

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
	while (window.isOpen()){
		sf::Event evnt;
		while (window.pollEvent(evnt)){
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
			point_index = pixel_column + pixel_row * width;
			long double real = pixel_column * 2 * scale / width - scale + center_x;
			long double imaginary = pixel_row * 2 * scale / height - scale + center_y;
			Complex c(real, imaginary);
			int time = itterations_to_escape(c, itterations);
			
		
			if (time != -1) {
				pixels.set_colour_by_hue(point_index, time % 360);
			}else{
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

		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			mouse_pos = sf::Mouse::getPosition(window);
			if ((0 <= mouse_pos.x)and mouse_pos.x <= width and 0 <= mouse_pos.y and mouse_pos.y <= height) {
				center_x = mouse_pos.x * 2.f * scale / width - scale + center_x;
				center_y = mouse_pos.y * 2.f * scale / width - scale + center_y;
				scale = scale / 2;
				rendering = true;
				window.clear();
			}
		}
		

		
		
	}
}

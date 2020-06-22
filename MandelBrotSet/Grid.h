/* Grid Object
Responsible for managing and holding a bitmap image 
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

struct Grid {

	sf::Uint8* points;

	Grid(int width, int height);

	~Grid();

	sf::Uint8* get_full();

	void set_colour_to_point(int index, int r, int g, int b, int brightness = 255);

	void set_colour_by_hue(int index, float hue);

	int r(int index);
	int g(int index);
	int b(int index);

};

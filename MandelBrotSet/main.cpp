#include <iostream>
#include <SFML\Graphics.hpp>
#include "Timer.h"
#include "Complex.h"
#include "Grid.h"
#include "MandelBrot.h"

Complex determine_new_center(sf::Vector2i mouse_pos, long double scale, Complex old_center);

bool in_window(sf::Vector2i mouse_pos);

int height = 1080;
int width = 1920;

int main() {
	
	MandelBrot mb(width, height);

	sf::RenderWindow window(sf::VideoMode(width, height), "MandelBrotSet", sf::Style::Fullscreen);

	// Object used to put the image on screen
	sf::Texture image;
	sf::Sprite sprite;
	image.create(width, height);
	sprite.setTexture(image);
	sprite.setPosition(0, 0);

	sf::Vector2i mouse_pos;

	Timer input_timer;

	window.clear();
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
			}

		}
		
		if (input_timer.has_elapsed(200)) {
			bool input = true;
			// Mouse input
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				mouse_pos = sf::Mouse::getPosition(window);
				if (in_window(mouse_pos)) {
					Complex new_center = determine_new_center(mouse_pos, mb.get_scale(), mb.get_center());
					mb.set_center(new_center);
					mb.change_scale_by(0.5);
					window.clear();
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				mouse_pos = sf::Mouse::getPosition(window);
				if (in_window(mouse_pos)) {
					Complex new_center = determine_new_center(mouse_pos, mb.get_scale(), mb.get_center());
					mb.set_center(new_center);
					mb.change_scale_by(2.0);
					window.clear();
				}

			}// Keyboard input
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
				mb.change_itterations_by(500);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
				mb.change_itterations_by(-500);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
				image.update(mb.get_buddah_brot());
				window.draw(sprite);
				window.display();
			}
			else {
				input = false;
			}
			if (input) {
				input_timer.reset();
			}
		}
		
		
		// Processes 
		if (mb.is_active()) {
			image.update(mb.feed_result_of_next_activity());
			window.draw(sprite);
			window.display();
		}
		



	}
}

Complex determine_new_center(sf::Vector2i mouse_pos, long double scale, Complex old_center) {
	Complex new_center;
	new_center.real = mouse_pos.x * 2.f * scale / width - scale + old_center.real;
	new_center.imaginary = mouse_pos.y * 2.f * scale / height - scale + old_center.imaginary;
	return new_center;

}

bool in_window(sf::Vector2i mouse_pos) {
	if (0 <= mouse_pos.x and mouse_pos.x <= width ){
		if (0 <= mouse_pos.y and mouse_pos.y <= height) {
			return true;
		}
	}
	return false;
}



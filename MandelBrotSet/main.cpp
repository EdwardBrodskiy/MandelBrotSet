#include <iostream>
#include <SFML\Graphics.hpp>
#include "Timer.h"
#include "Complex.h"
#include "Grid.h"
#include "MandelBrot.h"

std::complex<long double> mouse_pos_to_complex(sf::Vector2i mouse_pos, long double scale, std::complex<long double> old_center);

bool in_window(sf::Vector2i mouse_pos);

// window resolution
int height = 1080;
int width = 1920;

int main() {

	MandelBrot mandelBrot(width, height);

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
		
		if (input_timer.has_elapsed(100)) {
			bool input = true;
			// Mouse input
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				mouse_pos = sf::Mouse::getPosition(window);
				if (in_window(mouse_pos)) {
					std::complex<long double> new_center = mouse_pos_to_complex(mouse_pos, mandelBrot.get_scale(), mandelBrot.get_center());
					mandelBrot.set_center(new_center);
					mandelBrot.change_scale_by(0.5);
					window.clear();
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				mouse_pos = sf::Mouse::getPosition(window);
				if (in_window(mouse_pos)) {
					std::complex<long double> new_center = mouse_pos_to_complex(mouse_pos, mandelBrot.get_scale(), mandelBrot.get_center());
					mandelBrot.set_center(new_center);
					mandelBrot.change_scale_by(2.0);
					window.clear();
				}

			}// Keyboard input
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
				mandelBrot.change_itterations_by(128);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
				mandelBrot.change_itterations_by(-128);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
				image.update(mandelBrot.get_buddah_brot());
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
		if (mandelBrot.is_active()) { // check if mandel brot has a new render to display
			image.update(mandelBrot.feed_result_of_next_activity());
			window.draw(sprite);
			window.display();
		}
		



	}
}

/* convert mouse cooridnates to complex coordiante on screen */
std::complex<long double> mouse_pos_to_complex(sf::Vector2i mouse_pos, long double scale, std::complex<long double> old_center) {
	std::complex<long double> new_center;
	new_center.real(mouse_pos.x * 2.f * scale / width - scale + old_center.real());
	new_center.imag(mouse_pos.y * 2.f * scale / height - scale + old_center.imag());
	return new_center;

}

/* check if mouse position is with in the screen */
bool in_window(sf::Vector2i mouse_pos) {
	if (0 <= mouse_pos.x and mouse_pos.x <= width ){
		if (0 <= mouse_pos.y and mouse_pos.y <= height) {
			return true;
		}
	}
	return false;
}



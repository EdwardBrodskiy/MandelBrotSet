#include "MandelBrot.h"
#include <thread>

MandelBrot::MandelBrot(int width_in, int height_in) {
	width = width_in;
	height = height_in;
	w_to_h_ratio = (float)height / (float)width;
	image = new Grid(width, height);
	if (do_buddah_brot) {
		buddah_image = new Grid(width, height);
	}
	activate();
}

MandelBrot::~MandelBrot() {
	delete image;
}

sf::Uint8* MandelBrot::feed_result_of_next_activity() {
	if (pre_rendering) {
		pre_render();
		pre_rendering = false;
		rendering = true;
	} else if (rendering) {
		if (buddah_outdated) {
			clear_buddah();
		}
		render_multithread();
		active = false; // TODO: add a more dynamic system
	}
	return image->get_full();
}

sf::Uint8* MandelBrot::get_buddah_brot() {
	if (do_buddah_brot) {
		return buddah_image->get_full();
	}
	return feed_result_of_next_activity();
}

bool MandelBrot::is_active() {
	return active;
}

Complex MandelBrot::get_center() {
	return center;
}

void MandelBrot::set_center(Complex center_in) {
	center = center_in;
	activate();
}

long double MandelBrot::get_scale() {
	return scale;
}

void MandelBrot::set_scale(long double new_scale) {
	scale = new_scale;
	activate();
}

void MandelBrot::change_scale_by(long double factor) {
	set_scale(scale * factor);
}

void MandelBrot::set_itterations(int new_itterations) {
	if (new_itterations > 0) {
		itterations = new_itterations;
	}
	else {
		itterations = 0;
	}
	activate();
}

void MandelBrot::change_itterations_by(int amount) {
	set_itterations(itterations + amount);
}

void MandelBrot::activate() {
	if (not active) {
		active = true;
		if (do_buddah_brot) {
			buddah_outdated = true;
		}
		if (do_pre_render) {
			pre_rendering = true;
		}
		if (do_render) {
			rendering = true;
		}
	}
}

void MandelBrot::pre_render() {
	for (int pixel_column = 0; pixel_column < width; pixel_column++) {
		for (int pixel_row = 0; pixel_row < height; pixel_row++) {
			int point_index = pixel_column + pixel_row * width;
			Grid temp(width / 2, height / 2);

			image->set_colour_to_point(point_index, 100, 100, 100);
		}
	}
}

void MandelBrot::render() {
	for (int pixel_column = 0; pixel_column < width; pixel_column++) {
		for (int pixel_row = 0; pixel_row < height; pixel_row++) {
			int point_index = pixel_column + pixel_row * width;

			long double real = pixel_column * 2 * scale / width - scale + center.real;
			long double imaginary = (pixel_row * 2 * scale / height - scale + center.imaginary) * w_to_h_ratio;

			Complex c(real, imaginary);
			int time = itterations_to_escape(c);


			if (time != -1) {
				image->set_colour_by_hue(point_index, time % 360);
			}
			else {
				image->set_colour_to_point(point_index, 0, 0, 0);
			}
		}
	}


}

void MandelBrot::render_multithread() {
	int number_of_threads = 8;

	std::thread* threads = new std::thread[number_of_threads];

	for (int i = 0; i < number_of_threads; i++) {
		threads[i] = std::thread(&MandelBrot::render_subsection, this, i, number_of_threads);
	}

	for (int i = 0; i < number_of_threads; i++) {
		threads[i].join();
	}

}

void MandelBrot::render_subsection(int offset, int jump) {
	int pixel_row = offset;
	for (int pixel_column = 0; pixel_column < width; pixel_column++) {
		while(pixel_row < height) {
			int point_index = pixel_column + pixel_row * width;

			long double real = pixel_column * 2 * scale / width - scale + center.real;
			long double imaginary = (pixel_row * 2 * scale / height - scale + center.imaginary) * w_to_h_ratio;

			Complex c(real, imaginary);
			int time = itterations_to_escape(c);


			if (time != -1) {
				image->set_colour_by_hue(point_index, time % 360);
			}
			else {
				image->set_colour_to_point(point_index, 0, 0, 0);
			}
			pixel_row += jump;
		}
		pixel_row %= height;
	}
}



void MandelBrot::clear_buddah() {
	for (int i = 0; i < width * height; i++) {
		buddah_image->set_colour_to_point(i, 0, 0, 0);
	}
}

void MandelBrot::add_to_buddah_brot(int itteration, int index) {
	if (-1 < index and index < width * height) {
		
		int r = buddah_image->r(index);
		int g = buddah_image->g(index);
		int b = buddah_image->b(index);
		if (0) {
			if (itteration < itterations / 3) {
				if (r < 255) {
					r++;
					if (b > 0) {
						b--;
					}
				}

			}
			else if (itteration < itterations * 2 / 3) {
				if (g < 255) {
					g++;
					if (r > 0) {
						r--;
					}
				}
			}
			else {
				if (b < 255) {
					b++;
					if (g > 0) {
						g--;
					}
				}
			}
		}
		else if (1) {
			if (r < 255) {
				r++;

			}
			else if( g < 255) {
				g++;
			}
			if (not (g < 255) and (b < 255) and (r > 1)) {
				r -= 2;
				b++;
			}

		}
		
		buddah_image->set_colour_to_point(index, r, g, b);
	}
}

int MandelBrot::itterations_to_escape(Complex c) {
	Complex z(0, 0);
	
	int* stop_points;
	stop_points = new int[itterations];
	
	for (int i = 0; i < itterations; i++) {
		if (z.magintude_squared() > 4) {
			delete[] stop_points;
			return i;
		};
		z = mandelbrot_eq(z, c);
		if (do_buddah_brot) {
			stop_points[i] = complex_to_index(z);
		}
		
	};
	if (do_buddah_brot) {
		for (int i = 0; i < itterations; i++) {
			add_to_buddah_brot(i, stop_points[i]);
		}
	}
	delete[] stop_points;
	return -1;
}

Complex MandelBrot::mandelbrot_eq(Complex z, Complex c) {
	return z * z + c;
}

int MandelBrot::complex_to_index(Complex num) {
	int column = int(width / (2 * scale) * (num.real + scale - center.real));
	int row = int(height / (2 * scale) * (num.imaginary / w_to_h_ratio + scale - center.imaginary));
	return column + row * width;
}
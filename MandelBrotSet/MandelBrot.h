#pragma once
#include "Grid.h"
#include <complex>

class MandelBrot
{
public:
	bool do_render = true;
	bool do_pre_render = false;
	bool do_buddah_brot = true;
private:
	bool active = false;

	int width, height;
	float w_to_h_ratio;

	std::complex<long double> center;
	long double scale = (long double)2;
	int itterations = 128;

	Grid* image;

	Grid* buddah_image;

	bool buddah_outdated = false;
	bool pre_rendering = false;
	bool rendering = false;
public:
	MandelBrot(int width_in, int height_in);

	~MandelBrot();

	sf::Uint8* feed_result_of_next_activity();

	sf::Uint8* get_buddah_brot();

	bool is_active();

	std::complex<long double> get_center();

	void set_center(std::complex<long double> center);

	long double get_scale();

	void set_scale(long double new_scale);

	void change_scale_by(long double factor);

	void set_itterations(int new_itterations);

	void change_itterations_by(int amount);

private:
	void activate();

	void pre_render();

	void render();

	void render_multithread();

	void render_subsection(int offset, int jump);

	void clear_buddah();

	void add_to_buddah_brot(int i, int index);

	int itterations_to_escape(std::complex<long double> c);

	std::complex<long double> mandelbrot_eq(std::complex<long double> z, std::complex<long double> c);

	int complex_to_index(std::complex<long double> num);


};


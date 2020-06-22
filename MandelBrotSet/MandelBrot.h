/* MandelBrot Object
Manages the rendering of a Mandelbrot fractal as well as the Buddhabrot fractal 
*/
#pragma once
#include "Grid.h"
#include <complex>

class MandelBrot
{
public:
	// settings on what stages should be included in the rendering process
	bool do_render = true;
	bool do_pre_render = false;
	bool do_buddha_brot = true;
private:
	bool active = false; // weather there are sill renders to do from new commands

	int width, height; // resoution
	float w_to_h_ratio; // width to height ratio

	std::complex<long double> center; // what point should be at the center of the screen
	long double scale = (long double)2; // distance from the center to the vertical edge
	int itterations = 128; // number of itterations per point

	Grid* image; // where we store the render of the MandelBrot

	Grid* buddha_image; // where we store the render of the BuddhaBrot

	// basic flags
	bool buddha_outdated = false;
	bool pre_rendering = false;
	bool rendering = false;
public:
	MandelBrot(int width_in, int height_in); // initialize with resolution

	~MandelBrot();

	sf::Uint8* feed_result_of_next_activity(); // get the next render

	sf::Uint8* get_buddha_brot(); // get the buddag brot image

	bool is_active();

	std::complex<long double> get_center();

	void set_center(std::complex<long double> center);

	long double get_scale();

	void set_scale(long double new_scale);

	void change_scale_by(long double factor);

	void set_itterations(int new_itterations);

	void change_itterations_by(int amount);

private:
	void activate(); // indicate that there are processes to do

	void pre_render(); // do an aproximate render of MandelBrot

	void render(); // do a render of MandelBrot

	void render_multithread(); // do a render of MandelBrot but utilize multiple threads

	void render_subsection(int offset, int jump); // render every pixel starting at offset with gaps of jump

	void clear_buddha(); // clear the buddhaBrot image

	void add_to_buddha_brot(int i, int index); // add a trace point to buddhaBrot

	int itterations_to_escape(std::complex<long double> c); // calculates the ecape time for a point 

	std::complex<long double> mandelbrot_eq(std::complex<long double> z, std::complex<long double> c); // the mandelbrot equation function z^2 + c

	int complex_to_index(std::complex<long double> num); // convert complex number to the index in the image 


};


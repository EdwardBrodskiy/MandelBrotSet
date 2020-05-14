#pragma once
#include <chrono>


class Timer{
private:
	std::chrono::high_resolution_clock::time_point current_time, last_time;
	std::chrono::duration<double, std::milli> time_since_last_input;

public:

	Timer();

	bool has_elapsed(int millis);
	void reset();

};


#include "Timer.h"

Timer::Timer() {
	last_time = std::chrono::high_resolution_clock::now();
}

bool Timer::has_elapsed(int millis) {
	current_time = std::chrono::high_resolution_clock::now();
	time_since_last_input = current_time - last_time;
	return time_since_last_input.count() > millis;
}

void Timer::reset() {
	last_time = std::chrono::high_resolution_clock::now();
}
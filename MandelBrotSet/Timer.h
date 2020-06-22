/* Timer Object
times if a certain amount of time has passed 
*/
#pragma once
#include <chrono>


class Timer{
private:
	std::chrono::high_resolution_clock::time_point current_time, last_time;
	std::chrono::duration<double, std::milli> time_since_last_input;

public:

	Timer();

	bool has_elapsed(int millis); // checks if the amount of millis(milliseconds) has passed since last reset
	void reset(); // resets the timer

};


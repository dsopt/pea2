#pragma once
#include <chrono>
class Time
{
public:
	void start();
	void stop();
	double span();
	double spanNow();
	Time();
	~Time();
private:
	std::chrono::high_resolution_clock::time_point startV;
	std::chrono::high_resolution_clock::time_point stopV;
	double timeSpan;
};


#include "Time.h"
#include "Input.h"
#include <iostream>

using namespace std::chrono;

void Time::start() {
	startV = high_resolution_clock::now();
}

void Time::stop() {
	stopV = high_resolution_clock::now();
}

double Time::span() {
	duration<double> difference = duration_cast<duration<double>>(stopV - startV);
	timeSpan = difference.count();
	return timeSpan;
}

double Time::spanNow()
{
	duration<double> difference = duration_cast<duration<double>>(high_resolution_clock::now() - startV);
	timeSpan = difference.count();
	return timeSpan;
}


Time::Time()
{
	timeSpan = 0;
}


Time::~Time()
{
}

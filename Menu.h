#include "Input.h"
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"
#pragma once
class Menu
{
public:
	Menu(Input inp);
	~Menu();
private:
	void print();
	void options();
	char in;
	double stop;
	double a;
	int** matrix;
	Input input;
	TabuSearch ts;
	SimulatedAnnealing sa;
};

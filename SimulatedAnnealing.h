#include <vector>
#include "Time.h"
#pragma once
class SimulatedAnnealing
{
public:
	SimulatedAnnealing();
	~SimulatedAnnealing();
	void setStop(double stop_);
	double getStop();
	double geta();
	void seta(int a_);
	void run(int size_, int** matrix_);
private:
	struct move {
		int first, last;
	};
	int cost;
	int mincost;
	int max;
	int size;
	int itsince;
	int itmax;
	double maxtemp;
	double temp;
	double a;
	double e;
	double stop;
	double minfound;
	Time time;
	std::vector<int> path;
	std::vector<int> minpath;
	std::vector<move> candidates;
	std::vector<int> firstPath(int** matrix_);
	void setCandidates();
	void chooseCandidate(int** matrix_);
	int getCost(int** matrix_);
	void swap(int i, int j);
	void clear();
};


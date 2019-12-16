#include <vector>
#include "Time.h"
#pragma once
class TabuSearch
{
public:
	TabuSearch();
	~TabuSearch();
	void setStop(double stop_);
	double getStop();
	void run(int size_, int** matrix_);
private:
	struct move {
		int first, last;
	};
	int cost;
	int mincost;
	int max;
	int size;
	int itmax;
	int itsince;
	int maxtabu;
	double stop;
	double minfound;
	Time time;
	std::vector<int> path;
	std::vector<int> minpath;
	std::vector<move> tabu;
	std::vector<move> candidates;
	std::vector<int> firstPath(int** matrix_);
	std::vector<int> randomizePath();
	int contains(std::vector<move> vec, move m_);
	void setCandidates();
	void chooseCandidate(int** matrix_);
	int getCost(int** matrix_);
	void swap(int i, int j);
	void clear();
};


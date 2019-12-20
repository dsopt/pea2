#include "SimulatedAnnealing.h"
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing()
{
	time = Time();
	stop = 60.0;
	minfound = 0.0;
	tempf = 0.0;
	a = 0.9;
	max = 2147483647;
}

SimulatedAnnealing::~SimulatedAnnealing()
{
}

void SimulatedAnnealing::setStop(double stop_)
{
	stop = stop_;
}

double SimulatedAnnealing::getStop()
{
	return stop;
}

double SimulatedAnnealing::geta()
{
	return a;
}

void SimulatedAnnealing::seta(double a_)
{
	a = a_;
}

void SimulatedAnnealing::run(int size_, int** matrix_)
{
	time.start();
	size = size_;
	clear();
	itmax = 500 * size;
	maxtemp = 1000.00 * (double)size;
	temp = maxtemp;

	//path = firstPath(matrix_);
	path = randomizePath();
	cost = getCost(matrix_);
	minpath = path;
	mincost = cost;
	minfound = time.spanNow();

	setCandidates();

	while (time.spanNow() < stop) {
		//jezeli zbyt dlugo nie znajduje lepszego wyniku do poprzedniego, wykonywane jest przetasowanie
		if (itsince > itmax) {
			itsince = 0;
			temp = maxtemp / 2;
			path = randomizePath();
			cost = getCost(matrix_);
			setCandidates();
		}

		chooseCandidate(matrix_);
		itsince++;

		if (cost < mincost) {
			//lepszy wynik = nadpisywana droga
			minpath = path;
			mincost = cost;
			minfound = time.spanNow();
			itsince = 0;
			tempf = temp;
		}
		temp = temp * a;
	}

	time.stop();
	cout << "Najmniejszy koszt: " << mincost << " dla drogi: ";
	for (int k = 0; k < size; k++) {
		cout << minpath.at(k) << " ";
	}
	cout << "czas wyszukiwania: " << minfound << " s" <<" z temperatura " << tempf << endl << endl;
}

std::vector<int> SimulatedAnnealing::firstPath(int** matrix_)
{
	std::vector<int> firstpath;
	bool* visited = new bool[size];
	int minchoice, minnode, lastnode;

	firstpath.push_back(0);
	visited[0] = true;

	for (int i = 1; i < size; i++) {
		minchoice = max;
		minnode = 0;
		lastnode = firstpath.back();

		for (int j = 0; j < size; j++) {
			if (visited[j] != true) {
				if (matrix_[lastnode][j] < minchoice) {
					minchoice = matrix_[lastnode][j];
					minnode = j;
				}
			}
		}

		firstpath.push_back(minnode);
		visited[minnode] = true;
	}

	return firstpath;
}

std::vector<int> SimulatedAnnealing::randomizePath()
{
	std::vector<int> randpath;
	bool* visited = new bool[size];
	int x = 0;

	for (int i = 0; i < size; i++) {
		x = rand() % size;
		if (visited[x] != true) {
			randpath.push_back(x);
			visited[x] = true;
		}
		else {
			i--;
		}
	}

	return randpath;
}


void SimulatedAnnealing::setCandidates()
{
	candidates.clear();

	for (int i = 0; i < size - 1; i++) {
		for (int j = i; j < size; j++) {
			candidates.push_back({ path.at(i), path.at(j) });
		}
	}
}


void SimulatedAnnealing::chooseCandidate(int** matrix_)
{
	//losujemy nastepny ruch 
	int x = rand() % candidates.size();
	move m = candidates.at(x);

	swap(m.first, m.last);
	int tempcost = getCost(matrix_);
	double c = (double)(rand() % 1000001) / 1000000.00;
	double b = (double)exp((((double)cost - (double)tempcost)) / temp);

	//wybieramy nowa sciezke jezeli koszt jest mniejszy lub spelnia rownanie i losujemy dla niej sasiedztwo
	//w przeciwnym wypadku cofamy sie
	if (tempcost < cost || c < b) {
		cost = tempcost;
		setCandidates();
	}
	else {
		swap(m.last, m.first);
	}
}

int SimulatedAnnealing::getCost(int** matrix_)
{
	int thiscost = 0;

	for (int i = 0; i < size - 1; i++) {
		thiscost += matrix_[path.at(i)][path.at(i + 1)];
	}
	thiscost += matrix_[path.at(size - 1)][path.at(0)];

	return thiscost;
}

void SimulatedAnnealing::swap(int i, int j)
{
	int x = distance(path.begin(), find(path.begin(), path.end(), i));
	int y = distance(path.begin(), find(path.begin(), path.end(), j));

	path.at(x) = j;
	path.at(y) = i;
}

void SimulatedAnnealing::clear()
{
	cost = 0;
	mincost = max;
	itsince = 0;
	path.clear();
	minpath.clear();
	candidates.clear();
}

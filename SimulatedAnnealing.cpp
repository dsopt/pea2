#include "SimulatedAnnealing.h"
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing()
{
	time = Time();
	stop = 50.0;
	minfound = 0.0;
	maxtemp = 500000;
	a = 0.9;
	e = 2,718281828459;
	max = 2147483647;
	clear();
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

void SimulatedAnnealing::seta(int a_)
{
	a = a_;
}

void SimulatedAnnealing::run(int size_, int** matrix_)
{
	time.start();
	size = size_;
	clear();
	itmax = 10 * size;
	temp = maxtemp;

	path = firstPath(matrix_);
	cost = getCost(matrix_);
	minpath = path;
	mincost = cost;
	minfound = time.spanNow();

	setCandidates();

	while (time.spanNow() < stop) {
		//jezeli zbyt dlugo nie znajduje lepszego wyniku do poprzedniego, wykonywane jest przetasowanie
		if (itsince > itmax) {
			itsince = 0;
			randomizePath();
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
		}
		temp = temp * a;
	}

	time.stop();
	cout << "Najmniejszy koszt: " << mincost << " dla drogi: ";
	for (int k = 0; k < size; k++) {
		cout << minpath.at(k) << " ";
	}
	cout << "czas wyszukiwania: " << minfound << " s" << endl << endl;
}

std::vector<int> SimulatedAnnealing::firstPath(int** matrix_)
{
	std::vector<int> randpath;
	bool* visited = new bool[size];
	int minchoice, minnode, lastnode;

	randpath.push_back(0);
	visited[0] = true;

	for (int i = 1; i < size; i++) {
		minchoice = max;
		minnode = 0;
		lastnode = randpath.back();

		for (int j = 0; j < size; j++) {
			if (visited[j] != true) {
				if (matrix_[lastnode][j] < minchoice) {
					minchoice = matrix_[lastnode][j];
					minnode = j;
				}
			}
		}

		randpath.push_back(minnode);
		visited[minnode] = true;
	}

	return randpath;
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
		candidates.push_back({ path.at(i), path.at(i + 1) });
	}
	candidates.push_back({ path.at(size - 1), path.at(0) });
}


void SimulatedAnnealing::chooseCandidate(int** matrix_)
{
	//losujemy nastepny ruch i usuwamy go z listy kandydatow
	int x = rand() % candidates.size();
	move m = candidates.at(x);

	swap(m.first, m.last);
	int tempcost = getCost(matrix_);
	double c = (rand() % 101) / 100;
	double b = (cost - tempcost) / temp;

	//wybieramy nowa sciezke jezeli koszt jest mniejszy lub spelnia rownanie i losujemy dla niej sasiedztwo
	//w przeciwnym wypadku cofamy sie
	if (tempcost < cost || c < pow(e, b)) {
		cost = tempcost;
		setCandidates();
	}
	else {
		swap(m.last, m.first);
		cost = getCost(matrix_);
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
	path.at(distance(path.begin(), find(path.begin(), path.end(), i))) = j;
	path.at(distance(path.begin(), find(path.begin(), path.end(), j))) = i;
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

#include "TabuSearch.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

TabuSearch::TabuSearch()
{
	time = Time();
	stop = 50.0;
	minfound = 0.0;
	max = 2147483647;
	clear();
}

TabuSearch::~TabuSearch()
{
}

void TabuSearch::setStop(double stop_)
{
	stop = stop_;
}


double TabuSearch::getStop()
{
	return stop;
}

void TabuSearch::run(int size_, int** matrix_)
{
	time.start();
	size = size_;
	clear();
	maxtabu = 2 * size;
	itmax = 10 * size;

	//generowanie poczatkowej drogi
	path = firstPath(matrix_);
	cost = getCost(matrix_);
	minpath = path;
	mincost = cost;
	minfound = time.spanNow();


	while(time.spanNow() < stop){
		//petla wykonywana dopoki czas nie przekracza limitu czasowego

		if (itsince > itmax) {
			path = randomizePath();
			cost = getCost(matrix_);
			itsince = 0;
		}

		itsince++;
		setCandidates();
		chooseCandidate(matrix_);

		if (cost < mincost) {
			//lepszy wynik = nadpisywana droga
			minpath = path;
			mincost = cost;
			minfound = time.spanNow();
			itsince = 0;
		}
	}

	time.stop();
	cout << "Najmniejszy koszt: " << mincost << " dla drogi: ";
	for (int k = 0; k < size; k++) {
		cout << minpath.at(k) << " ";
	}
	cout << "czas wyszukiwania: " << minfound << " s" << endl << endl;
}

std::vector<int> TabuSearch::firstPath(int** matrix_)
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

std::vector<int> TabuSearch::randomizePath()
{
	tabu.clear();
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

int TabuSearch::contains(std::vector<move> vec, move m_)
{
	//sprawdza, czy ruch jest na liscie, zwraca indeks lub -1
	for (int i = 0; i < vec.size(); i++) {
		if (vec.at(i).first == m_.first && vec.at(i).last == m_.last) {
			return i;
		}
	}
	return -1;
}

void TabuSearch::setCandidates()
{
	candidates.clear();

	for (int i = 0; i < size - 1; i++) {
		candidates.push_back({path.at(i), path.at(i+1)});
	}
	candidates.push_back({path.at(size - 1), path.at(0)});
}


void TabuSearch::chooseCandidate(int** matrix_)
{
	//obliczenie najlepszego ruchu z mozliwych
	vector<int> bestpath;
	int bestcost = max;
	move m;

	for (int i = 0; i < (int)candidates.size(); i++) {
		if (contains(tabu, candidates.at(i)) == -1) {
			swap(candidates.at(i).first, candidates.at(i).last);
			if (getCost(matrix_) < bestcost) {
				bestcost = getCost(matrix_);
				bestpath = path;
				m = { candidates.at(i).last, candidates.at(i).first };
			}
			swap(candidates.at(i).last, candidates.at(i).first);
		}
		else {
			swap(candidates.at(i).first, candidates.at(i).last);
			if (getCost(matrix_) < mincost) {
				tabu.erase(tabu.begin() + contains(tabu, candidates.at(i)));
				bestcost = getCost(matrix_);
				bestpath = path;
				m = { candidates.at(i).last, candidates.at(i).first };
			}
			swap(candidates.at(i).last, candidates.at(i).first);
		}
		
	}

	path = bestpath;
	cost = bestcost;
	tabu.push_back(m);
	if ((int)tabu.size() > maxtabu) {
		tabu.erase(tabu.begin());
	}
}

int TabuSearch::getCost(int** matrix_)
{
	int thiscost = 0;

	for (int i = 0; i < size - 1; i++) {
		thiscost += matrix_[path.at(i)][path.at(i + 1)];
	}
	thiscost += matrix_[path.at(size - 1)][path.at(0)];

	return thiscost;
}

void TabuSearch::swap(int i, int j)
{
	path.at(distance(path.begin(), find(path.begin(), path.end(), i))) = j;
	path.at(distance(path.begin(), find(path.begin(), path.end(), j))) = i;
}

void TabuSearch::clear()
{
	itsince = 0;
	cost = 0;
	mincost = max;
	path.clear();
	minpath.clear();
	tabu.clear();
	candidates.clear();
}

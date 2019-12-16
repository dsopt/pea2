#include "Menu.h"
#include "Input.h"
#include "Time.h"
#include <iostream>

using namespace std;

Menu::Menu(Input inp_)
{
	input = inp_;
	//
	matrix = input.fromFile();
	//
	ts = TabuSearch();
	sa = SimulatedAnnealing();
	options();
}

Menu::~Menu()
{
}

void Menu::options()
{
	cout << endl;
	cout << "Co chcesz zrobic?\n[1] - wczytaj dane z pliku\n[2] - wyswietl dane\n[3] - tabu search\n[4] - symulowanie wyzarzanie\n[5] - zmien kryterium stopu\n[6] - zmien wspolczynnik zmiany temperatury\n[9] - wyjdz" << endl;
	cin >> in;
	cout << endl;

	switch (in) {
	case '1':
		matrix = input.fromFile();
		options();
		break;
	case '2':
		print();
		options();
		break;
	case '3':
		ts.run(input.getSize(), matrix);
		options();
		break;
	case '4':
		sa.run(input.getSize(), matrix);
		options();
		break;
	case '5':
		cout << "Kryterium stopu wynosi " << ts.getStop() << "s. Podaj wartosc w sekundach, jaka chcesz ustawic:" << endl;
		cin >> stop;
		ts.setStop(stop);
		sa.setStop(stop);
		options();
		break;
	case '6':
		cout << "Wspolczynnik zmiany temperatury wynosi " << sa.geta() << ". Podaj wartosc, jaka chcesz ustawic:" << endl;
		cin >> a;
		sa.seta(a);
		options();
		break;
	case '9':
		break;
	default:
		cout << "Nie ma takiej operacji" << endl << endl;
		options();
		break;
	}
}

void Menu::print() {
	for (int i = 0; i < input.getSize(); i++) {
		for (int j = 0; j < input.getSize(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

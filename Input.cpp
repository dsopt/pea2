#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Input.h"
#pragma once
using namespace std;


Input::Input(string path_) {
	size = 0;
	path = path_;
}
Input::Input()
{
}
Input::~Input() {

}



int** Input::fromFile() {
	//czytanie danych z pliku
	ifstream file(path.c_str());

	if (path.find(".txt") != string::npos) {
		if (file) {
			file >> line;
			file >> size;
			matrix_ = new int* [size];

			for (int i = 0; i < size; i++) {
				matrix_[i] = new int[size];

				for (int j = 0; j < size; j++) {
					file >> matrix_[i][j];
				}
			}

		}
	}
	else {
		while (file) {
			getline(file, line);

			if (line == "EOF" || line == "DISPLAY_DATA_SECTION") {
				break;
			}
			else if (line == "EDGE_WEIGHT_SECTION") {
				matrix_ = new int* [size];

				for (int i = 0; i < size; i++) {
					matrix_[i] = new int[size];

					for (int j = 0; j < size; j++) {
						file >> matrix_[i][j];
					}
				}
			}
			else {
				stringstream ss{ line };
				string x;
				ss >> x;
				if (x == "DIMENSION:") {
					ss >> size;
				}
			}
		}
	};
	file.close();
	cout << "Dane zostaly wczytane" << endl;
	return matrix_;

}

int Input::getSize()
{
	return size;
}

#include <string>
#pragma once
class Input {
public:
	int** fromFile();
	int getSize();
	Input(std::string path_);
	Input();
	~Input();
private:
	int size;
	int** matrix_;
	std::string path;
	std::string line;
};
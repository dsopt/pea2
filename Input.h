#include <string>
#pragma once
class Input {
public:
	int** fromFile();
	int getSize();
	void setPath(std::string path_);
	std::string getPath();
	Input(std::string path_);
	Input();
	~Input();
private:
	int size;
	int** matrix_;
	std::string path;
	std::string line;
};
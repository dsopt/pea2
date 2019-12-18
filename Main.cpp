#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

int main() {
	srand(time(NULL));
	Input inp = Input("./data/data17.txt");
	Menu m = Menu(inp);
	_getch();
	return 0;

}
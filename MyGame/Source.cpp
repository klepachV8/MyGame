#include <iostream>
#include <windows.h>
using namespace std;

const int X = 10;
const int Y = 8;

struct Player {
	char show;
	short team;

};
Player *** field;


void constructor() {
	field = new Player**[X];
	for (size_t i = 0; i < X; i++)
	{
		field[i] = new Player*[Y];

		//memset(field[i], 0, sizeof(Player) * Y);
		for (size_t j = 0; j < Y; j++)
		{
			field[i][j] = NULL;
		}
	}
}

void destructor() {
	for (int i = 0; i < X; i++)
	{
		delete []field[i];
	}
	delete field;
}

void main() {
	cout << "Hello World"<<endl;

	system("pause");
}
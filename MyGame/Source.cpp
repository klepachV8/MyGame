#include <iostream>
#include <windows.h>
#include "Source.h"
using namespace std;

const int X = 10;
const int Y = 8;



struct Point {
	int x;
	int y;
};

struct Player {
	char show;
	short team;
	void(*movement)(Point);
};
struct Data {
	Point * position;
	Player * gamer;
};
Player *** field;


Point * findBall() {
	for (size_t i = 0; i < X; i++)
	{
		for (size_t j = 0; j < Y; j++)
		{
			if (field[i][j] != NULL && field[i][j]->team == 0)
			{
				auto p = new Point();
				p->x = i;
				p->y = j;
				return p;
			}
		}
	}
}

void moveHunter(Point curentPosition) {

	Point * ball = findBall();
	if (abs(curentPosition.x - (long)ball->x) >= abs(curentPosition.y - (long)ball->y))
	{
		auto newPos = curentPosition.x > ball->x ? curentPosition.x -1 : curentPosition.x +1;
		swap(field[curentPosition.x][curentPosition.y],
			field[newPos][curentPosition.y]);
	}
	else
	{
		auto newPos = curentPosition.y > ball->y ? curentPosition.y - 1 : curentPosition.y + 1;
		swap(field[curentPosition.x][curentPosition.y],
			field[curentPosition.x][newPos]);
	}
			
}

void moveDefender(Point curentPosition) {

}

void initPlayers() {
	field[0][4] = new Player();
	field[0][4]->show = 'o';
	field[0][4]->team= -1;
	field[0][4]->movement = moveDefender;

	field[1][5] = new Player();
	field[1][5]->show = '0';
	field[1][5]->team = -1;
	field[1][5]->movement = moveHunter;

	field[7][6] = new Player();
	field[7][6]->show = '#';
	field[7][6]->team = 1;
	field[7][6]->movement = moveHunter;

	field[8][6] = new Player();
	field[8][6]->show = '$';
	field[8][6]->team = 1;
	field[8][6]->movement = moveDefender;

	field[X/2][Y/2] = new Player();
	field[X/2][Y/2]->show = 'B';
	field[X/2][Y/2]->team = 0;
	field[X / 2][Y / 2]->movement = NULL;

}

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
	initPlayers();
}

void destructor() {
	for (int i = 0; i < X; i++)
	{
		delete []field[i];
	}
	delete field;
}

void show() {
	for (size_t i = 0; i < X; i++)
	{
		for (size_t j = 0; j < Y; j++)
		{
			if (field[i][j] == NULL)
			{
				cout << " ";
			}
			else
			{
				cout << field[i][j]->show;
			}
		}
		cout << endl;
	}
}

void moveAllPlayers() {
	Data * data = new Data[X*Y];
	int count = 0;
	for (size_t i = 0; i < X; i++)
	{
		for (size_t j = 0; j < Y; j++)
		{
			if (field[i][j] != NULL &&  field[i][j]->team != 0)
			{
				Point * p = new Point();
				p->x = i;
				p->y = j;

				data[count].position = p;
				data[count++].gamer = field[i][j];
			}
		}
		cout << endl;
	}

	for (int i = 0; i < count; i++)
	{
		data[i].gamer->movement(*data[i].position);
	}

	//field[i][j]->movement(*p);

}

void main() {
	constructor();
	show();
	cout << "------------\n";
	moveAllPlayers();
	show();
	destructor();
	system("pause");
}
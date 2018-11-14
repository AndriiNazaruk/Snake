#include<iostream>
#include<Windows.h>
#include<ctime>
#include<fstream>
#include<conio.h>
#include<string>
const int NotUsed = system("color 8E");
using namespace std;
bool Finish;
const int visota = 20;
const int shirota = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
void setup()
{
	Finish = false;
	dir = STOP;
	x = visota / 2 - 1;
	y = shirota / 2 - 1;
	fruitX = 0 + rand() % 20;
	fruitY = 0 + rand() % 20;
	score = 0;
}
void map()
{
	system("cls");
	for (int i = 0; i < visota + 1; i++)
		cout << "&";
	cout << endl;

	for (int i = 0; i < shirota; i++)
	{
		for (int j = 0; j < visota; j++)
		{
			if (j == 0 || j == visota - 1)

				cout << "|";
			if (i == y && j == x)
				cout << "#";
			else if (i == fruitY && j == fruitX)
				cout << "$";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "*";
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}


	for (int i = 0; i < visota + 1; i++)
		cout << "&";
	cout << endl;
	cout << "Score :" << score << endl;

}
void vvod()
{
	if (_kbhit())
		switch (_getch())
		{
		case 'd':
			dir = LEFT;
			break;
		case 'g':
			dir = RIGHT;
			break;
		case 'r':
			dir = UP;
			break;
		case 'f':
			dir = DOWN;
			break;
		case '`':
			Finish = true;
		}
}
void settings()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	if (x >= visota - 1)
		x = 0;
	else if (x < 0)
		x = visota - 2;
	if (y > shirota)
		y = 0;
	else if (y < 0)
		y = shirota - 1;
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			Finish = true;
	}


	if (x == fruitX && y == fruitY)
	{
		score += 100;
		fruitX = 0 + rand() % 20;
		fruitY = 0 + rand() % 20;
		nTail++;
	}
}
int main()
{
	int choice;
	while (true)
	{
		cout << "------------Snake-------------" << endl;
		cout << "1.New Game " << endl;
		cout << "2.Record " << endl;
		cout << "3.Exit " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			setup();
			while (!Finish)
			{
				Sleep(300);
				map();
				vvod();
				settings();
			}
			ofstream fout;
			string name;
			cout << "Enter name: ";
			cin >> name;
			fout.open("Score.txt", ios_base::app);
			fout << "Name: " << name << "\tScore:" << score << endl;
			fout.close();

			break;
		}

		case 2:
		{
			ifstream fin;
			fin.open("Score.txt");
			char ch;
			while (fin.get(ch))
			{
				cout << ch;
			}
			cout << "Your score :" << score << endl;
			cout << "Enter any key to return main menu :" << endl;
			_getch();
			break;
		}
		case 3:
		{
			cout << "Good buy !" << endl;
			Sleep(1000);
			system("cls");
			return 0;
		}
		}
	}
	system("pause");
}

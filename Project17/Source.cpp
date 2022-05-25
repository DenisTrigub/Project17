#include <iostream>
#include<conio.h>
using namespace std;

char board[9] = { '-','-', '-', '-', '-', '-', '-', '-', '-' };//массив поля

bool has_won(char player)//условие выигрыша
{
	int wins[][3] = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
	for (int i = 0; i < 8; i++)
	{
		int count = 0;
		for (int j = 0; j <= 2; j++)
		{
			if (board[wins[i][j]] == player)
				count++;
			if (count == 3)
				return true;
		}
	}
	return false;
}

void print_board()//вывод поля
{
	cout << "Игровое поле\n";
	
	
	cout << "|-" << board[0] << "-|-" << board[1] << "-|-" << board[2] << "-|\n";
	cout << "|-" << board[3] << "-|-" << board[4] << "-|-" << board[5] << "-|\n";
	cout << "|-" << board[6] << "-|-" << board[7] << "-|-" << board[8] << "-|\n";
	
		cout << "ваш ход :\n";
}

int get_move()
{
	system("cls");
	setlocale(0,"");
	
	cout << "Управление\n";
	cout << "|-1-|-2-|-3-|\n";
	cout << "|-4-|-5-|-6-|\n";
	cout << "|-7-|-8-|-9-|\n";
	cout << endl;

	print_board();

	int move;
	cin >> move;
	while (move > 9 || move < 1 || board[move - 1] != '-') //проверка введённого числа
	{
		cout << "Ведите правильное число (1-9)\n";
		cin >> move;
	}
	return move;

}

char play()//игра и проверка комбинаций
{

	int turn = 0;
	while (!has_won('X') && !has_won('O') && turn < 9)
	{
		int move = get_move();
		if (turn % 2 == 0)
		{
			board[move - 1] = 'X';
			if (has_won('X'))
			{
				cout << "Выиграл игрок 'X'!\n";
				return 'X';
			}
		}
		else
		{
			board[move - 1] = 'O';
			if (has_won('O'))
			{
				cout << "Выиграл игрок 'O'!\n";
				return 'O';
			}
		}

		turn++;
	}
	cout << "Ничья :(\n";
	return 'D';
}

//---------------------------------------------------------------------------------------
bool gameOver;
const int width = 50;
const int heigth = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = heigth / 2;
	fruitX = rand() % width;
	fruitY = rand() % heigth;
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;



	for (int i = 0; i < heigth; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}

				}
				if (!print)
					cout << " ";
			}

		}
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	cout << "Scotre :" << score << endl;

}

void Input()
{
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
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
	//if (x > width || x < 0 || y > heigth || y < 0)
	//	gameOver = true;

	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= heigth)
		y = 0;
	else if (y < 0)
		y = heigth - 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == fruitX && y == fruitY)
	{
		score += 1;
		fruitX = rand() % width;
		fruitY = rand() % heigth;
		nTail++;
	}
}

int main()
{
	setlocale(0, "");
	int S = 2;
	cout << "выбери игру\n 1 - крестики-нолики\n 2 - змейка";
	cin >> S;
	switch (S)
	{
	case 1:
	{
		system("Title TicTacToe");
		system("color 2");

		play();
		int a;
		cin >> a;
		
	}break;
	case 2:
	{
		Setup();
		while (!gameOver)
		{
			Draw();
			Input();
			Logic();
		}
	}break;
	}
	return 0;
}
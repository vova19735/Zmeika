#include <iostream>
#include<conio.h>
#include<ctime>
using namespace std;
bool gameOver;

int x, y, fruit_x, fruit_y, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection{ STOP = 0,LEFT,RIGHT,UP,DOWN };
eDirection dir;
void Input() {
	if (_kbhit()) 
	{
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
		case 'v':
			gameOver = true;
			break;
		}
	}
}

void Logic(int width, int height, int mode_1) {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1;i < nTail;i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {
	case LEFT:
		x--;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	}
	if (mode_1 == 1) {
		if (x > width || x<0 || y>height || y < 0) {
			gameOver = true;
		}
	}
	if (mode_1 == 2) {
		if (x >= width - 1) {
			x = 0;
		}
		else if (x < 0) {
			x = width - 2;
		}
		if (y >= height) {
			y = 0;
		}
		else if (y < 0) {
			y = height - 1;
		}
	}
	for (int i = 0;i < nTail;i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
	if (x == fruit_x && y == fruit_y) {
		score += 10;
		fruit_x = rand() % width;  //ширина
		fruit_y = rand() % height; //высота
		nTail++;
	}
}

void Setup(int width, int height)
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruit_x = rand() % width;  //ширина
	fruit_y = rand() % height; //высота
	score = 0;
}

void Draw(int width, int height)
{
	system("cls");
	for (int i = 0;i < width + 2;i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0;i < height;i++)
	{
		for (int j = 0;j < width+1;j++) 
		{
			if (j == 0 || j == width)
			{
				cout << "#";
			}
			if (i == y && j == x) {
				cout << "0";
			}
			else if (i == fruit_y && j == fruit_x) {
				cout << "F";
			}
			else{
				bool print = false;
				for (int k = 0;k < nTail;k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if(!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	
	for (int i = 0;i < width + 2;i++)
	{
		cout << "#";
		
	}
	cout << endl;
	cout << "\tРезультат: " << score << endl;
}

int main()
{
	srand(time(NULL));
	
	int width = 20;
	int height = 20;
	setlocale(LC_ALL, "ru");

	Setup(width, height);
	int menu_1;
	int mode_1 = 1;
	menu: //goto menu
	cout << "\tИгра змейка :)\n";
	cout << "1 - Начать игру\n";
	cout << "2 - Настройки\n";
	//cout << "3 - ";
	//cout << "4 - ";
	//cout << "5 - ";
	cout << "Ваш выбор: ";
	cin >> menu_1;
	if (menu_1==1) 
	{
		system("cls");
		while (!gameOver)
		{
			Draw(width, height);
			Input();
			Logic(width, height, mode_1);
		}
	}
	else if (menu_1 == 2) 
	{
		int menu_2;
		setting:       //goto setting
		system("cls");
		cout << "Настройки: \n";
		cout << "1 - Изменить размер поля для игры\n";
		cout << "2 - Изменить режим игры\n";
		cout << "3 - Выход в главное меню\n";
		cout << "Ваш выбор: ";
		cin >> menu_2;
		int q;
		if (menu_2 == 1) {
			system("cls");
			cout << "Настройки размера поля: \n";
			cout << "Введите размер поля: ";
			cin >> width;
			height = width;
			cout << "\n\n\tУстновлены новые размеры поля: " << width << " x" << height;
			cout << "\nДля выхода в настройки нажмите '5'.";
			cin >> q;
			if (q == 5) {
				goto setting;
			}
		}
		if (menu_2 == 2) {
			system("cls");
			cout << "Настройки режима игры: \n";
			cout << "1 - режим игры классический\n";
			cout << "2 - режим игры с проходом через стены\n";
			cout << "Ваш выбор: ";
			cin >> mode_1;
			switch (mode_1) {
			case 1: cout << "\nВыбран режим игры классический";
				break;
			case 2: cout << "\nВыбран режим иры с проходом через стены";
				break;
			}
			cout << "\nДля выхода в настройки нажмите '5'.";
			cin >> q;
			if (q == 5) {
				goto setting;
			}
		}
		if (menu_2 == 3) {
			system("cls");
			goto menu;
		}
	}
						
	
	return 0;
}
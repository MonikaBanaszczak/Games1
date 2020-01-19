#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>   //potrzebna do sleep() i gotoxy()


using namespace std;

int width, height;
int speed;
int up, down, left_, right_;
char square[35][35];
int x_snake, y_snake;
int x_food, y_food;
int length = 3, x_story[10000], y_story[10000];
int how_many = 0;
int button;
char course='r'; //r = prawo; l = lewo; u = gora; d = dol
char snake = 219, food = 177, rd = 188, ru = 187, lu = 201, ld = 200, horizontal = 205, upright = 186;


//dzieki temu ekran nie miga

void gotoxy(int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}


int choose_size(int &size_p)
{
	cout << "Podales zla liczbe! Sprobuj jeszcze raz." << endl;
	cin >> size_p;
	if (size_p < 5 || size_p > 35)
	{
		cout << "Automatyczny wybor rozmiaru." << endl;
		size_p = 15;
		cout << size_p;
		return 0;
	}
}

int main()
{
	cout << "GRA SNAKE!!!" << endl << endl;
	cout << "Podaj szerokosc i wysokosc planszy z przedzialu od 5 do 35" << endl;
	cout << "Szerokosc: ";
	cin >> width;
	if (width < 5 || width > 35)
		choose_size(width);

	cout << endl << "Wysokosc: ";
	cin >> height;
	if (height < 5 || height > 35)
		choose_size(height);

	//cout << width << " " << height << endl;
		
	cout << "Podaj szybkosc (od 1 do 10): " << endl;
	cin >> speed;
	if (speed < 1)
	{
		cout << "Szybkosc minimalna = 1" << endl;
		speed = 1;
	}
	else if (speed > 10)
	{
		cout << "Szybkosc maksymalna = 10" << endl;
		speed = 10;
	}

	cout << "Podaj jakimi klawiszami chcesz zagrac." << endl;
	cout << "GORA" << endl;
	up = _getch();
	if (up == 224)
		up = up + _getch();
	else if (up == 0)
		up = up - _getch();

	cout << "DOL" << endl;
	down = _getch();
	if (down == 224)
		down = down + _getch();
	else if (down == 0)
		down = down - _getch();

	cout << "PRAWO" << endl;
	right_ = _getch();
	if (right_ == 224)
		right_ = right_ + _getch();
	else if (right_ == 0)
		right_ = right_ - _getch();

	cout << "LEWO" << endl;
	left_ = _getch();
	if (left_ == 224)
		left_ = left_ + _getch();
	else if (left_ == 0)
		left_ = left_ - _getch();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			square[j][i] = 'p';
		}
	}
	srand(time(NULL));
	//losowanie pola dla weza

	x_snake = rand() % width;
	y_snake = rand() % height;

	square[x_snake][y_snake] = 'w';

	//losowanie pola dla jedzenia

	do 
	{
		x_food = rand() % width;
		y_food = rand() % height;
	} while (square[x_food][y_food] != 'p');
	
	square[x_food][y_food] = 'j';

	system("cls");

	//RYSUJEMY PLANSZE
	gotoxy(0, 0); //wroc na poczatek 

	//gorna ramka
	cout << lu;
	for (int i = 0; i < width; i++)
	{
		cout << horizontal << horizontal;
	}
	cout << ru;

	//boki ramki

	for (int i = 0; i < height; i++)
	{
		cout << endl << upright; //lewa ramka
		for (int j = 0; j < width; j++)
		{
			if (square[j][i] == 'p')
			{
				cout << "  ";
			}
			else if (square[j][i] == 'w')
			{
				cout << snake << snake;
			}
			else if (square[j][i] == 'j')
			{
				cout << food << food;
			}

		}
		cout << upright; //prawa ramka
	}
	cout << endl;
	// dolna ramka
	cout << ld;
	for (int i = 0; i < width; i++)
	{
		cout << horizontal << horizontal;
	}
	cout << rd;


	//poczatek gry
	for (;;)
	{
		how_many++;
		x_story[how_many] = x_snake;
		y_story[how_many] = y_snake;

		Sleep(1000 / speed);

		if (_kbhit())  //jesli zostanie nacisniety klawisz wykona sie instrukcja
		{
			button = _getch();
			if (button == 224)
				button += _getch();

			else if (button == 0)
				button -= _getch();

			if (button == up && (course == 'l' || course == 'r'))
				course = 'u';
			if (button == down && (course == 'l' || course == 'r'))
				course = 'd';
			if (button == left_ && (course == 'u' || course == 'd'))
				course = 'l';
			if (button == right_ && (course == 'u' || course == 'd'))
				course = 'r';

		}

		
		if(course == 'u') 
			y_snake--;
		if (course == 'd')
			y_snake++;
		if (course == 'r')
			x_snake++;
		if (course == 'l')
			x_snake--;


		//waz przechodzi przez sciany
		if (x_snake == width)
		{
			x_snake = 0;
		}
		else if (x_snake == -1)
		{
			x_snake = width - 1;
		}

		if (y_snake == height)
		{
			y_snake = 0;
		}
		else if (y_snake == -1)
		{
			y_snake = height - 1;
		}

		//co jesli zje siebie
		if (square[x_snake][y_snake] == 'w')
		{
			gotoxy(0, length + 4);
			cout <<endl<<endl<< "Koniec gry!" << endl << "Wynik: " << length + 1;
			break;
		}

		//po zjedzeniu jedzenie
		if (square[x_snake][y_snake] == 'j')
		{
			length++;

			//losowanie pola dla jedzenia
			do
			{
				x_food = rand() % width;
				y_food = rand() % height;
			} while (square[x_food][y_food] != 'p');

			square[x_food][y_food] = 'j';
			gotoxy((x_food * 2) + 1, y_food + 1);
			cout << food << food;
		}
		else
		{
			//kasowanie ogona
			square[x_story[how_many - length]][y_story[how_many - length]] = 'p';
			gotoxy((x_story[how_many - length] * 2) + 1, y_story[how_many - length] + 1);
			cout << "  ";
		}
		
		square[x_snake][y_snake] = 'w';
		gotoxy((x_snake * 2) + 1, y_snake + 1);
		cout << snake << snake;
	}
	 
	_getch();

	return 0;
}
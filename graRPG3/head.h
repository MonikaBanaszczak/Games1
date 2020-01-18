#include<iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <time.h>

using namespace std;

bool player_smierc = false;
bool walka;
int command;

string ruch;

int hp, dmg, fhp, fdmg;
float Exp = 0, nexp = 100;
int lvl = 1;

int ehp, edmg, fedmg;

//pozycja gracza na mapie
int x = 2, y = 2;

//Kolekcja voidow

void menu();
void gra();
void map();
void stats();
void input();
void logic();
void klasa();
void fight();
void wolf();

//Kolekcja voidow

void menu()
{
	system("cls");
	cout << "Witaj w grze RPG!!!" << endl << endl;
	cout << "1. Start Gry!" << endl;
	cout << "2. Wyjscie z gry" << endl;
	cin >> command;

	switch (command)
	{
	case 1:
	{
		klasa();
	} break;
	case 2:
	{
		cout << "Gra zostanie wylaczona!"; Sleep(1500);
		exit(0);
	} break;
	default:
	{
		cout << "Nie ma takiej opcji!" << endl; Sleep(1500);
		menu();
	}break;
	}
}

void klasa()
{
	system("cls");
	cout << "Wybierz klase postaci!" << endl << endl;
	cout << "1. Wojownik" << endl;
	cout << "2. Lowca" << endl;
	cout << "3. Mag" << endl;
	cin >> command;

	switch (command)
	{
	case 1:
	{
		hp = 30; //zdrowie
		dmg = 5; //obrazenia
		gra();
	} break;
	case 2:
	{
		hp = 23;
		dmg = 8;
		gra();
	} break;
	case 3:
	{
		hp = 15;
		dmg = 13;
		gra();
	} break;
	default:
	{
		cout << "Nie ma takiej klasy." << endl; Sleep(1500);
		klasa();
	} break;
	}
}

void gra()
{
	system("cls");
	map();
	stats();
	input();
	logic();

}

void map()
{
	system("cls");
	if (x == 2 && y == 2)
	{
		cout<<"Torun!"<<endl;
		cout << "Uwazaj! Wilk!" << endl << "Wpisz 'walka' by go pokonac!" << endl;
	}

	if (x == 1 && y == 1)
	{
		cout << "Warszawa!" << endl;
		cout << "Uwazaj! Wilk!" << endl << "Wpisz 'walka' by go pokonac!" << endl;
	}

	if (x == 2 && y == 1)
	{
		cout << "Plonsk!" << endl;
		cout << "Uwazaj! Wilk!" << endl << "Wpisz 'walka' by go pokonac!" << endl;
	}

	if (x == 1 && y == 2)
	{
		cout << "Plock!" << endl;
		cout << "Uwazaj! Wilk!" << endl << "Wpisz 'walka' by go pokonac!" << endl;
	}
}

void stats()
{
	cout << ">> Pozycja gracza na mapie: X:" << x << " Y: " << y <<" <<"<<endl;
	cout << ">> HP:" << hp <<" DMG:"<<dmg<<" LVL:"<<lvl<<" Exp:" <<Exp<<"/" <<nexp<<" <<"<< endl;
}

void input()
{
	cin >> ruch;

	if (ruch == "w")
	{
		y++;
	}

	else if (ruch == "s")
	{
		y--;
	}

	else if (ruch == "a")
	{
		x--;
	}

	else if (ruch == "d")
	{
		x++;
	}
	else if (ruch == "walka")
	{
		wolf();
		fight();
	}
	else
	{
		cout << "Nie ma takiego polecenia!" << endl; Sleep(1500);
		gra();
	}
}

void logic()
{
	if (Exp >= nexp)
	{
		Exp = 0;
		lvl++;
		hp += 3;
		dmg += 2;
		nexp = nexp * 1.15;
	}
}

void fight()
{
	cout << "Rozpoczyna sie walka!" << endl; Sleep(1500);
	fhp = hp;

	while (ehp >= 1 && fhp >= 1)
	{
		system ("cls");
		cout << "GRACZ: >>  HP:" << fhp << "  DMG:" << dmg << "  LVL:" << lvl << "  Exp:" << Exp << "/" << nexp << " <<" << endl;
		cout << "PRZECIWNIK: >>  HP:" << ehp << "  DMG:" << edmg << " <<" << endl << endl;

		fdmg = rand() % dmg;
		cout << "Gracz zadaje: " << fdmg;
		ehp = ehp - fdmg;
		Sleep(500);

		fedmg = rand() % edmg;
		cout << endl << "Przeciwnik zadaje: " << fedmg;
		hp = hp - fedmg;
		Sleep(500);
	}
	gra();
}

void wolf()
{
	ehp = 15;
	edmg = 3;
}

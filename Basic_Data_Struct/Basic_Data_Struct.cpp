// SDIZO - projekt 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include "Array.h"
#include <fstream>
#include <string>
#include <cassert>
#include <math.h>
#include <Windows.h>
#include <vld.h>

// Struktury danych
Array* myArray = new Array();

// Prototypy funkcji wykorzystanych do tworzenia interfejsu 
void mainMenu();
void arrayMenu();

// Zmienne do pozycjonowania tekstu
CONSOLE_SCREEN_BUFFER_INFO csbi;
int columns, rows;


// Zmienne czasowe
LARGE_INTEGER start, end, PCFreq;
double time;

LARGE_INTEGER startTimer()
{
	QueryPerformanceFrequency(&PCFreq);
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}
LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}
int main()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	mainMenu();

	delete myArray;

	system("PAUSE");
	return 0;
}
void mainMenu()
{
	system("CLS");
	int choice;
	std::cout << "\n Struktury:\n\n ";
	std::cout << "1- Tablica\n 2- Lista\n 3- Kopiec\n 4- Drzewo czerwono - czarne\n 5- Wyjscie\n ";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
	{
		arrayMenu();
		break;
	}
	case 2:
	{

		return;
	}
	case 3:
	{

		break;
	}
	case 4:
	{

		break;
	}
	default:
	{
		return;
	}
	}
}
void arrayMenu()
{
	system("CLS");
	int choice;
	std::cout << "\n Tablica" << std::endl;
	while (true)
	{
		std::cout.width(20);
		std::cout << "\n 1- Wgraj z pliku\n 2- Dodaj\n 3- Usun\n 4- znajdz\n 5- Wyswietl\n 6- Wstecz\n 7- Wyjscie\n";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			std::string filepath;
			std::cout << std::endl << "Podaj nazwe pliku: ";
			std::cin >> filepath;
			myArray->loadFromFile(filepath);
			myArray->saveToFile(filepath);
			std::cout << "\n" << myArray->toString();
			break;
		}
		case 2:
		{
			for (int it = 0; it < 10; ++it)
				myArray->pushAt(it, 0);
			myArray->pushAt(12, 5);
			break;
		}
		case 3:
		{

			break;
		}
		case 4:
		{
			break;
		}
		case 5:
		{
			system("CLS");
			std::cout.width(floor(columns / 2));
			std::cout << "Tablica\n\n";

			std::cout << myArray->toString() << std::endl;
			break;
		}
		case 6:
		{
			mainMenu();
			return;
		}
		default:
		{
			return;
		}
		}
	}
}
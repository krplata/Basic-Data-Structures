// SDIZO - projekt 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include "DoubleLinkedList.h"
#include "DArray.h"
#include "Heap.h"
#include "R_BTree.h"
#include <fstream>
#include <string> 
#include <cassert>
#include <math.h>
#include <Windows.h>

// Struktury danych
DoubleLinkedList* doubleList = new DoubleLinkedList();
DArray* myArray = new DArray(0);
Heap* myHeap = new Heap();
R_BTree* myRBTree = new R_BTree();


// Prototypy funkcji wykorzystanych do tworzenia interfejsu 
void mainMenu();
void listMenu();
void arrayMenu();
void heapMenu();
void rbTreeMenu();
void removeList();
void addList();
void removeArray();
void admyArray();
void assertFiles(std::string filepath1, std::string filepath2);

// Stale
const int arrayType = 1;
const int listType = 2;
const int heapType = 3;
const int rbTreeType = 4;

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
	delete myHeap;
	delete doubleList;

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
		listMenu();
		return;
	}
	case 3:
	{
		heapMenu();
		break;
	}
	case 4:
	{
		rbTreeMenu();
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

			std::fstream plik;
			plik.open(filepath, std::ios::in);
			std::string line;
			int number;
			while (plik.good())
			{
				plik >> line;
				number = stoi(line);
				myArray->pushBack(number);
			}
			break;
		}
		case 2:
		{
			admyArray();
			break;
		}
		case 3:
		{
			removeArray();
			break;
		}
		case 4:
		{

			int index;

			std::cout << "Podaj indeks: \n";
			std::cin >> index;

			start = startTimer();
			myArray->lookUpIndex(index);
			end = endTimer();

			time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;
			std::cout << "Czas wykonania operacji to :" << time << std::endl;

			break;
		}
		case 5:
		{
			system("CLS");
			std::cout.width(floor(columns / 2));
			std::cout << "Tablica\n\n";
			myArray->display();
			std::cout << std::endl;
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
void listMenu()
{
	system("CLS");
	int choice;
	std::cout << "\n Lista Dwukierunkowa" << std::endl;
	while (true)
	{
		std::cout << "\n 1- Wgraj z pliku\n 2- Dodaj\n 3- Usun\n 4- Znajdz\n 5- Wyswietl\n 6- Wstecz\n 7- Wyjscie\n";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			std::string filepath;
			std::cout << std::endl << "Podaj nazwe pliku: ";
			std::cin >> filepath;

			std::fstream plik;
			plik.open(filepath, std::ios::in);
			std::string line;
			int number;
			while (plik.good())
			{
				plik >> line;
				number = stoi(line);
				doubleList->pushBack(number);
			}
			break;
		}
		case 2:
		{
			addList();
			break;
		}
		case 3:
		{
			removeList();
			break;
		}
		case 4:
		{
			std::cout << "Podaj wartosc:\n";
			int value;
			std::cin >> value;

			start = startTimer();
			doubleList->find(value);
			end = endTimer();

			time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

			std::cout << "Czas wykonania operacji to:" << time << std::endl;
			break;

		}
		case 5:
		{
			system("CLS");
			std::cout.width(floor(columns / 2));
			std::cout << "Lista Dwukierunkowa\n\n";
			doubleList->display();
			std::cout << std::endl;
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
void heapMenu()
{
	system("CLS");
	int choice;
	std::cout << "\n Kopiec" << std::endl;

	while (true)
	{
		std::cout << "\n 1- Wgraj z pliku\n 2- Dodaj\n 3- Usun\n 4- Znajdz\n 5- Wyswietl\n 6- Wstecz\n 7- Wyjscie\n";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			std::string filepath;
			std::cout << std::endl << "Podaj nazwe pliku: ";
			std::cin >> filepath;

			std::fstream plik;
			plik.open(filepath, std::ios::in);
			std::string line;
			int number;
			while (plik.good())
			{
				plik >> line;
				number = stoi(line);
				myHeap->pushValue(number);

			}
			break;
		}
		case 2:
		{
			std::cout << "\n Podaj wartosc jaka chcesz dodac:\n";
			int value = 0;
			std::cin >> value;

			start = startTimer();
			myHeap->pushValue(value);
			end = endTimer();

			time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;
			std::cout << "Czas wykonania operacji to :" << time;

			break;
		}
		case 3:
		{
			start = startTimer();
			myHeap->popRoot();
			end = endTimer();

			time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

			std::cout << "Czas wykonania operacji to :" << time;
			break;
		}
		case 4:
		{
			std::cout << "Podaj wartosc:\n";
			int value;
			std::cin >> value;

			start = startTimer();
			myHeap->findValue(value);
			end = endTimer();

			time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;


			std::cout << "Czas wykonania operacji to :" << time;
			break;
		}
		case 5:
		{
			system("CLS");
			myHeap->display("", "", 0);
			std::cout << "\n\n";
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
void rbTreeMenu()
{
	system("CLS");
	int choice;
	std::cout << "\n Drzewo Czerwono-Czarne" << std::endl;

	while (true)
	{
		std::cout << "\n 1- Wgraj z pliku\n 2- Dodaj\n 3- Usun\n 4- Znajdz\n 5- Wyswietl\n 6- Wstecz\n 7- Wyjscie\n";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			std::string filepath;
			std::cout << std::endl << "Podaj nazwe pliku: ";
			std::cin >> filepath;

			std::fstream plik;
			plik.open(filepath, std::ios::in);
			std::string line;
			int number;
			while (plik.good())
			{
				plik >> line;
				number = stoi(line);
				myRBTree->pushValue(number);
			}
			break;
		}
		case 2:
		{
			std::cout << "\n Podaj wartosc jaka chcesz dodac:\n";
			int value = 0;
			std::cin >> value;

			start = startTimer();
			myRBTree->pushValue(value);
			end = endTimer();

			time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

			std::cout << "Czas wykonania operacji to :" << time;
			break;
		}
		case 3:
		{
			start = startTimer();
			myRBTree->removeRoot(myRBTree->getRoot());
			end = endTimer();

			time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

			std::cout << "Czas wykonania operacji to :" << time;
			break;
		}
		case 4:
		{
			int value;
			std::cout << "Podaj wartosc";
			std::cin >> value;

			start = startTimer();
			myRBTree->find(value);
			end = endTimer();

			time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

			std::cout << "Czas wykonania operacji to :" << time;
			break;
		}
		case 5:
		{
			system("CLS");
			myRBTree->display("", "", myRBTree->getRoot());
			std::cout << "\n\n";
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
void admyArray()
{
	system("CLS");

	int choice;
	int value;

	std::cout << "\nGdzie chcesz dodac liczbe ?\n";
	std::cout << " 1-Poczatek\n";
	std::cout << " 2-Koniec\n";
	std::cout << " 3-Przed konkretnym indeksem\n";
	std::cin >> choice;

	std::cout << "Podaj wartosc: \n";
	std::cin >> value;

	switch (choice)
	{
	case 1:
	{
		start = startTimer();
		myArray->pushFront(value);
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

		std::cout << "\n Czas wykonania operacji to: " << time << std::endl;
		break;
	}
	case 2:
	{
		int index;

		std::cout << "Podaj indeks: \n";
		std::cin >> index;

		start = startTimer();
		myArray->pushBack(value);
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;


		std::cout << "\n Czas wykonania operacji to: " << time << std::endl;
		break;
	}
	case 3:
	{
		int index;

		std::cout << "Podaj indeks: \n";
		std::cin >> index;

		start = startTimer();
		myArray->pushAt(value, index);
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;


		std::cout << "\n Czas wykonania operacji to: " << time << std::endl;
		break;
	}
	}
}
void addList()
{
	system("CLS");

	int choice;
	int value;

	std::cout << "\nGdzie chcesz dodac liczbe ?\n";
	std::cout << " 1-Poczatek\n";
	std::cout << " 2-Koniec\n";
	std::cout << " 3-Przed konkretnym indeksem\n";
	std::cin >> choice;

	std::cout << "Podaj wartosc: \n";
	std::cin >> value;

	switch (choice)
	{
	case 1:
	{
		start = startTimer();
		doubleList->pushFront(value);
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

		std::cout << "Czas wykonania operacji to :" << time;
		break;
	}
	case 2:
	{
		doubleList->pushBack(value);
		break;
	}
	case 3:
	{
		int index;
		std::cout << "Podaj indeks:";
		std::cin >> index;

		start = startTimer();
		doubleList->pushAt(value, index);
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

		std::cout << "Czas wykonania operacji to :" << time;
		break;
	}
	}
}
void removeArray()
{
	system("CLS");
	int choice;
	int value;

	std::cout << "\nKtora liczbe chcesz usunac\n";
	std::cout << " 1-Poczatek\n";
	std::cout << " 2-Koniec\n";
	std::cout << " 3-Przed konkretnym indeksem\n";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
	{
		start = startTimer();
		myArray->popFront();
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;
		std::cout << "\n Czas wykonania operacji to: " << time << std::endl;

		break;
	}
	case 2:
	{
		start = startTimer();
		myArray->popBack();
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

		std::cout << "Czas wykonania operacji to :" << time;
		break;
	}
	case 3:
	{
		int index;

		std::cout << "Podaj indeks: \n";
		std::cin >> index;

		start = startTimer();
		myArray->popAt(index);
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

		std::cout << "Czas wykonania operacji to :" << time;
		break;
	}
	}

}
void removeList()
{
	system("CLS");

	int choice;
	int value;

	std::cout << "\nKtora liczbe chcesz usunac\n";
	std::cout << " 1-Poczatek\n";
	std::cout << " 2-Koniec\n";
	std::cout << " 3-Przed konkretnym indeksem\n";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
	{

		start = startTimer();
		doubleList->popFront();
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

		std::cout << "Czas wykonania operacji to :" << time;
		break;
	}
	case 2:
	{
		start = startTimer();
		doubleList->popBack();
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

		std::cout << "Czas wykonania operacji to :" << time;
		break;
	}
	case 3:
	{
		int index;

		std::cout << "Podaj indeks: \n";
		std::cin >> index;

		start = startTimer();
		doubleList->popAt(index);
		end = endTimer();

		time = (float)(end.QuadPart - start.QuadPart) / PCFreq.QuadPart;

		std::cout << "Czas wykonania operacji to :" << time;
		break;
	}
	}
}
/*void arrayTest()
{
std::fstream fileInput;
fileInput.open("file1.txt", std::ios::in);
std::string line;

int number = 0;
while (fileInput.good())
{
fileInput >> line;
number = std::stoi(line);
myArray->pushBack(number);
}
fileInput.close();
std::fstream fileInput2;
fileInput2.open(filepath, std::ios::app);
int* p = myArray->dArray;
int counter = 0;

while (counter < myArray->size - 1)
{
fileInput2 << *p << std::endl;
p++;
counter++;
}
fileInput2.close();

assertFiles(filepath, filepath);
}*/
/*void assertFiles(std::string filepath1, std::string filepath2)
{
std::fstream file1, file2;
file1.open(filepath1, std::ios::in);
file2.open(filepath2, std::ios::in);

std::string lineFile1;
const char * c1 = lineFile1.c_str();
std::string lineFile2;
const char * c2 = lineFile2.c_str();

while (file1.good() && file2.good())
{
getline(file1, lineFile1);
getline(file2, lineFile2);

assert(strcmp(c1, c2) == 0);
}
file1.close();
file2.close();

}*/

// SDIZO - projekt 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <vld.h>

#include "Array.h"
#include "List.h";
#include "DoublyLinkedList.h"
#include "Heap.h"
#include "Stack.h"
#include "Timer.h"

using namespace std;

Array* myArray = new Array();
List* myList = new List();
DoublyLinkedList* myDLList = new DoublyLinkedList();

double time;

void mainMenu();

HANDLE consoleLine = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPosition; 

void gotoXY(int, int); 
void drawMenu(std::string namesArr[], int size, std::string title);

int main()
{
	mainMenu();

	delete myArray;
	delete myList;
	delete myDLList;

	system("PAUSE");
	return 0;
}
void mainMenu()
{
	std::string test[6] = {"Array", "Heap", "Stack", "List", "Doubly Linked List", "Exit"};
	drawMenu(test, 6, "Structures");
	return ;
}

void gotoXY(int x, int y)
{
	cursorPosition.X = x;
	cursorPosition.Y = y;
	SetConsoleCursorPosition(consoleLine, cursorPosition);
}

void drawMenu(std::string namesArr [], int size, std::string title)
{
	// -------------------- Values needed for padding -------------------
	int spacesInside;
	int longestName = 0;
	
	for (int it = 0; it < size; it++)
	{
		if (namesArr[it].length() > longestName)
			longestName = namesArr[it].length();
	}
	spacesInside = longestName + 8; // 2 vertical lines, "1)", 2 chars for "->", 1 empty space before and after the word
	
	int leftTitleSpace = floor(spacesInside / 2 - title.length()/2);	
	int rightTitleSpace = spacesInside - leftTitleSpace - title.length();

	// ----------------------- Printing ---------------------------------
	gotoXY(5, 0);
	std::cout << std::string(leftTitleSpace, '-') << title << std::string(rightTitleSpace, '-');

		// Each line has a form of : "|  1) title |".
		// All lines are adjusted towards the longest subtitles.

	for (int drawIt = 1; drawIt <= size; ++drawIt)
	{
		gotoXY(5, drawIt);
		int spaces = longestName - namesArr[drawIt - 1].length();
		std::cout << "|  " << drawIt << ") " << namesArr[drawIt - 1] << std::string (spaces, ' ') << " |\n";
	}

	gotoXY(5, size + 1);
	std::cout << std::string(spacesInside, '-') << std::endl;

}
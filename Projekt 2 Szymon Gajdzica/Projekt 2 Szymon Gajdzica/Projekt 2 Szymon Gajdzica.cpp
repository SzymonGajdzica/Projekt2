// Projekt 2 Szymon Gajdzica.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include "mList.h"
#include "mCount.h"
#include <conio.h>

void displayHelp() {
	std::cout << "-------------help-------------" << std::endl;
	std::cout << "Enter large numbers and sign" << std::endl;
	std::cout << "For example: \"997 + 998 * 999\"" << std::endl;
	std::cout << "For more help write \"program h\"" << std::endl << std::endl;
	std::cout << "Created by Szymon Gajdzica" << std::endl;
	std::cout << "Press any key" << std::endl;
	_getch();
}

bool addToList(const char *numbers, Node<int> *guard) {
	for (int i = 0; i < strlen(numbers); i++) {
		int tmp = static_cast<int>(numbers[i]) - 48;
		if (tmp >= 0 && tmp <= 9)
			addFront(tmp, guard);
		else
			return false;
	}
	return true;
}

void clearMemory(Node<int> **tableOfLists, int size) {
	for (unsigned int i = 0; i < size; i++) {
		clearList(tableOfLists[i]);
		delete(tableOfLists[i]);
	}
	delete(tableOfLists);
	displayHelp();
}

int fillLists(int argc, char *argv[], Node<int> **tableOfLists, countMode *signs) {
	unsigned int sizeLists = 0;
	unsigned int sizeSigns = 0;
	bool expectations = true;
	for (unsigned int i = 1; i < argc; i++) {
		if (argv[i] == "h") {
			delete(signs);
			clearMemory(tableOfLists, sizeLists);
			return -1;
		}
		if (argv[i][0] == '+' || argv[i][0] == '-' || argv[i][0] == '*' && strlen(argv[i]) == 1) {
			if (expectations) {
				delete(signs);
				clearMemory(tableOfLists, sizeLists);
				return -1;
			}
			expectations = true;
			if (argv[i][0] == '+')
				signs[sizeSigns] = ADD;
			else if (argv[i][0] == '-')
				signs[sizeSigns] = DIFFERENCE;
			else if (argv[i][0] == '*')
				signs[sizeSigns] = MULTIPLICATION;
			sizeSigns++;
		}
		else {
			if (!expectations) {
				delete(signs);
				clearMemory(tableOfLists, sizeLists);
				return -1;
			}
			expectations = false;
			tableOfLists[sizeSigns] = newList<int>();
			if (!addToList(argv[i], tableOfLists[sizeSigns])) {
				delete(signs);
				clearMemory(tableOfLists, sizeLists);
				return -1;
			}
			sizeLists++;
		}
	}
	return sizeSigns;
}

void workLists(Node<int> **tableOfLists, countMode *signs, int sizeSigns) {
	auto *result = new Result<int>();
	result->digit = newList<int>();
	result->sign = false;
	for (unsigned int i = 0; i < sizeSigns; i++) {
		countLists(tableOfLists[i], tableOfLists[i + 1], result, signs[i]);
		clearList(tableOfLists[i]);
		clearList(tableOfLists[i + 1]);
		delete(tableOfLists[i]);
		delete(tableOfLists[i + 1]);
		if (i + 1 != sizeSigns) {
			tableOfLists[i + 1] = result->digit;
			result->digit = newList<int>();
			result->sign = false;
		}
		else {
			displayList(result);
			clearList(result->digit);
			delete(result);
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 4) {
		displayHelp();
		return 0;
	}
	auto **tableOfLists = new Node<int>*[argc / 2];
	auto *signs = new countMode[(argc - 2) / 2];
	int sizeSigns = fillLists(argc, argv, tableOfLists, signs);
	if (sizeSigns < 0) {
		displayHelp();
		return -1;
	}
	workLists(tableOfLists, signs, sizeSigns);
	std::cout << "Press any key to continue" << std::endl;
	_getch();
	return 0;
}


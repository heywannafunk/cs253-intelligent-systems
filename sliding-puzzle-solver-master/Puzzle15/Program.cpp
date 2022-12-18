#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "Node.cpp"

using namespace std;

string startPos;
vector<int> pos(16);
int zero;

char key;
int asciiValue;

bool solvable() {
	int n = 0;
	for (size_t i = 0; i < 16; i++){
		if (pos[i] == 0) {
			continue;
		}
		for (size_t j = i; j < 16; j++){
			if (pos[j] == 0) {
				continue;
			}
			if (pos[i] > pos[j]) {
				n++;
			}
		}
	}
	n += zero / 4 + 1;
	return !(n % 2);
}

void printGuide() {
	cout << "use these keys to move tiles: " << endl;
	cout << "	  w" << endl;
	cout << "	a s d" << endl;
	cout << endl;
	cout << "press esc to quit playing." << endl;
	cout << endl;
}


void pushTile(int asciiValue) {
	int tile = zero;
	switch (asciiValue) {
	case 119://push tile up
		if (zero > 11) {
			return;
		}
		else {
			tile = zero + 4;
		}
		break;
	case 100://push tile left
		if (zero % 4 == 0) {
			return;
		}
		else {
			tile = zero - 1;
		}
		break;
	case 115://push tile down
		if (zero < 4) {
			return;
		}
		else {
			tile = zero - 4;
		}
		break;
	case 97://push tile right
		if (zero % 4 == 3) {
			return;
		}
		else {
			tile = zero + 1;
		}
		break;
	}
	//swapTiles(zero, tile);
}

void play(string startPos) {
	printGuide();

	for (size_t i = 0; i < startPos.length(); i++) {
		switch (startPos[i])
		{
		case 'A':
			pos[i] = 10;
			break;
		case 'B':
			pos[i] = 11;
			break;
		case 'C':
			pos[i] = 12;
			break;
		case 'D':
			pos[i] = 13;
			break;
		case 'E':
			pos[i] = 14;
			break;
		case 'F':
			pos[i] = 15;
			break;
		default:
			if (startPos[i] == '0') {
				zero = i;
			}
			pos[i] = startPos[i] - '0';
			break;
		}
	}

	if (!solvable()) {
		cout << "position cant be solved";
		return;
	}

	//printPosition();

	while (true)	{
		key = _getch();
		asciiValue = key;
		if (asciiValue == 27) {
			break;
		}
		switch (asciiValue){
		case 119: case 97: case 115: case 100:
			pushTile(asciiValue);
			break;
		default:
			continue;
			break;
		}
		//printPosition();
	}
}

/*
//123456789ABCDEF0
int main() {
	//cin >> startPos;
	play("1234067859ACDEBF");

	return 0;
}*/
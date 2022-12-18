#include <vector>
#include <string>
#include <iostream>
#include "Algorithm.cpp"

using namespace std;

//123456789ABCDEF0
//1234067859ACDEBF 5
int main() {
	vector<int> startBoard(16);
	string startPos = "1234067859ACDEBF";
	for (size_t i = 0; i < 16; i++) {
		switch (startPos[i])
		{
		case 'A':
			startBoard[i] = 10;
			break;
		case 'B':
			startBoard[i] = 11;
			break;
		case 'C':
			startBoard[i] = 12;
			break;
		case 'D':
			startBoard[i] = 13;
			break;
		case 'E':
			startBoard[i] = 14;
			break;
		case 'F':
			startBoard[i] = 15;
			break;
		default:
			startBoard[i] = startPos[i] - '0';
			break;
		}
	}

	hNode * root = new hNode(startBoard);
	Algorithm ui = Algorithm();

	//vector<hNode*> solution = ui.BFS(root);

	//vector<hNode*> solution = ui.IDS(root, 10);

	vector<hNode*> solution = ui.IDAstar(root);

	if (solution.size() > 0) {
		for (size_t i = 0; i < solution.size(); i++){
			solution[i]->printBoard();
		}
	}
	else {
		cout << "no solution" << endl;
	}
	return 0;
}
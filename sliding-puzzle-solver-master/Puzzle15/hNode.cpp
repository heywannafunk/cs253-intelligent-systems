#include <vector>
#include <iostream>

using namespace std;

class hNode{
public:
	vector<hNode*> children;
	hNode* parent;
	vector<int> board;
	int z;

	int heuristic;
	int depth;

	hNode(vector<int> b) {
		board = b;
		for (size_t i = 0; i < 16; i++) {
			if (b[i] == 0) {
				z = i;
			}
		}
		depth = 0;
	}

	hNode() {
		board = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0} ;
		z = 15;
		depth = 0;
	}

	void printBoard() {
		int x = 0;
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) {
				if (board[x] < 10) {
					if (board[x] == 0) {
						cout << "|  | ";
						x++;
					}
					else {
						cout << "| " << board[x++] << "| ";
					}
				}
				else {
					cout << "|" << board[x++] << "| ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	bool solvable() {
		int n = 0;
		for (size_t i = 0; i < 16; i++) {
			if (board[i] == 0) {
				continue;
			}
			for (size_t j = i; j < 16; j++) {
				if (board[j] == 0) {
					continue;
				}
				if (board[i] > board[j]) {
					n++;
				}
			}
		}
		n += z / 4 + 1;
		return !(n % 2);
	}

	bool goalReached() {
		bool res = true;
		for (size_t i = 0; i < 15; i++) {
			for (size_t j = i; j < 15; j++) {
				if (board[j] < board[i]) {
					res = false;
				}
			}
		}
		return res;
	}

	int h() {
		int h = 0;
		vector<int> goal = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0 };
		for (size_t i = 0; i < board.size(); i++)
		{
			if (board[i] == '0')
				continue;

			int Pos = i;
			int destPos = -1;
			for (size_t j = 0; j < 16; j++) {
				if (board[i] == goal[j])
					destPos = j;
			};

			int xDist = abs((destPos / 4) - (Pos / 4));
			int yDist = abs((destPos % 4) - (Pos % 4));

			int distance = xDist + yDist;
			h += distance;
		}
		return h;
	}

	void expand() {
		right(board, z);
		left(board, z);
		up(board, z);
		down(board, z);
	}

	void right(vector<int> b, int i) {
		if (i % 4 < 3) {
			vector<int> pp = b;
			int temp = pp[i + 1];
			pp[i + 1] = pp[i];
			pp[i] = temp;

			hNode* child = new hNode(pp);
			children.push_back(child);
			child->parent = this;
			child->depth = this->depth + 1;
			child->heuristic = child->h();
		}
	}
	void left(vector<int> b, int i) {
		if (i % 4 > 0) {
			vector<int> pp = b;
			int temp = pp[i - 1];
			pp[i - 1] = pp[i];
			pp[i] = temp;

			hNode* child = new hNode(pp);
			children.push_back(child);
			child->parent = this;
			child->depth = this->depth + 1;
			child->heuristic = child->h();
		}
	}
	void up(vector<int> b, int i) {
		if (i - 4 >= 0) {
			vector<int> pp = b;
			int temp = pp[i - 4];
			pp[i - 4] = pp[i];
			pp[i] = temp;

			hNode* child = new hNode(pp);
			children.push_back(child);
			child->parent = this;
			child->depth = this->depth + 1;
			child->heuristic = child->h();
		}
	}
	void down(vector<int> b, int i) {
		if (i + 4 < 16) {
			vector<int> pp = b;
			int temp = pp[i + 4];
			pp[i + 4] = pp[i];
			pp[i] = temp;

			hNode* child = new hNode(pp);
			children.push_back(child);
			child->parent = this;
			child->depth = this->depth + 1;
			child->heuristic = child->h();
		}
	}
};
#include <vector>
#include <iostream>

using namespace std;

class Node {
public:
	vector<Node*> children;
	Node* parent;
	vector<int> board;
	int z;

	Node(vector<int> b) {
		board = b;
		for (size_t i = 0; i < 16; i++) {
			if (board[i] == 0) {
				z = i;
			}
		}
	};

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
		for (size_t i = 0; i < 15; i++){
			for (size_t j = i; j < 15; j++){
				if (board[j] < board[i]) {
					res = false;
				}
			}
		}
		return res;
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

			Node * child = new Node(pp);
			children.push_back(child);
			child->parent = this;
		}
	}
	void left(vector<int> b, int i) {
		if (i % 4 > 0) {
			vector<int> pp = b;
			int temp = pp[i - 1];
			pp[i - 1] = pp[i];
			pp[i] = temp;

			Node* child = new Node(pp);
			children.push_back(child);
			child->parent = this;
		}
	}
	void up(vector<int> b, int i) {
		if (i - 4 >= 0) {
			vector<int> pp = b;
			int temp = pp[i - 4];
			pp[i - 4] = pp[i];
			pp[i] = temp;

			Node* child = new Node(pp);
			children.push_back(child);
			child->parent = this;
		}
	}
	void down(vector<int> b, int i) {
		if (i + 4 < 16) {
			vector<int> pp = b;
			int temp = pp[i + 4];
			pp[i + 4] = pp[i];
			pp[i] = temp;

			Node* child = new Node(pp);
			children.push_back(child);
			child->parent = this;
		}
	}
};
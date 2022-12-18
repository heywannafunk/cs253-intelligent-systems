#include <vector>
#include <iostream>
#include <list>
#include "hNode.cpp"
#include <tuple>
#include <algorithm>

using namespace std;

class Algorithm {
public:
	Algorithm() {}

	void pathTrace(vector<hNode*>& p, hNode* n) {
		cout << "tracing path..." << endl;
		hNode* currentNode = n;
		while (currentNode->parent != NULL) {
			currentNode = currentNode->parent;
			p.push_back(currentNode);
		}
	}

	bool Contains(vector<hNode*> l, hNode* c) {
		bool res = false;

		for (size_t i = 0; i < l.size(); i++) {
			if (l[i]->board == c->board) {
				res = true;
			}
		}
		return res;
	}

	vector<hNode*> BFS(hNode * r) {
		vector<hNode*> path;
		vector<hNode*> white;
		vector<hNode*> black;

		white.push_back(r);
		bool exit = false;

		while (white.size() > 0 && !exit) {
			hNode * currentNode = white[0];
			black.push_back(currentNode);
			white.erase(white.begin());

			if (!currentNode->solvable()) {
				cout << "This starting position can't be solved!" << endl;
				break;
			}

			if (currentNode->goalReached()) {
				cout << "Starting position is already a goal!" << endl;
				break;
			}

			currentNode->expand();

			for (size_t i = 0; i < currentNode->children.size(); i++){
				hNode * currentChild = currentNode->children[i];
				if (currentChild->goalReached()) {
					cout << "goal found" << endl;
					exit = true;
					
					pathTrace(path, currentChild);
				}
				if (!Contains(white, currentChild) && !Contains(black, currentChild))
					white.push_back(currentChild);
			}
		}
		return path;
	}

	bool DLS(hNode* currentNode, int limit, vector<hNode*> & p){
		if (currentNode->goalReached()) {
			p.push_back(currentNode);
			return true;
		}

		currentNode->expand();

		if (limit <= 0)
			return false;

		for (size_t i = 0; i < currentNode->children.size(); i++)
			if (DLS(currentNode->children[i], limit - 1, p) == true) {
				p.push_back(currentNode);
				return true;
			}

		return false;
	}

	vector<hNode*> IDS(hNode* r, int max_depth){
		vector<hNode*> path;
		for (size_t i = 0; i <= max_depth; i++)
			if (DLS(r, i, path) == true) {
				return path;
			}
	}

	struct hComp {
		inline bool operator()(hNode* const& p1, hNode* const& p2){
			return p1->heuristic < p2->heuristic;
		}
	};

	tuple<hNode*, int> IDAsearch(vector<hNode*>& p, int cost, int bound)
	{
		hNode * currentNode = p[p.size()-1];
		int f = currentNode->heuristic;
		if (f > bound)
			return { currentNode, 0 };
		if (currentNode->goalReached())
			return { currentNode, 1 };
		hNode* min = new hNode();
		min->heuristic = INT_MAX;
		currentNode->expand();

		auto successors = currentNode->children;
		sort(successors.begin(), successors.end(), hComp());

		for (size_t i = 0; i < successors.size(); i++){
			int ind = -1;
			for (size_t j = 0; j < p.size(); j++){
				if (p[j] == successors[i])
					ind = j;
			}
			
			if (ind == -1) {
				p.push_back(successors[i]);
				tuple<hNode*, int> t = IDAsearch(p, f, bound);
				if (get<1>(t) == 1) {
					return t;
				}
				hNode* node = get<0>(t);
				if (node->heuristic < min->heuristic) {
					min = node;
				}
				p.erase(p.begin());
			}
		}
		return { min, 0 };
	}

	vector<hNode*> IDAstar(hNode * r){
		vector<hNode*> path;

		hNode* currentNode = r;
		currentNode->heuristic = currentNode->depth + currentNode->h();

		int bound = currentNode->heuristic;
		path.push_back(currentNode);

		while (true){
			tuple<hNode*, int> t = IDAsearch(path, 0, bound);
			if (get<1>(t) == 1){
				path.push_back(get<0>(t));
				return path;
			}
			hNode* node = get<0>(t);
			bound = node->heuristic;
		}
	}
};
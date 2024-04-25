#include <iostream>
#include "Graph.h"

using namespace std;

#define el endl;

int main() {

	Graph* mp = new Graph();
	mp->addEdge("1", "2");
	mp->addEdge("2", "3");
	mp->addEdge("1", "3");
	mp->addEdge("1", "5");
	mp->addEdge("4", "3");
	mp->addEdge("4", "6");

	string val;
	int ans = -1;
	Node* test = nullptr;
	while (ans != 3) {
		cout << "enter value and request\n";
		cout << "for bfs -> 1, dfs -> 2, break -> 3 \n";
		cin >> val;
		cin >> ans;
		test = mp->getNode(val);
		mp->clearVisted();
		if (test != nullptr)
		{
			if (ans == 2)
				mp->dfs(test);
			if (ans == 1)
				mp->bfs(test);
			cout << el;
		}
		else {
			cout << "node doesn't exist\n";
		}
	}
	return 0;
}
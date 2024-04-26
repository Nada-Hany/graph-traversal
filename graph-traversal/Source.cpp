#include <iostream>
#include "Graph.h"
#include "File.h"
#include <vector>
#include <sstream>
using namespace std;

#define el endl;

void toLowercase(string& str) {
	string result;
	for (char c : str) 
		result += tolower(c);
	str = result;
}

int main() {

	//files 
	File file("TransportationMap.txt");
	file.readFile();

	//for (auto line : file.data) {
	//	for (string word : line) {
	//		cout << word << " ";
	//	}
	//	cout << el;
	//}

	Graph* mp = new Graph();
	file.convertToObjects(mp);

	//mp->addEdge("1", "2");
	//mp->addEdge("2", "3");
	//mp->addEdge("1", "3");
	//mp->addEdge("1", "5");
	//mp->addEdge("4", "3");
	//mp->addEdge("4", "6");
	

	//dfs and bfs 
	string val, dest;
	int ans = -1;
	Node* test = nullptr;
	Node* destNode = nullptr;
	vector<vector<string>> path;
	while (ans != 3) {
		path.clear();
		cout << "enter value and request\n";
		cout << "for bfs -> 1, dfs -> 2, break -> 3 , 4-> paths\n";
		cin >> val;
		cin >> ans;
		if (ans == 4) {
			cout << "enter dest\n";
			cin >> dest;
			destNode = mp->getNode(dest);
		}
		toLowercase(val);
		test = mp->getNode(val);
		mp->clearVisted();
		mp->clearPrevious();

		if (test != nullptr)
		{
			if (ans == 2)
				mp->dfs(test);
			else if (ans == 1)
				mp->bfs(test);
			else if (ans == 4)
			{
				if (destNode != nullptr)
				{
					mp->dfs(test, destNode, path);
					mp->getPaths(path);
				}
				else
					cout << "dest doesn't exist\n";
			}
			cout << el;
		}
		else {
			cout << "node doesn't exist\n";
		}
	}

	return 0;
}
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
	//file.convertToObjects(mp);
	file.convertWeights(mp);
	//for (auto n : mp->adj) {
	//	for(auto x: n.first->weights)
	//	{
	//		for (auto s : x.second)
	//		{
	//			cout << n.first->value << "  " << x.first->value << "  " << s.first << "  " << s.second << endl;
	//		}
	//	}
	//}

	//mp->addEdge("1", "2");
	//mp->addEdge("2", "3");
	//mp->addEdge("1", "3");
	//mp->addEdge("1", "5");
	//mp->addEdge("4", "3");
	//mp->addEdge("4", "6");
	

	//dfs and bfs 
	string src, dest, weightType;
	int ans = -1, action;
	double weightValue;
	Node* startNode = nullptr;
	Node* destNode = nullptr;
	vector<vector<string>> path;
	while (ans != 3) {
		path.clear();
		cout << "enter request and value\n";
		cout << "for bfs -> 1, dfs -> 2, break -> 3 , 4-> paths, 5->dealing with weights, 6-> complete graph\n";
		cin >> ans;
		if (ans == 6) {
			if (mp->checkCompleteness())
				cout << "graph is complete\n";
			else
				cout << "graph isn't complete\n";
			continue;
		}
		cin >> src;
		toLowercase(src);
		if (ans == 4) {
			cout << "enter dest\n";
			cin >> dest;
			destNode = mp->getNode(dest);
		}else if (ans==5)
		{
			cout << "enter dest\n";
			cin >> dest;
			cout << "enter weight type and its value\n";
			cin >> weightType >> weightValue;
			toLowercase(weightType);
			cout << "eneter action: 1-> add, 2-> delete, 3-> update weight value\n";
			cin >> action;
			mp->addEdge(src, dest, weightType, weightValue, action);
			for (auto n : mp->adj) {
				for (auto x : n.first->weights)
				{
					for (auto s : x.second)
					{
						cout << n.first->value << "  " << x.first->value << "  " << s.first << "  " << s.second << endl;
					}
				}
			}
			continue;
		}
		
		toLowercase(dest);
		startNode = mp->getNode(src);
		mp->clearVisted();
		mp->clearPrevious();

		if (startNode != nullptr)
		{
			if (ans == 2)
				mp->dfs(startNode);
			else if (ans == 1)
				mp->bfs(startNode);
			else if (ans == 4)
			{
				if (destNode != nullptr)
				{
					mp->dfs(startNode, destNode, path);
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
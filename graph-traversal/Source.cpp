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

	Graph* graph = new Graph();
	//file.convertToObjects(graph);
	file.convertWeights(graph);
	//for (auto n : graph->adj) {
	//	for(auto x: n.first->weights)
	//	{
	//		for (auto s : x.second)
	//		{
	//			cout << n.first->value << "  " << x.first->value << "  " << s.first << "  " << s.second << endl;
	//		}
	//	}
	//}

	//graph->addEdge("1", "2");
	//graph->addEdge("2", "3");
	//graph->addEdge("1", "3");
	//graph->addEdge("1", "5");
	//graph->addEdge("4", "3");
	//graph->addEdge("4", "6");
	

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
		cout << "for bfs -> 1, dfs -> 2, break -> 3 , 4-> paths,"
			<< "5->dealing with weights, 6-> cographlete graph, 7-> path considering weights\n";
		cin >> ans;
		if (ans == 3)
			break;
		if (ans == 6) {
			if (graph->checkCompleteness())
				cout << "graph is cographlete\n";
			else
				cout << "graph isn't cographlete\n";
			continue;
		}
		cin >> src;
		toLowercase(src);
		if (ans == 4) {
			cout << "enter dest\n";
			cin >> dest;
			destNode = graph->getNode(dest);
		}else if (ans==5)
		{
			cout << "enter dest\n";
			cin >> dest;
			cout << "enter weight type and its value\n";
			cin >> weightType >> weightValue;
			toLowercase(weightType);
			cout << "eneter action: 1-> add, 2-> delete, 3-> update weight value\n";
			cin >> action;
			graph->addEdge(src, dest, weightType, weightValue, action);
			for (auto n : graph->adj) {
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
		startNode = graph->getNode(src);
		graph->clearVisted();
		graph->clearPrevious();

		if (startNode != nullptr)
		{
			if (ans == 2)
				graph->dfs(startNode);
			else if (ans == 1)
				graph->bfs(startNode);
			else if (ans == 4)
			{
				if (destNode != nullptr)
				{
					graph->dfs(startNode, destNode);
					graph->getPaths();
				}
				else
					cout << "dest doesn't exist\n";
			}
			else if (ans == 7) {
				//all path considering the weights here
			}
			cout << el;
		}
		else {
			cout << "node doesn't exist\n";
		}
	}
	file.writeOnFile(graph);
	return 0;
}
#include <iostream>
#include "Graph.h"
#include "File.h"
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>

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

	Graph* graph = new Graph();
	file.convertWeights(graph);

	//checking weighted paths
	Node* start = graph->getNode("cairo");
	Node* des = graph->getNode("dahab");
	graph->dfs(start, des);
	vector <vector< pair<vector<string>, float >> > paths;
	graph->getWeightedPaths(paths, 500);

	vector<pair<float,string>> out;
	for (int i = 0; i < paths.size(); i++) {
		for (auto allWeights : paths[i]) {
			string s = "";
			int indWeight = 0;
			s= s+ graph->paths[i][graph->paths[i].size() - 1] + " ";
			for (int nodeInd = graph->paths[i].size()-2; nodeInd >=0; nodeInd--) {
				s = s + allWeights.first[indWeight] + " " + graph->paths[i][nodeInd] + " ";
				indWeight++;
			}
			out.push_back(make_pair(allWeights.second, s));
		}
	}
	sort(out.begin(), out.end());
	for (auto n : out) {
		cout << n.second << "  " << n.first << el;
	}


	//dfs and bfs 
	string src, dest, weightType;
	int ans = -1, action;
	float weightValue;
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
#pragma once
#include <vector>
#include <map>
#include <list>
#include <string>
#include <queue>

using namespace std;


class Node
{

public:

	Node* previous = nullptr;
	map<Node*,vector<pair<string, double>>> weights;
	string value;

	bool isVisted = false;
	int weightExist(Node*, Node*, string);
	void changeWeightValue(vector<pair<string, double>>&, double, string);
	void changeWeightType(vector<pair<string, double>>&, string);
	void deleteWeight(Node*, Node*, string);
	void addWeight(Node *, Node*, double, string);
	Node(string);
	~Node();

};

class Graph
{
	map <string, int> indices;
	bool inOpen(Node*, queue<Node*>);
	bool childExist(Node*, Node*);
	void toLowerCase(string&);
	void getEachPath(Node*);
	vector<vector<string>> paths;

public:
	int nodesNumber = 0;
	Node* destination = nullptr;
	map<Node*, vector<Node*>> adj;

	Graph();
	void getPaths();
	Node* getNode(string);
	void addEdge(string, string);
	void addEdge(string, string, string, double, int);
	//traversing
	void dfs(Node*);
	//all possible paths without considering the weights
	void dfs(Node*, Node*);
	void bfs(Node*);
	void clearVisted();
	void clearPrevious();
	bool checkCompleteness();
	void getWeightedPaths(vector <vector< pair<vector<string>, double >> > &, double);
	~Graph();
};


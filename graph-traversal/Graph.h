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
	void getEachPath(Node*, vector<vector<string>>&);

public:
	int nodesNumber;
	Node* destination = nullptr;
	map<Node*, vector<Node*>> adj;
	Graph();
	void getPaths(vector<vector<string>>&);
	Node* getNode(string);
	void addEdge(string, string);
	void addEdge(string, string, string, double, int);
	void dfs(Node*);
	void dfs(Node*, Node*, vector<vector<string>>&, double);
	void dfs(Node*, Node*, vector<vector<string>>&);
	void bfs(Node*);
	void clearVisted();
	void clearPrevious();
	bool checkCompleteness();
	~Graph();
};


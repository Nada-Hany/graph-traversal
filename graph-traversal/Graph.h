#pragma once
#include <vector>
#include <map>
#include <list>
#include <string>
#include <queue>

using namespace std;
class Node {
	map<string, double> transportations;
	//coordinates
	int x, y;

public:
	string value;
	bool isVisted = false;
	Node(string);
	~Node();

};
class Graph
{
	bool inOpen(Node*, queue<Node*>);
	bool childExist(Node*, Node*);
public:
	map< Node*, vector<Node*>> adj;
	map <string, int> indices;
	Graph();
	Node* getNode(string);
	void addEdge(string, string);
	void clearVisted();
	void dfs(Node*);
	void bfs(Node*);
	~Graph();
};


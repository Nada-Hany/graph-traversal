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

	enum class StateOfPath {
		CLEAR, COLLISION
	};
	StateOfPath state;
	Node* previous = nullptr;
	map<Node*, vector<pair<string, double>>> transportations;
	string value;

	void setState(StateOfPath);
	StateOfPath getState();
	bool isVisted = false;
	bool transportationExist(Node*, Node*, string);
	void changePrice(vector<pair<string, double>>&, double, string);
	void changeTranspName(vector<pair<string, double>>&, string);
	//void deleteTransportation(vector<pair<string, double>>&);
	//void addTransportation(vector<pair<string, double>>&);
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
	void getAugmentedPath(Node*, Node*, vector<vector<string>>&);
public:
	Node* destination = nullptr;
	map<Node*, vector<Node*>> adj;
	Graph();
	void getPaths(vector<vector<string>>&);
	Node* getNode(string);
	void addEdge(string, string);
	void addEdge(string, string, string, double);
	void clearVisted();
	void dfs(Node*);
	void dfs(Node*, Node*, vector<vector<string>>&);
	void bfs(Node*);
	void clearPrevious();
	~Graph();
};


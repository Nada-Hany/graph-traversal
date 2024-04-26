#include "Graph.h"
#include <iostream>
#include <queue>
#include <map>

using namespace std;

#define el endl

//node class
Node::Node(string val) {
	value = val;
}
bool Node::transportationExist(Node* parent, Node* child, string transp) {
	//if the edge already exist either ways.
	if (parent->transportations.find(child) != parent->transportations.end())
	{
		for (auto t : parent->transportations[child])
			if(t.first == transp)
				return true;
	}
	return false;
}
void Node::changePrice(vector<pair<string, double>>& allTransp, double price, string transp) {
	for (auto& t : allTransp) {
		if (transp == t.first) 
		{
			t.second = price;
			return;
		}
	}
}
void Node::changeTranspName(vector<pair<string, double>>& allTransp, string name) {
	for (auto& t : allTransp) {
		if (name == t.first)
		{
			t.first = name;
			return;
		}
	}
}
void Node::setState(StateOfPath newState) {
	state = newState;
}
Node::StateOfPath Node::getState() {
	return state;
}
Node::~Node() {}

//graph class
Graph::Graph() {}

void Graph::toLowerCase(string& str) {
	string result;
	for (char c : str)
		result += tolower(c);
	str = result;
}
void Graph::addEdge(string node1, string node2, string transp, double price) {
	toLowerCase(node1);
	toLowerCase(node2);
	Node* node2_obj = getNode(node2);
	Node* node1_obj = getNode(node1);

	if (node2_obj == nullptr)
		node2_obj = new Node(node2);
	if (node1_obj == nullptr)
		node1_obj = new Node(node1);
	//if the child doesn't exist -> so as the transportations else i need to check if it already exists
	if (!childExist(node1_obj, node2_obj))
	{
		adj[node1_obj].push_back(node2_obj);
		node1_obj->transportations[node2_obj].push_back(make_pair(transp, price));
	}
	else {
		
	}
	if (!childExist(node2_obj, node1_obj))
	{
		adj[node2_obj].push_back(node1_obj);
		node2_obj->transportations[node1_obj].push_back(make_pair(transp, price));
	}
	//child already exists so we need to check for transportation options;
	
	//else {

	//}

}
void Graph::addEdge(string node1, string node2) {
	toLowerCase(node1);
	toLowerCase(node2);
	Node* node2_obj = getNode(node2);
	Node* node1_obj = getNode(node1);

	if (node2_obj == nullptr) 
		node2_obj = new Node(node2);
	if (node1_obj == nullptr) 
		node1_obj = new Node(node1);
	
	if (!childExist(node1_obj, node2_obj))
		adj[node1_obj].push_back(node2_obj);
	if (!childExist(node2_obj, node1_obj))
		adj[node2_obj].push_back(node1_obj);
}
void Graph::dfs(Node* node) {
	node->isVisted = true;
	cout << node->value << "\t";

	for (Node* child : adj[node])
		if (!(child->isVisted))
			dfs(child);
}
void Graph::dfs(Node* node, Node* dest, vector<vector<string>>& path) {
	node->isVisted = true;
	//cout << node->value << "\t";
	if (node == dest )
		getEachPath(dest, path);
	
	//cout << node->value << "\t";
	for (Node* child : adj[node])
	{	
		//no collision between paths
		if (!(child->isVisted))
		{	
			child->previous = node;
			//if (child == dest && child->previous != nullptr )
			//	getEachPath(child, path);
			//// dest got found by another path 
			//if (child->previous != nullptr && destination != nullptr) {
			//	getAugmentedPath(child, node, path);
			//}
			dfs(child, dest, path);
			child->isVisted = false;
		}
		//cout << el;
	}
}
void Graph::getAugmentedPath(Node* collision, Node* node, vector<vector<string>>& path) {
	vector<string> line;
	Node* tmp = destination;
	line.push_back(destination->value);
	
	while (tmp->value != collision->previous->value) {
		line.push_back(tmp->value);
		tmp = tmp->previous;
	}
	tmp = node;
	while (tmp->previous!=nullptr)
	{
		line.push_back(tmp->value);
		tmp = tmp->previous;
	}
	path.push_back(line);
}

void Graph::getEachPath(Node* dest, vector<vector<string>>& path) {
	destination = dest;
	vector<string> eachPath;
	if (dest->previous == nullptr) 
		eachPath.push_back("destination is start");
	else {
		//cout << "in else\n";
		Node* tmp = dest;
		while (tmp->previous != nullptr) {
			//cout << tmp->previous->value << "  el" <<el;
			eachPath.push_back(tmp->value);
			tmp = tmp->previous;
			if (tmp->previous == nullptr)
			{
				eachPath.push_back(tmp->value);
			}
		}
	}
	path.push_back(eachPath);
}
void Graph::getPaths(vector<vector<string>>& paths) {
	for (auto path : paths) {
		for (int i = path.size() - 1; i >= 0; i--) 
			cout << path[i] << " ";
		cout << el;
	}
}
void Graph::clearPrevious() {
	for (auto n : adj) {
		n.first->previous = nullptr;
		for (auto x : n.second)
			x->previous = nullptr;
	}
}
void Graph::bfs(Node* node) {
	queue<Node*> open;
	open.push(node);
	while (open.size())
	{
		Node* current = open.front();
		open.pop();
		cout << current->value << "\t";
		current->isVisted = true;

		for (Node* child : adj[current])
			if (!child->isVisted && !inOpen(child, open))
				open.push(child);
	}
}
bool Graph::inOpen(Node* node, queue<Node*> open) {
	while (open.size())
	{
		Node* check = open.front();
		open.pop();
		if (check == node)
			return true;
	}
	return false;
}
void Graph::clearVisted() {
	for (auto node : adj)
		node.first->isVisted = false;
}
Node* Graph::getNode(string value) {
	for (auto node : adj) {
		if (node.first->value == value)
			return node.first;
	}
	return nullptr;
}
bool Graph::childExist(Node* parent, Node* child) {
	for (Node* node : adj[parent])
		if (child == node)
			return true;
	return false;
}

Graph::~Graph() {}
#include "Graph.h"
#include <iostream>
#include <queue>

using namespace std;


Node::Node(string val) {
	value = val;
}
Node::~Node() {}

Graph::Graph() {}

void Graph::addEdge(string node1, string node2) {
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
	queue<Node*> tmp;
	while (open.size() != tmp.size()) {
		tmp.push(open.front());
	}
	while (tmp.size())
	{
		Node* check = tmp.front();
		tmp.pop();
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
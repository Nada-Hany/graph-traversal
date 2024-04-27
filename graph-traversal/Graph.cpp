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

//if exists->return index else return -1
int Node::weightExist(Node* parent, Node* child, string weightType) {
	//if the edge already exist either ways.
	if (parent->weights.find(child) != parent->weights.end())
	{
		/*for (auto t : parent->transportations[child])
			if(t.first == weightType)
				return;*/

		for (int i = 0; i < parent->weights[child].size(); i++)
			if (parent->weights[child][i].first == weightType)
				return i;
	}
	return -1;
}
//update el mfrod tkon fel weightValue bs wla type w weightValue ?
void Node::changeWeightValue(vector<pair<string, double>>& allWeights, double weightValue, string weightType) {
	for (auto& t : allWeights) {
		if (weightType == t.first) 
		{
			t.second = weightValue;
			return;
		}
	}
}
void Node::changeWeightType(vector<pair<string, double>>& allweights, string weightType) {
	for (auto& t : allweights) {
		if (weightType == t.first)
		{
			t.first = weightType;
			return;
		}
	}
}

void Node::deleteWeight(Node* parent, Node* child, string weightType) {
	int index = parent->weightExist(parent, child, weightType);
	parent->weights[child].erase(parent->weights[child].begin() + index);
}
void Node::addWeight(Node* parent, Node* child, double weightValue, string weightType) {
	parent->weights[child].push_back(make_pair(weightType, weightValue));
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
//Node*, vector<pair<string, double>> >  <<- transportation stucture
//actions: 1->add a new transp, 2->delete, 3->update 
//hayhsal eh lw ana b add transp already mwgoda? ha3ml update wla a-drop el request
void Graph::addEdge(string node1, string node2, string weightType, double weightValue, int action) {
	toLowerCase(node1);
	toLowerCase(node2);
	toLowerCase(weightType);
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
		node1_obj->weights[node2_obj].push_back(make_pair(weightType, weightValue));
	}
	//child already exists so we need to check for options;
	else {
		switch (action)
		{
		//add
		case 1:
			if (node1_obj->weightExist(node1_obj, node2_obj, weightType) == -1)
				node1_obj->addWeight(node1_obj, node2_obj, weightValue, weightType);
			break;
		//delete
		case 2:
			if (node1_obj->weightExist(node1_obj, node2_obj, weightType) != -1)
				node1_obj->deleteWeight(node1_obj, node2_obj, weightType);
			break;
		//update weightValue
		case 3:
			if (node1_obj->weightExist(node1_obj, node2_obj, weightType) != -1)
				node1_obj->changeWeightValue(node1_obj->weights[node2_obj], weightValue, weightType);
			break;
		default:
			break;
		}

	}
	if (!childExist(node2_obj, node1_obj))
	{
		adj[node2_obj].push_back(node1_obj);
		node2_obj->weights[node1_obj].push_back(make_pair(weightType, weightValue));
	}
	else {
		switch (action)
		{
			//add
		case 1:
			if (node2_obj->weightExist(node2_obj, node1_obj, weightType) == -1)
				node2_obj->addWeight(node2_obj, node1_obj, weightValue, weightType);
			break;
			//delete
		case 2:
			if (node2_obj->weightExist(node2_obj, node1_obj, weightType) != -1)
				node2_obj->deleteWeight(node2_obj, node1_obj, weightType);
			break;
			//update weightValue
		case 3:
			if (node2_obj->weightExist(node2_obj, node1_obj, weightType) != -1)
				node2_obj->changeWeightValue(node2_obj->weights[node1_obj], weightValue, weightType);
			break;
		default:
			break;
		}
	}

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
void Graph::dfs(Node* node) {
	node->isVisted = true;
	cout << node->value << "\t";

	for (Node* child : adj[node])
		if (!(child->isVisted))
			dfs(child);
}
void Graph::dfs(Node* node, Node* dest, vector<vector<string>>& path) {
	node->isVisted = true;
	if (node == dest )
		getEachPath(dest, path);
	
	for (Node* child : adj[node])
	{	
		//no collision between paths
		if (!(child->isVisted))
		{	
			child->previous = node;
			dfs(child, dest, path);
			child->isVisted = false;
		}
	}
}

void Graph::getEachPath(Node* dest, vector<vector<string>>& path) {
	destination = dest;
	vector<string> eachPath;
	if (dest->previous == nullptr) 
		eachPath.push_back("destination is start");
	else {
		Node* tmp = dest;
		while (tmp->previous != nullptr) {
			eachPath.push_back(tmp->value);
			tmp = tmp->previous;
			if (tmp->previous == nullptr)
				eachPath.push_back(tmp->value);
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

bool Graph::checkCompleteness() {
	if (adj.size() != nodesNumber)
		return false;
	for (auto node : adj) 
		if(node.second.size() != nodesNumber - 1)
			return false;
	return true;
}

void Graph::clearPrevious() {
	for (auto n : adj) {
		n.first->previous = nullptr;
		for (auto x : n.second)
			x->previous = nullptr;
	}
}
void Graph::clearVisted() {
	for (auto node : adj)
		node.first->isVisted = false;
}

Graph::~Graph() {}
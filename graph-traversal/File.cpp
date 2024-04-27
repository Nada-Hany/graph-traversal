#include "File.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#define el endl

File::File(string name) {
	path = name;
}
void File::readFile() {
	ifstream file(path);
	string line;
	if (file.is_open()) {
		while (getline(file,line)){
			istringstream ss(line);
			string word;
			vector<string> line;
			while (getline(ss, word, ' ')) 
			{
				if (word == "-")
					continue;
				line.push_back(word);
			}
			data.push_back(line);
			line.clear();
		}
	}
	file.close();
}

void File::convertToObjects(Graph* graph) {

	for (auto line : data) {
		if (line.size() < 2)
		{
			graph->nodesNumber = stod(line[0]);
			continue;
		}
		graph->addEdge(line[0], line[1]);
	}
}
void File::writeOnFile(Graph* graph){
	ofstream file("output.txt");
	vector<pair<string, string>> addedNodes;
	if (file.is_open()) {
		file << graph->nodesNumber << el;
		for (auto node : graph->adj) {
			for (auto node : graph->adj) {
				if ()
			}
		}
	}
	file.close();
}
void File::convertWeights(Graph* graph) {

	for (auto line : data) {
		if (line.size() < 2)
		{
			graph->nodesNumber = stod(line[0]);
			continue;
		}
		else if (line.size() == 2) {
			graph->addEdge(line[0], line[1]);
		}
		else {
			string weightType;
			double weightValue;
			string parent = line[0], child = line[1];
			for (int i = 2; i < line.size()-1; i++) {
				//weightType 1st then weightValue
				if (i % 2 == 0) {
					weightType = line[i];
					weightValue = stod(line[i + 1]);
					graph->addEdge(line[0], line[1], weightType, weightValue, 1);
				}
			}
		}
	}
}
void File::toLowerCase(string& str) {
	string result;
	for (char c : str)
		result += tolower(c);
	str = result;
}

File::~File() {

}

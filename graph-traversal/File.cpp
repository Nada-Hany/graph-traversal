#include "File.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>

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
}
void File::convertToObjects(Graph* graph) {

	for (auto line : data) {
		if (line.size() < 2)
			continue;
		graph->addEdge(line[0], line[1]);
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

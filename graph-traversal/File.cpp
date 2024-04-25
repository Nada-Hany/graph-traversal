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
File::~File() {

}

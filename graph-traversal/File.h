#pragma once
#include <string>
#include <vector>
#include "Graph.h"
using namespace std;

class File
{
	string path;
public:
	vector<vector<string>> data;
	File(string);
	void readFile();
	void convertToObjects(Graph*);
	void toLowerCase(string&);
	~File();
};


#pragma once
#include <string>
#include <vector>
using namespace std;

class File
{
	string path;
public:
	vector<vector<string>> data;
	File(string);
	void readFile();
	~File();
};


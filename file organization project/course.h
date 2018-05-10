#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class course
{
public:
	course(void);
	~course(void);
	void add();
	void show();
	void delete_course(char key[11]);
private:
	string c_code,c_name,c_description;
	stringstream ss1;
	void pack(ofstream &ofile);
	void unpack(fstream &ifile);
	bool search_code(string key);
	void deleter(string key);
};


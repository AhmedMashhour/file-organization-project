#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class student
{
public:
	student(void);
	~student(void);
	void add();
	void show();
	void student::delete_student(char key[11]);
private:
	string id, name,grade,address;
	void display();
	bool search_id(string key);
	void deleter(string key);
};


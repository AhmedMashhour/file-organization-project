#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class registration
{
public:
	registration(void);
	~registration(void);
	void register_student();
	void show_courses(char id[11]);
	void show_students(char code[11]);
	void drop(char key1[11],char key2[11]);
private:
	char id_s[11],code_c[11],buf[21];
	void read_id_code();
	void write(string fn);
	void unpack_courses (char id[11],ifstream &in);
	void unpack_student(char code[11],ifstream &in);
	bool search_id_code(string s, string s2,ifstream &ifile);
	bool search_id(string key);
	bool search_code(string key);
	void delete1(char key[11],char key2[11]);
};


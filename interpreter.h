#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include <string>
#include <map>
#include <vector>
using namespace std;

class Interpreter {
public:
	Interpreter();
	~Interpreter();
	string message(char*);
	string outputConv(int, map<int, char>);

private:
	char* binary;
	string outMsg;
	int wordCount;
	int wordTotal;
	int i;
	int j;
	map<int, char> bitMap1;
	map<int, char> bitMap2;
};

#endif
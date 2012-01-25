#ifndef __SKIPGRAM_H__
#define __SKIPGRAM_H__

#include<iostream>
#include<string>
using namespace std;

class SkipGram {
string w1, w2;

public:
SkipGram();
SkipGram(string, string );
string getw1();
string getw2();
string getSkipGramList();

bool operator()(const int x,const int y) { 
	return (x-y)>0; 
	}
};

#endif

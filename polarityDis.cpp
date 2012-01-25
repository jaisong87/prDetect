#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
using namespace std;

int main()
{
ifstream fin(string("PosNeg").c_str());
ofstream fout(string("polarityDisFeature").c_str());

string line;
while(getline(fin,line))
	{
	double p1, n1, p2, n2, dis;
	for(int i=0;i<line.length();i++)
		if(line[i] == ',') line[i]= ' ';	
	stringstream ss1(line);
	ss1>>p1>>n1>>p2>>n2;
	dis = sqrt((p1-p2)*(p1-p2) + (n1-n2)*(n1-n2));
	double pdis = (sqrt(2)-dis)/(sqrt(2));
	fout<<dis<<","<<endl;
	}
}

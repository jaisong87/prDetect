#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
using namespace std;

int main()
{
ifstream fin(string("PosNegNeutal").c_str());
ofstream fout(string("polarityDisFeature2").c_str());

string line;
while(getline(fin,line))
	{
	double p1, n1, p2, n2,e1,e2, dis;
	for(int i=0;i<line.length();i++)
		if(line[i] == ',') line[i]= ' ';	
	stringstream ss1(line);
	ss1>>p1>>n1>>e1>>p2>>n2>>e2;
	dis = sqrt((p1-p2)*(p1-p2) + (n1-n2)*(n1-n2)+(e1-e2)*(e1-e2));
	double pdis = (sqrt(3)-dis)/(sqrt(3));
	fout<<dis<<","<<endl;
	}
}

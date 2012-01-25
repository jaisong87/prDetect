#include<iostream>
#include<sstream>
#include<string>
using namespace std;

int main()
{
string s, line;
while(getline(cin,line))
	{
	stringstream ss1(line);
	while(ss1>>s)
		{
		cout<<s;
		}
	cout<<endl;
	}

}

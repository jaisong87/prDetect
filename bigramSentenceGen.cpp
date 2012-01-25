#include<iostream>
#include<sstream>
using namespace std;

int main()
{
string line;
string word, tag, S;
while(getline(cin,line))
	{
	stringstream ss1(line);

	while(ss1>>S)
		{
		int pos = S.find('_');
		S[pos]= ' ';
		stringstream ss2(S);
		ss2>>word;
		ss2>>tag;	
		cout<<tag<<' ';
		}
	cout<<endl;
	}
return 0;	
}

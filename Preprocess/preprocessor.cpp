#include<iostream>
using namespace std;

int main()
{
string s;

while(getline(cin,s))
	{
	string str;
	for(int i=0;i<s.length();i++)
		{
		if(isupper(s[i])) str+=tolower(s[i]);
		else str+=s[i];
		}
	cout<<str<<endl;
	}
}

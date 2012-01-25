#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;

void format(string &S)
{
for(int i=0;i<S.size();i++)
	if(S[i]==':') S[i]=' ';
}

int main()
{
int n1, n2, n3, n4 ,n5;

ifstream f1("result2.txt");
ifstream f2("Test1");
ifstream f3("Test2");

string str, str1, str2;

while(getline(f1, str))
	{
	getline(f2,str1);
	getline(f3,str2);
	format(str);
	stringstream ss1(str);
	ss1>>n1>>n2>>n3>>n4>>n5;
	if(n3==0 && n5==1)// && n1<=1742)
			{
			cout<<"Case#"<<n1<<endl;
			cout<<str1<<endl;	
			cout<<str2<<endl;
			cout<<"-----------------------------------------------------------------"<<endl;
			}
	}

return 0;
}

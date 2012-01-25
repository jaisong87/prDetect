#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include "skipGram.h"
#include<set>
using namespace std;

#define TH 0.63
#define MAX 500

void normalize(string &s)
{
int len = s.length();
string seperators = ".;&*()?/!~";
//seperators+='\"';

for(int i=0;i<len;i++)
	{
	char ch = s[i];
	if(seperators.find(ch) != string::npos)
		s[i]=' ';
	}
//if(s[s.length()-1]=='.') s[s.length()-1]=' ';
}

vector<string> getWords(string S1)
{
vector<string> vs1;
stringstream ss1(S1);

string tmp;
while(ss1>>tmp)
	{
	vs1.push_back(tmp);
	}

return vs1;
} 

int main()
{
ifstream fres("ParaResults");
ifstream fs1("ParaSen1");
ifstream fs2("ParaSen2");

ofstream fout("unigramFeature");

int result;
string sen1,sen2;
int rc = 0;

cout<<"---------------------- NonParaphrases with unigramMatch >= 0.63 -----------------------"<<endl;
while(fres>>result)
{
//cout<<sen1<<' '<<sen2<<' '<<result<<endl;
getline(fs1, sen1);
getline(fs2, sen2);

normalize(sen1);
normalize(sen2);

vector<string> v1 = getWords(sen1);
vector<string> v2 = getWords(sen2);

double ugc = 0 ;
int z1 = v1.size(); 
int z2 = v2.size();

for(int i =0;i<z1;i++)
	{
	bool p = false;
	for(int j=0;j<z2;j++)
		{		
		if( (v1[i] == v2[j]))
			p = true;		
		}
	if(p) ugc++;
	}
double zM = max(z1, z2);

double f1 = ugc/zM;

ugc = 0;
for(int i =0;i<z2;i++)
        {
        bool p = false;
        for(int j=0;j<z1;j++)
                {
                if( (v2[i] == v1[j]))
                        p = true;
                }
        if(p) ugc++;
        }

double f2 = ugc/zM;

if(result==0 && (f1>= TH || f2>= TH) )
{
cout<<"Line#1 ("<<f1<<"):"<<sen1<<endl;
cout<<"Line#2 ("<<f2<<"):"<<sen2<<endl;

cout<<"################################################################################################"<<endl;
rc++;
}
/*
fout<<f1<<','<<f2<<","<<endl;
cout<<f1<<','<<f2<<","<<endl;
*/
}
cout<<"There are "<<rc<<" cases "<<endl;

return 0;
}


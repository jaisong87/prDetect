#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include "skipGram.h"
#include<set>
using namespace std;

#define MAX 500

void normalize(string &s)
{
int len = s.length();
string seperators = ";&*()?/!~";

for(int i=0;i<len;i++)
	{
	char ch = s[i];
	if(seperators.find(ch) != string::npos)
		s[i]=' ';
	}
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

//ofstream fout("plainSimilarityFeature");

int result;
string sen1,sen2;

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
int zM = max(z1,z2);

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
int delta = abs(z1-z2);

fout<<f1<<','<<f2<<","<<endl;
cout<<f1<<','<<f2<<","<<endl;
}

return 0;
}


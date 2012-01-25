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
string seperators = ".;&*()?/!~";

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
ifstream fs1("trainS1POS");
ifstream fs2("trainS2POS");

ofstream fout("POSSkipGramFeature");

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

double bgc = 0 ;
int z1 = v1.size(); 
int z2 = v2.size();

set<string> skipGrams1, skipGrams2;
for(int a = 0; a< z1;a++)
	for(int b = a+1;b<z1;b++)
		skipGrams1.insert(v1[a]+"#$"+v1[b]);	

for(int a = 0; a< z2;a++)
	for(int b = a+1;b<z2;b++)
		skipGrams2.insert(v2[a]+"#$"+v2[b]);	


for(int i =0;i<z1;i++)
	for(int j=i+1;j<z1;j++)
		{		
		if(skipGrams2.find(v1[i]+"#$"+v1[j]) != skipGrams2.end()) 
				bgc++;
		}
double f1 = 2*bgc/(z1*(z1-1));
if(z1<2) f1 = 0;

bgc = 0;
for(int i =0;i<z2;i++)
        for(int j=i+1;j<z2;j++)
                {               
                if(skipGrams1.find(v2[i]+"#$"+v2[j]) != skipGrams1.end())
                                bgc++;
        }
double f2 = 2*bgc/(z2*(z2-1));
if(z2<2) f2 = 0;


fout<<f1<<','<<f2<<","<<endl;
cout<<f1<<','<<f2<<","<<endl;
}

return 0;
}


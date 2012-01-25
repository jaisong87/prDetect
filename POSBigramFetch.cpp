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
	bool isTag = true;
	for(int i=0;i<tmp.size();i++)
		if(!(isupper(tmp[i])||tmp[i]=='$')) isTag = false;
	if(isTag)
	vs1.push_back(tmp);
	}

return vs1;
} 

int main()
{
ifstream fres("ParaResults");
ifstream fs1("trainS1POS");
ifstream fs2("trainS2POS");

ofstream fout("POSbigramFeature");

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

for(int i =1;i<z1;i++)
	{
	bool p = false;
	for(int j=1;j<z2;j++)
		{		
		if( (v1[i] == v2[j]) && (v1[i-1] == v2[j-1]))
			p = true;
		}	
		if(p) bgc++; 
	}
double f1 = bgc/z1;

bgc = 0;
for(int j =1;j<z2;j++)
        {
        bool p = false;
        for(int i=1;i<z1;i++)
                {
                if( (v1[i] == v2[j]) && (v1[i-1] == v2[j-1]))
                        p = true;
                }
                if(p) bgc++;
        }
double f2 = bgc/z2;

fout<<f1<<','<<f2<<","<<endl;
cout<<f1<<','<<f2<<","<<endl;
}

return 0;
}


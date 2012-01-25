#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include "skipGram.h"
#include<set>
using namespace std;

#define MAX 500
#define TH 0.85

int getLCS(string X,string Y)
{
        if (Y.length() > X.length())
                swap(X,Y);
        int m = X.length(),n=Y.length();
        vector< vector<int> > c(2, vector<int>(n+1,0));
        int i,j;
        for (i=1;i<=m;i++)
        {
                for (j=1;j<=n;j++)
                {
                        if (X[i-1]==Y[j-1])
                                c[1][j]=c[0][j-1]+1;
                        else
                                c[1][j]=max(c[1][j-1],c[0][j]);
                }
                for (j=1;j<=n;j++)
                        c[0][j]=c[1][j];
        }
        return (c[1][n]);
}

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
ifstream fs1("ParaSen1");
ifstream fs2("ParaSen2");

ofstream fout("nGramFeature");

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

int z1 = v1.size(); 
int z2 = v2.size();

double ngc = 0;

set<string> nGrams;

for(int i=0;i<z1;i++)
	for(int j=i+1;j<z1;j++)
		{
		string str = v1[i];
		for(int k = i+1;k<=j;k++)
			str+="#$"+v1[k];
		nGrams.insert(str);
		}

for(int i=0;i<z2;i++)
        for(int j=i+1;j<z2;j++)
                {
                string str = v2[i];
                for(int k = i+1;k<=j;k++)
                        str+="#$"+v2[k];
                //if(nGrams.find(str)!=nGrams.end()) ngc++;
		
		double bestMatch = 0;
		for(set<string>::iterator itr = nGrams.begin();itr!=nGrams.end();itr++)
			{
			double curMatch = getLCS(*itr, str);
			curMatch/=str.length();
			if(curMatch > bestMatch) bestMatch = curMatch;	
			}
		if(bestMatch > TH) ngc++;
                }

double mZ = max(z1,z2);
double f1 = ngc/mZ;
double f2 = ngc/mZ;

cout<<f1<<','<<f2<<","<<result<<endl;
fout<<f1<<','<<f2<<","<<endl;
}

return 0;
}


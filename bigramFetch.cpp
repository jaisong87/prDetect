#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include "skipGram.h"
#include<algorithm>
#include<set>
using namespace std;

#define MAX 500
#define TH 0.86

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

ofstream fout("bigramFeature");

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

bool use3G = false;

double bgc = 0 ;
int z1 = v1.size(); 
int z2 = v2.size();

if(use3G)
{
	for(int i =2;i<z1;i++)
	{
		bool p = false;
		for(int j=2;j<z2;j++)
		{
			if( (v1[i] == v2[j]) && (v1[i-1] == v2[j-1])&&(v1[i-2]==v2[j-2]) )
				p = true;
		}
		if(p) bgc++;
	}
}

for(int i =1;i<z1;i++)
	{
	bool p = false; //found bigram
	for(int j=1;j<z2;j++)
		{		
                if( getLCS(v1[i],v2[j])>=(TH*v1[i].size())  && getLCS(v1[i-1],v2[j-1])>=(TH*v1[i-1].size()))
			p = true;	
		}
	if(p) bgc++;
	}
/*
for(int a=0;a<z1;a++)
        {
        if(find(v2.begin(),v2.end(),v1[a])!=v2.end()) bgc++;
        }
*/
double f1 = bgc/(z1-1);

bgc = 0;

if(use3G)
{
        for(int i =2;i<z1;i++)
        {
                bool p = false;
                for(int j=2;j<z2;j++)
                {
                        if( (v1[i] == v2[j]) && (v1[i-1] == v2[j-1])&&(v1[i-2]==v2[j-2]) )
                                p = true;
                }
                if(p) bgc++;
        }
}

for(int j =1;j<z2;j++)
        {
        bool p = false; //found bigram
        for(int i=1;i<z1;i++)
                {
                if( getLCS(v1[i],v2[j])>=(TH*v2[j].size())  && getLCS(v1[i-1],v2[j-1])>=(TH*v2[j-1].size()))
                        p = true;
                }
        if(p) bgc++;
        }
/*
for(int a=0;a<z2;a++)
        {
        if(find(v1.begin(),v1.end(),v2[a])!=v1.end()) bgc++;
        }
*/
double f2 = bgc/(z2-1);
double f3 = 0;
if(f1&&f2) f3 = 2*f1*f2/(f1+f2);

int zM = max(z1,z2);
//f1 = bgc/zM;
//f2 = bgc/zM;

fout<<f1<<','<<f2<<","<<f3<<","<<endl;
cout<<f1<<','<<f2<<","<<f3<<","<<endl;
}

return 0;
}


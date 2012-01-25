#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include "skipGram.h"
#include<set>
using namespace std;

#define MAX 500

#define TH 0.60

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
int lc = 0 ;

ifstream fres("ParaResults");
ifstream fs1("ParaSen1");
ifstream fs2("ParaSen2");

ofstream fout("plainSimilarityFeature");

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
	double similarity = 0;
	for(int j=0;j<z2;j++)
		{		
		if(getLCS (v1[i],v2[j])> similarity)
			similarity = getLCS(v1[i],v2[j]);		
		}
	ugc+=similarity/v1[i].length();
	}
int zM = max(z1,z2);

double f1 = ugc/zM;

ugc = 0;
for(int i =0;i<z2;i++)
        {
        double similarity = 0;
        for(int j=0;j<z1;j++)
                {
                if(getLCS(v2[i] ,v1[j])>similarity )
                        similarity = getLCS(v2[i] ,v1[j]);
                }
        ugc+=similarity/v2[i].length();
        }

double f2 = ugc/zM;
if(result == 1 && ( f1<TH || f2<TH) )
	{
	cout<<"Line#1 ("<<f1<<"): "<<sen1<<endl;
	cout<<"Line#2 ("<<f2<<"): "<<sen2<<endl;
	cout<<"------------------------------------------------------------------"<<endl;
	lc++;
	}
/*
fout<<f1<<','<<f2<<","<<endl;
cout<<f1<<','<<f2<<","<<endl;
*/
}

cout<<"There are "<<lc<<" instance "<<endl;
//cout<<getLCS("jaison", "jason")<<endl;
return 0;
}


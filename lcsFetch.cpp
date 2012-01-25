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

/*
double getLCSFeature(vector<string> sen1, vector<string> sen2)
{
int z1 = sen1.size();
int z2 = sen2.size();

int LCS[MAX][MAX];
for(int i=0;i<MAX;i++)
	for(int j=0;j<MAX;j++)
		LCS[i][j] = 0;

for(int i=1;i<MAX;i++)
        for(int j=1;j<MAX;j++)
                LCS[i][j] = 10000;

for(int i=1;i<=z1;i++)
	for(int j=1;j<=z2;j++)
		{
		if(sen1[i-1] == sen2[j-1])
			LCS[i][j] = min(LCS[i][j], 1 + LCS[i-1][j-1]);		

		LCS[i][j] = min(LCS[i][j], 1 + LCS[i][j-1]);
		LCS[i][j] = min(LCS[i][j], 1 + LCS[i-1][j]);
		}
return LCS[z1][z2];
}
*/
double getLCSFeature(vector<string> X,vector<string> Y)
{
        if (Y.size() > X.size())
        	{        //swap(X,Y);
			vector<string> Z = X;
			X = Y;
			Y = Z; 
		}

        int m = X.size(),n=Y.size();
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

int main()
{
ifstream fres("ParaResults");
ifstream fs1("ParaSen1");
ifstream fs2("ParaSen2");

ofstream fout("LCSFeature");

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

double f3 = getLCSFeature(v1, v2)/v1.size();
double f4 = getLCSFeature(v1, v2)/v2.size();

fout<<f3<<','<<f4<<","<<endl;
cout<<f3<<','<<f4<<","<<endl;
}

return 0;
}


#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include "skipGram.h"
#include<set>
using namespace std;

#define MAX 500

bool cmpSkipGram ( SkipGram g1, SkipGram g2) {
        string x =  g1.getw1()+g1.getw2();
        string y =  g2.getw1()+g2.getw2();
        return (x > y ) ;
        }

bool isSameSkipGram( SkipGram g1, SkipGram g2)
{
return (g1.getw1()==g2.getw1())&&(g1.getw2()==g2.getw2());
}

bool (*compare) (SkipGram, SkipGram) = cmpSkipGram;

double getSkipGramCount(vector<string> sen1, vector<string> sen2)
{
int z1 = sen1.size();
int z2 = sen2.size();

set<SkipGram,  bool (*) (SkipGram, SkipGram) > skipGramList(compare);

for(int i=0;i<z1;i++)
	for(int j=i+1;j<z1;j++)
		{
			skipGramList.insert(SkipGram(sen1[i], sen1[j]));
		}

int skipGramMatches = 0;
for(int i=0;i<z2;i++)
        for(int j=i+1;j<z2;j++)
                {
               SkipGram curSkipGram = SkipGram(sen2[i], sen2[j]);
		if(skipGramList.find(curSkipGram) != skipGramList.end() )
				skipGramMatches++;
		 }
return skipGramMatches;
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

ofstream fout("skipGramFeature");

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

double f5 = getSkipGramCount(v1,v2)/v1.size();
double f6 = getSkipGramCount(v1,v2)/v2.size();
 
fout<<f5<<','<<f6<<endl;
cout<<f5<<','<<f6<<endl;
}

return 0;
}


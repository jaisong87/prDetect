#include<iostream>
#include<fstream>
#include<sstream>
#include<set>
#include<vector>
using namespace std;

#define TH 0.75

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

string format(string s)
{
for(int i=0;i<s.length();i++)
	if(isupper(s[i])) s[i]=tolower(s[i]);
return s;
}

int main()
{
ifstream f1("trainS1Tagged");
ifstream f2("trainS2Tagged");

ofstream fout("PNNFeature");

string line;

int tc = 0;
int pNC1 = 0, pNC2= 0;
while(getline(f1,line) )
	{
	tc++; 
	set<string> properNouns;
	//NNP, NNPS
	string word, tag, comb;
	stringstream ss1(line);
	int wc1, wc2;
	wc1=wc2= 0;
		
	while(ss1>>comb)
			{
			int pos = comb.find('_');
			comb[pos] = ' ';
			
			stringstream ss2(comb);
			ss2>>word>>tag;
			if( tag == "NN" || tag == "NNP" || tag =="NNPS")
				{ 
				properNouns.insert(format(word));
				pNC1++;
				}
			wc1++;
			}	

double pnC = 0;

	getline(f2, line);
	stringstream ss2(line);
	
        while(ss2>>comb)
                        {
			wc2++;
                        int pos = comb.find('_');
                        comb[pos] = ' ';
                        
                        stringstream ss2(comb);
                        ss2>>word>>tag;
                        if(tag =="NN" || tag == "NNP" || tag =="NNPS")
                               {
				pNC2++;
				word = format(word);
				int bestMatch = 0; 
				 //if(properNouns.find(word) != properNouns.end() )
				for(set<string>::iterator itr = properNouns.begin(); itr != properNouns.end(); itr++)
					{ 
						if(getLCS(*itr, word) >bestMatch)
							bestMatch = getLCS(*itr, word);
						//cout<<word<<endl;
					}
				if(bestMatch > TH) pnC += double(bestMatch)/word.length();	
				}            
            		}       

double f1 = 0, f2 = 0;
if(pNC1 && pnC) f1 = double(pnC)/wc1;
if(pNC2 && pnC) f2 = double(pnC)/wc2;


fout<<f1<<","<<f2<<","<<endl;
cout<<f1<<","<<f2<<","<<endl;
	}

return 0;
}

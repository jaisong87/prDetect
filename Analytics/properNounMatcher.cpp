#include<iostream>
#include<fstream>
#include<sstream>
#include<set>
using namespace std;

int main()
{
ifstream f1("trainS1Tagged");
ifstream f2("trainS2Tagged");

ofstream fout("PNNFeature");

ifstream f3("ParaResults");
int result;

string line, line1;

int tc = 0;
while(getline(f1,line) )
	{
	f3>>result;
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
			if(tag == "NNP" || tag =="NNPS")
				properNouns.insert(word);
			wc1++;
			}	

int pnC = 0;
	line1 = line;
	getline(f2, line);
	stringstream ss2(line);
	
        while(ss2>>comb)
                        {
			wc2++;
                        int pos = comb.find('_');
                        comb[pos] = ' ';
                        
                        stringstream ss2(comb);
                        ss2>>word>>tag;
                        if(tag == "NNP" || tag =="NNPS")
                               {
				 if(properNouns.find(word) != properNouns.end() )
					{ 
						pnC++;
						//cout<<word<<endl;
					}
				}            
            		}       

double f1 = 0, f2 = 0;

if(wc1) f1 = double(pnC)/wc1;
if(wc2) f2 = double(pnC)/wc2;

fout<<f1<<","<<f2<<endl;
//cout<<f1<<","<<f2<<endl;

if(result = 1 && pnC == 0 ) 
		{
		cout<<"Case#"<<tc<<"("<<pnC<<" out of "<<properNouns.size()<<" )"<<endl;
		cout<<line1<<endl;
		cout<<line<<endl;
		cout<<"-------------------------------------------------------------------------------"<<endl;
		}
	}

return 0;
}

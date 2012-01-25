#include<iostream>
#include<fstream>
#include<vector>
#include<cassert>
#include<sstream>
using namespace std;

int main()
{
ifstream f1pos("trainS1POS");
ifstream f1("ParaSen1");
ofstream fo1("trainS1Tagged");

ifstream f2pos("trainS2POS");
ifstream f2("ParaSen2");
ofstream fo2("trainS2Tagged");

string l1, l2, p1, p2;

int c = 0 ;
while(getline(f1,l1))
	{
	c++;
	getline(f1pos, p1);

	getline(f2,l2);
	getline(f2pos, p2);
	
	vector<string> vl1, vp1, vl2, vp2;		
	string tmp;	

	stringstream ss1(l1);
	while(ss1>>tmp) vl1.push_back(tmp);	

	stringstream ssp1(p1);
	while(ssp1>>tmp) vp1.push_back(tmp);	

	stringstream ss2(l2);
	while(ss2>>tmp) vl2.push_back(tmp);	

	stringstream ssp2(p2);
	while(ssp2>>tmp) vp2.push_back(tmp);	
	
	cout<<" Case "<<c<<endl;
	//if(vl1.size() != vp1.size())
		cout<<vl1.size()<<","<<vp1.size()<<"  : "<<l1<<"---->"<<p1<<endl;

	//if(vl2.size() != vp2.size())
		cout<<vl2.size()<<","<<vp2.size()<<"  : "<<l2<<"---->"<<p2<<endl;

	//assert(vl1.size() != vp1.size());	
	//assert(vl2.size() != vp2.size());
	
	for(int i = 0; i< vl1.size(); i++)
		fo1<<vl1[i]<<"_"<<vp1[i]<<" ";
	fo1<<endl;
	
	
	for(int i = 0; i< vl2.size(); i++)
		fo2<<vl2[i]<<"_"<<vp2[i]<<" ";
	fo2<<endl;
	}
return 0;
}



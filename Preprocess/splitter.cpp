#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

int main()
{
string line;
getline(cin,line); //let this line go

int result;
int t1,t2;
string str;

ofstream fres("ParaResults",ios::app);
ofstream fs1("unpParaSen1",ios::app);
ofstream fs2("unpParaSen2", ios::app);

int cnt = 0;
while(cin>>result /*&& cnt< 9*/)
	{
	cnt++;
	cin>>t1>>t2;
	getline(cin,line);
	fres<<result<<endl;
	cout<<(result?"Paraphrase":"Not a Paraphrase")<<endl;
	//fres<<result<<endl;
	int len = line.length();
	int pos1=1;

	//cout<<pos1<<'.'<<int(line[pos1])<<'.'<<line[pos1]<<'.'<<int(char(' '))<<endl;
	while(pos1<len && line[pos1]!='\t' ) pos1++;

	/*	
	cout<<pos1<<endl;
	while( pos1<len && !(line[pos1]==' ' && line[pos1-1]==' ') ) pos1++;
	cout<<pos1<<endl;
	*/

	string sen1, sen2;
	sen1 = line.substr(1,pos1-1);		
	sen2 = line.substr(pos1+1, len -pos1-1);

	cout<<sen1<<endl<<sen2<<endl;
	cout<<"----------------"<<endl;
	
	fs1<<sen1<<endl;
	fs2<<sen2<<endl;
	}

return 0;
}

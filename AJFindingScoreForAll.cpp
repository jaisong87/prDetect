#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include "editdistance.h"

using namespace std;


struct SVO{
   string subject;
   string object;
   string verb;
};

string findverb(string line)
{
  string s1,s2;
  stringstream ss1(line);
  ss1>>s1>>s2;
  s2.erase(s2.length()-1,1);
  return s2;
}  

string findsub(string line, string verb)
{
  line=line.substr(line.find(verb)+verb.length()+1,line.length());
  line = line.substr(0,line.find("-"));  
  return line; 
}
string findobj(string line, string verb)
{
  line=line.substr(line.find(verb)+verb.length()+1,line.length());
  line = line.substr(0,line.find("-"));  
  return line; 
}

string findsubject(string line)
{
  string subject;
  return subject;
}

SVO* findSVO(string line, string filename)
{
  fstream fp;
  fp.open(filename.c_str());
  string subject="", object="", verb="",v1;
  verb=line.substr(line.find("(")+1, line.length()-1);
  subject=verb.substr(verb.find(" ")+1,verb.length()-1);
  subject=subject.substr(0,subject.find("-"));
  verb=verb.substr(0,verb.find("-"));
  while(getline(fp,line))
   {
    if(line.find(verb)!=line.npos && line.find("dobj")!=line.npos)
     {
       v1=line.substr(line.find("(")+1, line.length()-1);
       object=v1.substr(v1.find(" ")+1,v1.length()-1);
       object=object.substr(0,object.find("-"));
     }
   }
    
  SVO *p;
  p = new SVO;
  p->verb=verb;
  p->object=object;
  p->subject=subject;
  return p;
  
}

int score(string file1, string file2)
{
  string line, v1, processedverb1, processedverb2, v2, s1, s2, o1, o2;
  fstream fp1, fp2, fp3, fp4;
  fp1.open(file1.c_str()); 
  fp2.open(file2.c_str());
  vector<SVO*> first;
  vector<SVO*> second;
   
  while(getline(fp1,line))
  {
    if(line.find("nsubj(")!=line.npos)
     { 
       SVO *a=findSVO(line, file1); 
       first.push_back(a);
     }    
  }   
  while(getline(fp2,line))
  {
    if(line.find("nsubj(")!=line.npos)
     { 
       SVO *a=findSVO(line, file1); 
       second.push_back(a);
     }    
  }
  
  int score=0;
  int max=0;
  int ii1;
   for(ii1=0; ii1 < first.size(); ii1++)
   {
      int ii2;
      score = score+max;
      max = 0;
      for(ii2=0; ii2 < second.size(); ii2++)
      {
	  //cout<<first[ii1]->verb<<" "<<second[ii2]->verb<<endl;
	  //cout<<first[ii1]->subject<<" "<<second[ii2]->subject<<endl;
	  //cout<<first[ii1]->object<<" "<<second[ii2]->object<<endl;
          int maxIter =0;
          if(first[ii1]->verb==second[ii2]->verb && (first[ii1]->verb!="" || second[ii2]->verb!="") )
	   {maxIter++;}
//  	  else
//  	   { 
// 	    if (maxIter>max) {max=maxIter;}
//  	    continue;
// 	   }
	  if(first[ii1]->subject==second[ii2]->subject && (first[ii1]->subject!="" || second[ii2]->subject!=""))
	   {maxIter++;}
	  if(first[ii1]->object==second[ii2]->object && (first[ii1]->object!="" || second[ii2]->object!=""))
	   {maxIter++;}
	   
	  if (maxIter>max) {max=maxIter;}
	  //EDIT-DISTANCE
	  /*if((first[ii1]->verb != "" || second[ii2]->verb != "") )
	  {score=score+edit_distance(first[ii1]->verb.c_str(),second[ii2]->verb.c_str());}
	  if((first[ii1]->subject != "" || second[ii2]->subject != ""))
	  {score=score+edit_distance(first[ii1]->subject.c_str(),second[ii2]->subject.c_str());}
	  if((first[ii1]->object != "" || second[ii2]->object != ""))
	  {score=score+edit_distance(first[ii1]->object.c_str(),second[ii2]->object.c_str());}
	  *///EDIT-DISTANCE
	  
	  //Python Lemmatizer
// 	  string verb = "python Lemma.py 'v' " + first[ii1]->verb; 
// 	  cout<<system(verb.c_str());
// 	  verb1 = 
// 	  verb2 =
// 	  subject1 =
// 	  subject2 = 
// 	  object1 = 
// 	  object2 =
// 	  
// 	  if(system(python first[ii1]->verb) != "" || second[ii2]->verb != "") )
// 	  {score=score+edit_distance(first[ii1]->verb.c_str(),second[ii2]->verb.c_str());}
// 	  if((first[ii1]->subject != "" || second[ii2]->subject != ""))
// 	  {score=score+edit_distance(first[ii1]->subject.c_str(),second[ii2]->subject.c_str());}
// 	  if((first[ii1]->object != "" || second[ii2]->object != ""))
// 	  {score=score+edit_distance(first[ii1]->object.c_str(),second[ii2]->object.c_str());}
	  //Python Lemmatizer
	  
      }
   }

  
   
  return score;
}


int main()
{
  int i=1;string result;
  fstream fp;
  fp.open("ParaResults");
  //cout<<score("Parsedfile979", "2Parsedfile979");
  while(i<=5801 && getline(fp, result))
  {
    
    string line1="Parsedfile", line2="2Parsedfile", s;
    stringstream out;
    out << i;
    s = out.str();
    line1=line1+s;
    line2=line2+s;    
    //cout<<"SENTENCE "<<i<<":";
    cout<<score(line1, line2)<<","<<result<<"\n";  
    
  
//     if (score(line1, line2)==0 && result=="1")
//     {cout<<i<<" ";}
    i++;
  }
return 0;  
}  
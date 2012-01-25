#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include "skipGram.h"
#include<set>
using namespace std;


int main()
{
ifstream fres("ParaResults");

ifstream feature0("unigramFeature");
ifstream feature1("bigramFeature");
ifstream feature2("LCSFeature");
ifstream feature3("skipGramFeature");
ifstream feature4("PNNFeature");
ifstream feature5("synonymFeature");
ifstream feature6("POSbigramFeature");
ifstream feature7("POSSkipGramFeature");
ifstream feature8("PosNeg");
ifstream feature9("SVOagreement");
ifstream feature10("SVOscore2Feature");
ifstream feature11("trigramFeature");
ifstream feature12("polarityDisFeature");
ifstream feature12a("polarityDisFeature2");

ifstream feature13("intelligentSVOED");
ifstream feature14("intellingentSVO1");
ifstream feature15("intellingentSVO2");
ifstream feature16("LunigramFeature");
ifstream feature17("POStrigramFeature");
ifstream feature18("nGramFeature");
ifstream feature19("oldUnigramFeature");
ifstream feature20("plainSimilarityFeature");
ifstream feature20a("stemSimilarityFeature");

ofstream fout("feature.arff");

///////////////////////////// Feature Extraction related Input and Setting ////////////////////////
bool isUnigramRequired = false;
bool isBigramRequired = false;
bool isLCSRequired = false;
bool isSkipGramRequired = false;
bool isPNNRequired = false;
bool isSynonymFeatureRequired = false;
bool isPOSBigramRequired = false;
bool isPOSSkipGramFeature = false;
bool isPolarityRequired = false;
bool isSVOscore1Required = false;
bool isSVOscore2Required = false;
bool isTrigramRequired = false;
bool isPolDisRequired = false;
bool isSVOEDRequired = false;
bool isSVO1Required = false;
bool isSVO2Required = false;
bool isLuniGramRequired = false;
bool isPOSTriGRamRequired = false;
bool isNgramRequired = false;
bool isOldUniGramRequired = false;
bool isPlainSimilarityRequired = false;

char ch;
cout<<"Do you want old unigram(not so well normalized) feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
	isOldUniGramRequired = true;


cout<<"Do you want unigram feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
	isUnigramRequired = true;

cout<<"Do you want bigram feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
	isBigramRequired = true;


cout<<"Do you want LCS feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
        isLCSRequired = true;

cout<<"Do you want skipgram feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
        isSkipGramRequired = true;

cout<<"Do you want properNoun match count feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
        isPNNRequired = true;

cout<<"Do you want Synonym match count feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
        isSynonymFeatureRequired = true;

//isPOSBigramRequired
cout<<"Do you want POSBigram count feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isPOSBigramRequired = true;

//POSSkipGramFeature
cout<<"Do you want POSSkipGram count feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isPOSSkipGramFeature = true;

//POSSkipGramFeature
cout<<"Do you want Polarity feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isPolarityRequired = true;

//isSVOscore2Required
cout<<"Do you want SVO-Agreement#1 feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isSVOscore1Required = true;

//isSVOscore1Required
cout<<"Do you want SVO-Agreement#2 feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isSVOscore2Required = true;

//isTrigramRequired
cout<<"Do you want trigram feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isTrigramRequired = true;

//isPolDisRequired
cout<<"Do you want Polarity Distance(Euclidian) feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isPolDisRequired = true;
/*
//isPolDisRequired
cout<<"Do you want SVOED feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isSVOEDRequired = true;

//isPolDisRequired
cout<<"Do you want SVO1 feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isSVO1Required = true;

//isPolDisRequired
cout<<"Do you want SVO2 feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isSVO2Required = true;


//isPolDisRequired
cout<<"Do you want lematized unigram feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isLuniGramRequired = true;
*/
/////////////////////////////////////
cout<<"Do you want isPOSTriGRamRequired feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isPOSTriGRamRequired = true;

/////////////////////////////////////
cout<<"Do you want nGRam feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isNgramRequired = true;

cout<<"Do you want Plain Similarity feature(y/n)?";
cin>>ch;
if(ch=='y' || ch=='Y')
       isPlainSimilarityRequired = true;

int result;
//string sen1,sen2;
fout<<"@RELATION ParaPhrase"<<endl;

if(isPlainSimilarityRequired)
{
  fout<<"@ATTRIBUTE plainWordSimilarity1  NUMERIC"<<endl;
  fout<<"@ATTRIBUTE plainWordSimilarity2  NUMERIC"<<endl;
  fout<<"@ATTRIBUTE plainWordSimilarityF  NUMERIC"<<endl;
  fout<<"@ATTRIBUTE stemWordSimilairty1  NUMERIC"<<endl;
  fout<<"@ATTRIBUTE stemWordSimilairty2  NUMERIC"<<endl;
  fout<<"@ATTRIBUTE stemWordSimilairtyF  NUMERIC"<<endl;
  fout<<"@ATTRIBUTE deltaSenLen  NUMERIC"<<endl;
}

if(isOldUniGramRequired)
{
	fout<<"@ATTRIBUTE oldUnigram1  NUMERIC"<<endl;
	fout<<"@ATTRIBUTE oldUnigram2  NUMERIC"<<endl;
}

if(isUnigramRequired) {
		fout<<"@ATTRIBUTE unigram1  NUMERIC"<<endl;
		fout<<"@ATTRIBUTE unigram2  NUMERIC"<<endl;
		     }

if(isBigramRequired) {
		fout<<"@ATTRIBUTE bigram1  NUMERIC"<<endl;
		fout<<"@ATTRIBUTE bigram2  NUMERIC"<<endl;
		fout<<"@ATTRIBUTE bigramF  NUMERIC"<<endl;
		     }
if(isLCSRequired)
		{
		fout<<"@ATTRIBUTE wordLevelLCS1 NUMERIC"<<endl;
		fout<<"@ATTRIBUTE wordLevelLCS2 NUMERIC"<<endl;
		}

if(isSkipGramRequired)
		{
		fout<<"@ATTRIBUTE skipGram1 NUMERIC"<<endl;
		fout<<"@ATTRIBUTE skipGram2 NUMERIC"<<endl;
		}

if(isPNNRequired)
                {
                fout<<"@ATTRIBUTE PNNCount1 NUMERIC"<<endl;
                fout<<"@ATTRIBUTE PNNCount2 NUMERIC"<<endl;
                }

if(isSynonymFeatureRequired)
                {
                fout<<"@ATTRIBUTE SynonymCount1 NUMERIC"<<endl;
                fout<<"@ATTRIBUTE SynonymCount2 NUMERIC"<<endl;
                }

if(isPOSBigramRequired)
                {
                fout<<"@ATTRIBUTE POSBigram1 NUMERIC"<<endl;
                fout<<"@ATTRIBUTE POSBigram2 NUMERIC"<<endl;
                }

if(isPOSSkipGramFeature)
	{
		fout<<"@ATTRIBUTE POSSkipGram1 NUMERIC"<<endl;
		fout<<"@ATTRIBUTE POSSkipGram2 NUMERIC"<<endl;
	}

if(isPolarityRequired)
	{
		fout<<"@ATTRIBUTE PositivePol1 NUMERIC"<<endl;
		fout<<"@ATTRIBUTE NegativePol1 NUMERIC"<<endl;
		fout<<"@ATTRIBUTE PositivePol2 NUMERIC"<<endl;
		fout<<"@ATTRIBUTE NegativePol2 NUMERIC"<<endl;	
	}

if(isSVOscore1Required)
{
	fout<<"@ATTRIBUTE IntelligentSVO NUMERIC"<<endl;
}

if(isSVOscore2Required)
{
	fout<<"@ATTRIBUTE SVOAgreement2 NUMERIC"<<endl;
}

if(isTrigramRequired)
{
	fout<<"@ATTRIBUTE trigramFeature1 NUMERIC"<<endl;
	fout<<"@ATTRIBUTE trigramFeature2 NUMERIC"<<endl;
}

if(isPolDisRequired)
{
	fout<<"@ATTRIBUTE polarityDistance NUMERIC"<<endl;
	fout<<"@ATTRIBUTE CompletepolarityDistance NUMERIC"<<endl;
}

if(isSVOEDRequired)
{
	fout<<"@ATTRIBUTE SVOED NUMERIC"<<endl;
}

if(isSVO1Required)
{
	fout<<"@ATTRIBUTE SVO1 NUMERIC"<<endl;
}


if(isSVO2Required)
{
	fout<<"@ATTRIBUTE SVO2 NUMERIC"<<endl;
}

if(isLuniGramRequired)
{
	fout<<"@ATTRIBUTE Lunigram1 NUMERIC"<<endl;
	fout<<"@ATTRIBUTE Lunigram2 NUMERIC"<<endl;
}

if(isPOSTriGRamRequired)
{
fout<<"@ATTRIBUTE POSTrigram1 NUMERIC"<<endl;
fout<<"@ATTRIBUTE POSTrigram2 NUMERIC"<<endl;
}

if(isNgramRequired)
{
fout<<"@ATTRIBUTE nGram1 NUMERIC"<<endl;
fout<<"@ATTRIBUTE nGram2 NUMERIC"<<endl;
}

fout<<"@ATTRIBUTE class {0,1}"<<endl;
fout<<"@DATA"<<endl;

while(fres>>result)
{
string featureValue;
int fc = 0;

if(isPlainSimilarityRequired)
{
 	feature20>>featureValue;
        fout<<featureValue;
	feature20a>>featureValue;
	fout<<featureValue;
        fc++;
}

if(isOldUniGramRequired)
	{
	feature19>>featureValue;
	fout<<featureValue;
	fc++;
	}

if(isUnigramRequired) {
                	feature0>>featureValue;
			fout<<featureValue;    
			fc++;
		 }

if(isBigramRequired) {
                	feature1>>featureValue;
			fout<<featureValue;    
			fc++;
		 }
if(isLCSRequired)
                {
			//if(fc) fout<<",";
		       feature2>>featureValue;
                        fout<<featureValue;
               		fc++;
		 }

if(isSkipGramRequired)
                {
	   //if(fc) fout<<",";
                       feature3>>featureValue;
                        fout<<featureValue;
               		fc++;
		 }

if(isPNNRequired)
                {
           //if(fc) fout<<",";
                       feature4>>featureValue;
                        fout<<featureValue;
              		fc++;
		  }
//isSynonymFeatureRequired
if(isSynonymFeatureRequired)
                {
           //if(fc) fout<<",";
                       getline(feature5,featureValue);
                        fout<<featureValue;
              		fout<<",";
			fc++;
		  }

//isPOSBigramRequired
if(isPOSBigramRequired)
                {
           //if(fc) fout<<",";
                       feature6>>featureValue;
                        fout<<featureValue;
                        fc++;
                  }

if(isPOSSkipGramFeature)
                {
           //if(fc) fout<<",";
                       feature7>>featureValue;
                        fout<<featureValue;
                        fc++;
                  }

if(isPolarityRequired)
	{
 //if(fc) fout<<",";
                       feature8>>featureValue;
                        fout<<featureValue;
                        fout<<",";
			fc++;
	}

if(isSVOscore1Required)
	{
 //if(fc) fout<<",";
                       feature9>>featureValue;
                        fout<<featureValue;
                        fc++;
	}

if(isSVOscore2Required)
	{
 //if(fc) fout<<",";
                       feature10>>featureValue;
                        fout<<featureValue;
                        fc++;
	}

if(isTrigramRequired)
	{
 //if(fc) fout<<",";
                       feature11>>featureValue;
                        fout<<featureValue;
                        fc++;
	}

if(isPolDisRequired)
	{
 //if(fc) fout<<",";
                       feature12>>featureValue;
                        fout<<featureValue;
                       feature12a>>featureValue;
                        fc++;
                        fout<<featureValue;
	}

if(isSVOEDRequired)
	{
// if(fc) fout<<",";
                       feature13>>featureValue;
                        fout<<featureValue<<",";
                        fc++;
	}

if(isSVO1Required)
	{
         //  if(fc) fout<<",";
                       feature14>>featureValue;
                        fout<<featureValue;
                        fc++;
	}

if(isSVO2Required)
	{
          // if(fc) fout<<",";
                       feature15>>featureValue;
                        fout<<featureValue;
                        fc++;
	}

if(isLuniGramRequired)
	{
         //  if(fc) fout<<",";
                       feature16>>featureValue;
                        fout<<featureValue;
                        fc++;
	}

if(isPOSTriGRamRequired)
	{
           //if(fc) fout<<",";
                        feature17>>featureValue;
                        fout<<featureValue;
                        fc++;
	}

if(isNgramRequired)
{
        feature18>>featureValue;
        fout<<featureValue;
        fc++;
}

fout<</*","<<*/result<<endl;
}

return 0;
}


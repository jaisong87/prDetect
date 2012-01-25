#include "skipGram.h"

SkipGram::SkipGram()
{
}

SkipGram::SkipGram(string wa, string wb) : w1(wa) , w2(wb)
{
}

string SkipGram::getw1()
{
return w1;
}

string SkipGram::getw2()
{
return w2;
}

string SkipGram::getSkipGramList()
{
return w1+"/"+w2;
}

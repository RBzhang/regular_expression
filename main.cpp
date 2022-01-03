#include<string>
#include"suffix.h"
#include"NFA.h"
#include"DFA.h"
#include"MinDfa.h"
#include"ismatch.h"
#include<iostream>
#include<fstream>
using namespace std;
int main(){
    ifstream theRe , theString; 
    theRe.open("theRe.txt",ios::in);
    theString.open("theString.txt",ios::in);
    ismatch(theRe, theString);
    return 0;
}
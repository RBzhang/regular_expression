#include"ismatch.h"

void ismatch(std::ifstream& theRe , std::ifstream& theString){
    std::string s1;
    getline(theRe,s1);
    theRe >> s1;
    std::cout << "the Re is \""<< s1 << "\""<<std::endl;
    std::string s2;
    MinDfa* theMin = new MinDfa(s1);
    while(getline(theString,s2)){
        theString >> s2;
        std::cout << s2 << std::endl;
        if(theMin -> ismatch(s2)){
            std::cout << "match!" << std::endl;
        }
        else{
            std::cout << "not Match!" << std::endl;
        }
    }
    delete theMin;
}
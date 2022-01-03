#ifndef _MINDFA_H
#define _MINDFA_H
#include"DFA.h"
#include<vector>
// #include<set>
// #include<map>
class MinDfa{
private:
    DfaState* begin;
    std::vector<DfaState*> mp;  
public:
    MinDfa(DfaCreate* node);
    MinDfa(const std::string& s);
    ~MinDfa();
    bool ismatch(const std::string&);
};

#endif
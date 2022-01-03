#ifndef _DFA_H
#define _DFA_H
#include<vector>
#include<map>
#include<string>
#include<set>
#include"NFA.h"
class DfaState{
private:
    int index;
    bool target;
    std::map<char,DfaState*> mp;
public:
    DfaState(int index):index(index),target(false){}
    const int& getindex() const{return this -> index;}
    bool istarget() const{return this -> target;}
    void settarget(bool t){this -> target = t;}
    void setmap(char, DfaState*);
    bool isexist(const char& c);
    DfaState* operator[](const char& c) const{return this -> mp.find(c) -> second;}
    const std::map<char,DfaState*>& getmp() const{return this -> mp;}
    void insert(char c , DfaState* n);
};

class DfaCreate{
private:
    DfaState* begin;
    std::vector<DfaState*> Dfa;
    bool dfs(const NFA* nfa_node,std::vector<bool>& label, const NfaState* node);
    std::string toString(std::vector<bool>& label);
    std::set<char> Che;
public:
    const DfaState* getbegin() const{return this -> begin;}
    DfaState* operator[](const int& i) const{return this -> Dfa[i];}
    int getsize() const{return Dfa.size();}
    DfaCreate(const NFA* );
    DfaCreate(const std::string& );
    ~DfaCreate();
    const std::set<char>& getChe() const{return this -> Che;}
    bool ismatch(const std::string& );
};

#endif
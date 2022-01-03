#ifndef _NFA_H
#define _NFA_H
#include<vector>
#include<set>
#include<string>
class NfaState{
private:
    int index;
    int next;
    char bridge;
    std::vector<int> mp;
public:
    const int& operator[](const int& i) const{return mp[i];}
    NfaState(int index, int next, char bridge): index(index) , next(next), bridge(bridge) {}
    NfaState(int index): index(index) , next(-1), bridge('#') {}
    void insert(int num);
    const int& get_index() const{return this -> index;}
    const int& get_next() const{return this -> next;}
    const char& get_bridge() const{return this -> bridge;}
    const std::vector<int>& get_mp() const{return this -> mp;}
};

struct nfa{
    NfaState* first;
    NfaState* next;
};

class NFA{
private:
    NfaState* begin;
    NfaState* target;
    std::vector<NfaState*> collec;
    std::set<char> che;
    bool ismatch(NfaState* begin_in, const std::string& s , int index);
public:
    NFA(const std::string& );
    ~NFA();
    const int getsize() const{return collec.size();}
    const NfaState* operator[](const int& i) const{return this -> collec[i];}
    NfaState* getbegin() const{return this -> begin;}
    NfaState* gettarget() const{return this -> target;}
    const std::vector<NfaState*>& getCollec() const{return this -> collec;}
    const std::set<char>& getChe() const{return this -> che;}
    bool match_in(const std::string& );
};

#endif
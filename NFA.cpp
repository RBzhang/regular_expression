#include"NFA.h"
#include"suffix.h"
#include<stack>
//#include<string>
//#include<set>
//#include<vector>
#include<queue>
//#include<iostream>
using namespace std;
void NfaState::insert(int num){
    this ->mp.push_back(num);
}
bool NFA::ismatch(NfaState* begin_in, const string& s , int index){
    int length = s.size();
    if(index == length && begin_in == target) return true;
    else if(index == length && begin_in != target){
        for(auto& i : begin_in -> get_mp()){
            if(ismatch(collec[i], s , index)){
                return true;
            }
        }
    }
    else{
        if(begin_in -> get_bridge() == s[index]){
            if(ismatch(collec[begin_in -> get_next()] , s , index + 1)){
                return true;
            }
        }
        for(auto& i : begin_in -> get_mp()){
            if(ismatch(collec[i] , s , index)){
                return true;
            }
        }
    }
    return false;
}
bool NFA::match_in(const string& s){
    return ismatch(this -> begin,s,0);
}
NFA::~NFA(){
    for(int i = 0;i < collec.size(); ++ i){
        delete collec[i];
    }
}
NFA::NFA(const string& s){
    Suffix* suf = new Suffix(s);
    const string ss = suf -> getstr();
        int count = 0;
        stack<nfa*> store;
//        cout << "t " << ss << endl;
        /*计算NFA*/
        for(auto& c : ss){
            if(suf -> isw(c)){
                che.insert(c);
                NfaState* n1 = new NfaState(count,count + 1, c);
                ++ count;
                NfaState* n2 = new NfaState(count);
                ++ count;
                nfa* node = new nfa;
                node -> first = n1;
                node -> next = n2;
                if(store.empty()){
                    begin = n1;
                }
                target = n2;
                store.push(node);
                collec.push_back(n1);
                collec.push_back(n2);
            }
            else if(c == '&'){
                nfa* node1 = store.top();
                store.pop();
                nfa* node2 = store.top();
                store.pop();
                node2 -> next -> insert(node1 -> first -> get_index());
                node2 -> next = node1 -> next;
                if(store.empty()){
                    begin = node2 -> first;
                }
                target = node1 -> next;
                store.push(node2);
                delete node1;
            }
            else if(c == '|'){
                nfa* node1 = store.top();
                store.pop();
                nfa* node2 = store.top();
                store.pop();
                NfaState* n1 = new NfaState(count);
                collec.push_back(n1);
                ++ count;
                NfaState* n2 = new NfaState(count);
                collec.push_back(n2);
                ++ count;
                nfa* node = new nfa;
                node -> first = n1;
                node -> next = n2;
                n1 -> insert(node1 -> first -> get_index());
                n1 -> insert(node2 -> first -> get_index());
                node1 -> next -> insert(n2 -> get_index());
                node2 -> next -> insert(n2 -> get_index());
                if(store.empty()){
                    begin = node -> first;
                }
                target = node -> next;
                store.push(node);
                delete node1;
                delete node2;
            }
            else{
                nfa* topp = store.top();
                store.pop();
                NfaState* n1 = new NfaState(count);
                collec.push_back(n1);
                ++ count;
                NfaState* n2 = new NfaState(count);
                collec.push_back(n2);
                ++ count;
                n1 -> insert(n2 -> get_index());
                nfa* node = new nfa;
                node -> first = n1;
                node -> next = n2;
                topp -> next -> insert(n2 -> get_index());
                topp -> next -> insert(topp -> first -> get_index());
                n1 -> insert(topp -> first -> get_index());
                if(store.empty()){
                    begin = node -> first;
                }
                target = node -> next;
                store.push(node);
                delete topp;
            }
        }
        nfa* del = store.top();
        store.pop();
        delete del;
}
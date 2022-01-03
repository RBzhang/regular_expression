#include"NFA.h"
#include"DFA.h"
#include<queue>
#include<iostream>
using namespace std;
bool DfaState::isexist(const char& c){
    return mp.find(c) != mp.end();
}

void DfaState::setmap(char c , DfaState* node){
    this -> mp[c] = node;
}
void DfaState::insert(char c , DfaState* n){
    mp[c] = n;
}
bool DfaCreate::dfs(const NFA* nfa_node,vector<bool>& label, const NfaState* node){
        bool result = false;
        if(node == nfa_node -> gettarget()){
            result = true;
        }
        label[node -> get_index()] = true;
        for(auto& i : node -> get_mp()){
            if(!label[i]){
                if(dfs(nfa_node,label,(*nfa_node)[i])){
                    result = true;
                }
            }
        }
        return result;
}
string DfaCreate::toString(vector<bool>& label){
        string result;
        for(int index = 0; index < label.size();++ index){
            if(label[index]){
                int n = index;
                string s = to_string(index);
                for(auto& i : s){
                    result.push_back(i);
                }
            }
        }
        return result;
}

bool DfaCreate::ismatch(const string& s){
    DfaState* node = begin;
    for(int index = 0; index < s.size(); ++ index){
        if(!(node -> isexist(s[index]))){
//            cout << "n1 "<<index << endl;
            return false;
        }
        else{
//            cout << "n2 "<<index << endl;
            node = (*node)[s[index]];
        }
    }
    return node -> istarget();
}
DfaCreate::DfaCreate(const NFA* nfa_node){
        int count = 0;
        map<string,DfaState*> memory;
        vector<bool> label(nfa_node -> getsize(),false);
        DfaState* node = new DfaState(0);
        queue<DfaState*> que;
        queue<vector<int>> q;
        begin = node;
        node -> settarget(dfs(nfa_node,label,nfa_node -> getbegin()));
        string mm = (toString(label));
        memory[mm] = node;
        vector<int> num_q;
        for(int i = 0 ; i < label.size(); ++ i){
            if(label[i]){
//                node -> store.push_back(i);
                num_q.push_back(i);
            }
        }
        Dfa.push_back(node);
        q.push(num_q);
        que.push(node);
//        num_q.swap(vector<int>());
        vector<int>().swap(num_q);
        while(!que.empty()){
            DfaState* n = que.front();
            que.pop();
            for(auto i = nfa_node -> getChe().begin(); i != nfa_node -> getChe().end(); ++ i){
                Che.insert(*i);
//                cout << *i << endl;
                for(int ned = 0 ;  ned < label.size(); ++ ned){
                    label[ned] = false;
                }
                bool alart = false;
                for(auto& j : q.front()){
                    if((*nfa_node)[j] -> get_bridge() == *i){
//                        cout << "cxk    "<< *i << endl;
                        if(dfs(nfa_node,label,(*nfa_node)[(*nfa_node)[j] -> get_next()])) alart = true;
                    }
                }
                
                string mid = toString(label);
                if(mid.size() != 0 && memory.find(mid) == memory.end()){
                    
                    DfaState* p = new DfaState( ++ count);
                    Dfa.push_back(p);
                    memory[mid] = p;
                    for(int k = 0 ; k < label.size(); ++ k){
                        if(label[k]){
                            num_q.push_back(k);
                        }
                    }
                    q.push(num_q);
                    vector<int>().swap(num_q);
//                    n -> mp[*i] = p;
                    n -> setmap(*i , p);
                    if(alart) p -> settarget(true) ;
                    que.push(p);
                }
                else{
                    if(mid.size() != 0)n -> setmap(*i , memory[mid]);
//                    n -> mp[*i] = memory[mid];
                    
                }
            }
            q.pop();
        }
}
DfaCreate::DfaCreate(const string& s){
    NFA* m = new NFA(s);
    new (this) DfaCreate(m);
    delete m;
}

DfaCreate::~DfaCreate(){
    for(int index = 0; index < Dfa.size(); ++ index){
        delete Dfa[index];
    }
}
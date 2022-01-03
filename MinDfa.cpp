#include"MinDfa.h"
#include<set>
#include<map>
using namespace std;

MinDfa::MinDfa(DfaCreate* node){
        int count = 0;
        int begin_num = 0;
        vector<set<int>> mid(2,set<int>());
        vector<int> label(node -> getsize(),1);
        for(int index = 0; index < label.size(); ++ index){
            if((*node)[index] -> istarget()){
                label[index] = 0;
                mid[0].insert(index);
                
            }
            else{
                mid[1].insert(index);
                count = 1;
            }
        }
        bool alart = true;
        while(alart && count > 0){
            alart = false;
            for(auto i = node ->getChe().begin(); i != node ->getChe().end(); ++ i){
                for(auto j = mid.begin(); j != mid.end(); ++ j){
                    int start = label[*((*j).begin())];
                    map<int,int> cmpio;
                    int c = 0;
                    for(auto index = (*j).begin(); index != (*j).end(); ++ index){
                        if(!(*node)[*index] -> isexist(*i) && c == 0){
                            cmpio[-1] = c ++; 
                        }
                        else if(!(*node)[*index] -> isexist(*i) && c != 0){
                            ;
                        }
                        else{
                            if(cmpio.find(label[(*((*node)[*index]))[*i] -> getindex()]) == cmpio.end()){
                                cmpio[label[(*((*node)[*index]))[*i] -> getindex()]] = c ++ ;
                            }
                            else{
                                ;
                            }
                        }
                    }
                    if(c != 1){
                        alart = true;
                        for(auto index = (*j).begin(); index != (*j).end(); ++ index){
                        
                            
                            if(!(*node)[*index] -> isexist(*i)){
                                label[*index] = start;

                            }
                            else{
                                if(cmpio[label[(*((*node)[*index]))[*i] -> getindex()]] == 0){
                                    label[*index] = start;
                                }
                                else{
                                    label[*index] = count + cmpio[label[(*((*node)[*index]))[*i] -> getindex()]];
                                }
                            }
                        }
                    
                    } 
                    count = count + c - 1;
                }
                vector<set<int>> swap_mid(count + 1, set<int>());
                    for(int i = 0 ; i < mid.size(); ++ i){
                        for(auto j = mid[i].begin(); j != mid[i].end(); ++ j){
                            swap_mid[label[*j]].insert(*j);
                            if(*j == 0){
                                begin_num = label[*j];
                            }
                        }
                    }
                    mid.swap(swap_mid);
            }
        }
//        cout << "begin_num  "<< begin_num<<endl;
        mp.resize(count +1, nullptr);
        for(int i = 0; i < mp.size(); ++ i){
            mp[i] = new DfaState(i);
        }
            for(int i = 0; i <= count ; ++ i){
                DfaState* n = (*node)[*(mid[i].begin())];

                for(auto j = n -> getmp().begin() ; j != n -> getmp().end(); ++ j){
//                    mp[i] -> mp[j -> first] = mp[label[j -> second -> index]];
                    mp[i] -> insert(j -> first, mp[label[j -> second -> getindex()]]);
                }
                mp[i] -> settarget(n -> istarget()) ;
            }
            begin = mp[begin_num];    
}
MinDfa::MinDfa(const string& s){
    DfaCreate* node = new DfaCreate(s);
    new (this) MinDfa(node);
    delete node;
}

MinDfa::~MinDfa(){
    for(int index = 0; index < mp.size(); ++ index){
        delete mp[index];
    }
}

bool MinDfa::ismatch(const string& s){
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
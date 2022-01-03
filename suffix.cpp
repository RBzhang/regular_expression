#include<stack>
#include"suffix.h"
using namespace std;

const string& Suffix::getstr() const{return this -> str;}
bool Suffix::isw(const char& c){
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
int Suffix::sear(const char& c){
    int result = 0;
    switch(c){
        case ')':
            result = 0;
            break;
        case '|':
            result = 1;
            break;
        case '&':
            result = 2;
            break;
        case '*':
            result = 3;
            break;
        case '(':
            result = 4;
            break;
        default:
            result = 4;
    }
    return result;
}
Suffix::Suffix(const string& s){
//        stack<nfa*> store;
        stack<char> ops;
//        mid = nullptr;
        
        string ss;
        ss.push_back('(');
        if(!s.empty() ){
            ss.push_back(s[0]);
        }
        for(int i = 0;i < s.size() - 1; ++ i){ 
            if((isw(s[i + 1]) && (s[i] != '|' && s[i] != '(')) || (s[i + 1]=='(' &&(s[i] != '|') )){
                ss.push_back('&');
            }
            ss.push_back(s[i + 1]);
        }
        ss.push_back(')');
//        cout << str<< endl;
        //转换为后缀表达式
        for(auto& c : ss){
            if(isw(c)){
//                che.insert(c);
                this -> str.push_back(c);
            }
            else{
                if(ops.empty()){
                    ops.push(c);
                    continue;
                }
                if(sear(c) > sear(ops.top()) || c == '('){
                    ops.push(c);
                }
                else{
                    while(!ops.empty() && sear(c) <= sear(ops.top())){
                        if(ops.top() == '&' || ops.top() == '|'){
                            this -> str.push_back(ops.top());
//                            ops.pop();
                        }
                        else if(ops.top() == '*'){
                            this -> str.push_back('*');
//                            ops.pop();
                        }
                        else{
                            break;
                        }
                        ops.pop();
                    }
                    if(!ops.empty() && ops.top() == '(' && c == ')'){
                        ops.pop();
                    }
                    else{
                        ops.push(c);
                    }
                }
            }
//            cout << ss << endl;
        }
}
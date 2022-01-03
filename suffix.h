#ifndef _SUFFIX_H
#define _SUFFIX_H
#include<string>
class Suffix{
private:
    std::string str;
    
    int sear(const char& );
public:
    bool isw(const char& );
    const std::string& getstr() const;
    Suffix(const std::string&);
};

#endif
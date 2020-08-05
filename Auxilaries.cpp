#include "Auxilaries.h"

std::string rtrim(std::string &str){
    if(str.empty()){
        return str;
    }
    std::string r_trimmed(str);
    for(int i = r_trimmed.length() - 1; i > 0 and isspace(str[i]); i--){
        r_trimmed.pop_back();
    }
    return r_trimmed;
}

std::string ltrim(std::string &str){
    if(str.empty()){
        return str;
    }
    std::string l_trimmed(str);
    for(int i = 0; l_trimmed.length() and isspace(str[i]); i++){
        l_trimmed.erase(0,1);
    }
    return l_trimmed;
}

std::string trim(std::string& str){
    std::string r_trimmed(str);
    return ltrim(r_trimmed);
}

bool startsWith(std::string& str, std::string sub_str){
    return str.find(sub_str) == 0;
}

bool endsWith(std::string& str, std::string sub_str){
    return str.find(sub_str) == str.length() - sub_str.length();
}

#include "Auxilaries.h"

std::string right_trim(std::string str){
    if(str.empty()){
        return str;
    }
    std::string r_trimmed(str);
    for(int i = r_trimmed.length() - 1; i > 0 and isspace(str[i]); i--){
        r_trimmed.pop_back();
    }
    return r_trimmed;
}

std::string left_trim(std::string str){
    if(str.empty()){
        return str;
    }
    std::string l_trimmed(str);
    for(int i = 0; l_trimmed.length() and isspace(str[i]); i++){
        l_trimmed.erase(0,1);
    }
    return l_trimmed;
}

std::string trim(std::string str){
    std::string r_trimmed = right_trim(str);
    return left_trim(r_trimmed);
}

std::string getInner(std::string& str){
    if(str[0] == '(' and str[str.length() - 1] == ')'){
        std::string inner = str.substr(1);
        inner.pop_back();
        return inner;
    }
    return str;
}

bool startsWith(std::string str, std::string sub_str){
    return str.find(sub_str) == 0;
}

bool endsWith(std::string str, std::string sub_str){
    return str.find(sub_str) == str.length() - sub_str.length();
}

bool isLegalOperator(char c){
    if(c == '+' or c == '-' or c == '^' or c == '*'){
        return true;
    }
    return false;
}

int numOfOccurences(const std::string& str, char ch){
    int cnt = 0;
    for (const char c : str){
        if(c == ch){
            cnt++;
        }
    }
    return cnt;
}

size_t findOperatorIndex(std::string& s){
    for(auto c : s){
        if(c == '+' or c == '-' or c == '*' or c == '^'){
            return s.find(c);
        }
    }
    throw CommandNotInFormat();
}

void checkFileName(std::string file_name){
    if(file_name.empty()){
        throw InvalidFileName();
    }
    for(auto c : file_name){
        if(c == '(' or c == ')' or c == ','){
            throw InvalidFileName();
        }
    }
}

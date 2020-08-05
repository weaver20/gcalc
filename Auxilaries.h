#ifndef GCALC_AUXILARIES_H
#define GCALC_AUXILARIES_H

#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <memory>
#include <set>
#include <utility>
#include <algorithm>
#include <iterator>


typedef enum WORKMODE {INTERACTIVE, BATCH} Mode;

std::set<std::string> CALC_FUNTIONS = {"print", "delete", "who", "reset", "quit"};

bool startsWith(std::string& str, std::string sub_str);

bool endsWith(std::string& str, std::string sub_str);

std::string rtrim(std::string& str);

std::string ltrim(std::string& str);

std::string trim(std::string& str);























#endif //GCALC_AUXILARIES_H

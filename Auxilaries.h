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
#include <cctype>
#include "CalcException.h"
#include "GraphException.h"
#include "Graph.h"


typedef enum WORKMODE {INTERACTIVE, BATCH} Mode;

const std::set<std::string> SAVED_CALC_FUNCS = {"print", "delete", "who", "reset", "quit"};

bool startsWith(std::string str, std::string sub_str);

bool endsWith(std::string str, std::string sub_str);

std::string rtrim(std::string str);

std::string ltrim(std::string str);

std::string trim(std::string str);

size_t findOperatorIndex(std::string&);

int numOfOccurences(const std::string& str, char ch);
























#endif //GCALC_AUXILARIES_H

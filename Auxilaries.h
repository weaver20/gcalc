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
#include <cctype>
#include "GraphException.h"
#include "Graph.h"

typedef enum {INTERACTIVE, BATCH} Mode;

const std::set<std::string> SAVED_CALC_FUNCS = {"print", "delete", "who", "reset", "quit"};

bool startWith(std::string str, std::string sub_str);

bool endWith(std::string str, std::string sub_str);

bool isLegalOperator(char c);

std::string right_trim(std::string str);

std::string left_trim(std::string str);

std::string trim(std::string str);

std::string getInner(std::string&);

size_t findOperatorIndex(std::string&);

int numOfOccurences(const std::string& str, char ch);

void checkFileName(std::string);
























#endif //GCALC_AUXILARIES_H

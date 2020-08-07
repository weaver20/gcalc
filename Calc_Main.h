#ifndef GCALC_CALC_MAIN_H
#define GCALC_CALC_MAIN_H


#include "Calc.h"
#include "Auxilaries.h"
#include "Graph.h"
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <memory>
#include <algorithm>
#define BATCH_MODE (argc == 3)
#define SHELL_MODE (argc == 1)



void start(std::istream& input, std::ostream &output, Mode mode);



























#endif //GCALC_CALC_MAIN_H

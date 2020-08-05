#include "Graph.h"
using namespace mtm;

int main(int argc, char** argv){
    Graph g("{v1, v2, v3 | <v1, v2>, <v1, v3>}");
    g.print(std::cout);
}

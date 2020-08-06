#include "Graph.h"
using namespace mtm;

int main(int argc, char** argv){
    Graph g("{v1, v2, v3 | <v1, v2>, <v1, v3>}");
    Graph g2("{v5, v6 | <v5, v6>}");
    (g*g2).print(std::cout);
}

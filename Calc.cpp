#include "Calc.h"
#include "Graph.h"

using namespace mtm;

void Calc::reset() {
    graph_memory.clear();
}

namespace mtm {

    void Calc::addGraph(std::string &name, Graph g) {
        if(graph_memory.count(name)){
            throw GraphAlreadyInserted();
        }
        name = trim(name);
        std::pair<std::string, Graph> pair(name, g);
        graph_memory.insert(pair);
    }
}


namespace mtm {
    std::ostream &operator<<(std::ostream &os, Calc &calc) {
        for (const auto &pair : calc.graph_memory) {
            os << pair.first << std::endl;
        }
        return os;
    }
}

Graph Calc::getGraph(std::string name) const{
    if(!graph_memory.count(name)){
        throw AbsentGraph();
    }
    return graph_memory.at(name);
}

void Calc::delete_graph(std::string graph_to_delete) {
    if(graph_memory.count(graph_to_delete)){
        throw AbsentGraph();
    }
    graph_memory.erase(graph_to_delete);
}

Graph Calc::calculate(std::string& g1_str, char oper, std::string& g2_str) const {
    Graph g1 = getGraph(trim(g1_str)), g2 = getGraph(trim(g2_str));
    switch (oper) {
        case '+':
            return g1 + g2;
        case '^':
            return g1 ^ g2;
        case '-':
            return g1 - g2;
        case '*':
            return g1 * g2;
        default:
            return Graph("|");
    }
}





















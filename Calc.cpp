#include "Calc.h"
#include "Graph.h"

using namespace mtm;

void Calc::reset() {
    graph_memory.clear();
}

namespace mtm {
    void Calc::addGraph(std::string &name, Graph g) {
        graph_memory[name] = g;
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
    checkLeftVariable(name);
    if(!graph_memory.count(name)){
        throw AbsentGraph();
    }
    return graph_memory.at(name);
}

void Calc::delete_graph(std::string graph_to_delete) {
    checkLeftVariable(graph_to_delete);
    if(!graph_memory.count(graph_to_delete)){
        throw AbsentGraph();
    }
    graph_memory.erase(graph_to_delete);
}

 void Calc::checkLeftVariable(const std::string &name) {
    if (name.empty()){
        throw InvalidGraphVariable();
    }

    if(!isalpha(name[0])){
        throw InvalidGraphVariable();
    }

    if(name.length() > 1) {
        for (auto c : name.substr(1)) {
            if (!isalnum(c)) {
                throw InvalidGraphVariable();
            }
        }
    }
}

void Calc::checkSavedFunction(std::string &variable) {
    for(auto command : SAVED_CALC_FUNCS){
        if(variable == command){
            throw SavedWordInserted();
        }
    }
}

Graph Calc::generate(std::string g) const{
    for(int  i = g.length() - 1; i >= 0 ; i-- ) {
        // Parsing the string from left to right when in parallel ! operator has the highest priority
        if(isLegalOperator(g.at(i))){
            Graph g1 = generate(trim(g.substr(0, i)));
            Graph g2 = generate(trim(g.substr(i + 1)));
            if(g.at(i) == '+'){
                return g1 + g2;
            }
            else if(g.at(i) == '-'){
                return g1 - g2;
            }

            else if(g.at(i) == '*'){
                return g1 * g2;
            }

            else if(g.at(i) == '^'){
                return g1 ^ g2;
            }
        }
    }
    if(startsWith(g, "!")) { // Giving the complement operator the highest priority
        std::string complement_graph = g.substr(1);
        return !generate(complement_graph);
    }
    if(graph_memory.find(g) != graph_memory.end()) { //Checking whether g is a saved graph or not
        Graph gr = getGraph(trim(g));
        return gr;
    }
    //Creating a new graph according to the string that was inserted
    return Graph(trim(g));
}




















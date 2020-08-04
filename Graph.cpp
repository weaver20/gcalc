
#include "Graph.h"
#include <cassert>

using namespace mtm;

bool Graph::checkValidity(std::string str) {
    int parantheses = 0;
    for(const char& c : str) {
        if(parantheses < 0){
            return false;
        }
        if(c == ';' and parantheses <= 0){
            return false;
        }
        if(c == '['){
            parantheses++;
        }
        if(c == ']'){
            parantheses--;
        }
        if(!((islower(c)) or (isupper(c)) or (isdigit(c)))){
            return false;
        }
    }
    return true;
}

Graph::Graph(std::string g) {
    if (!checkValidity(g)){ //TODO: need to change the condition to check main string validity and not vertex's name validity
        throw InvalidString();
    }
    std::set<std::string> vert;
    std::multimap<std::string, std::string> edge;
    char c = g[1];
    while(c != '|'){
        int pos = g.find(',');
        std::string sub_str = g.substr(0, --pos);
        if(!checkValidity(sub_str)){
            throw InvalidString();
        }
        vert.insert(sub_str);
        g = g.substr(pos + 1);
        c = g[0];
    }
    while(c != '}'){
        int p1 = g.find('<'), p2 = g.find('>');
        std::string sub_str = g.substr(p1, p2);
        int delimeter = sub_str.find(',');
        std::string v1 = sub_str.substr(0, --delimeter);
        std::string v2 = sub_str.substr(++delimeter);
        if(!checkValidity(v1) or !checkValidity(v2)){
            throw InvalidString();
        }
        if((!vert.count(v1)) or (!vert.count(v2))){
            throw IllegalEdge();
        }
        edge.insert(v1, v2);
        g = g.substr(p2);
        c = g[1];
    }
    vertex = vert.size();
    edges = edge.size();
}

Graph::Graph(Graph& graph): vertex(graph.vertex), edges(graph.getEdgeSize()), v(graph.v), e(graph.e) {
}

Graph& Graph::operator=(const Graph& graph){
    if(this == &graph){
        return *this;
    }
    vertex = graph.vertex;
    edges = graph.edges;
    v = graph.v;
    e = graph.e;
    return *this;
}

Graph Graph::operator+(Graph&){
    
}



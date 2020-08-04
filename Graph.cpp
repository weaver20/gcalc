
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

Graph::Graph(std::set<std::string> v, std::set<std::pair<std::string, std::string>> e):vertex(v.size()), edges(e.size()),
v(v), e(e){}

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

Graph Graph::operator+(Graph& graph){
    std::set<std::string> union_v = this->v;
    std::set<std::pair<std::string, std::string>> union_e = this->e;
    for(auto it = graph.v.begin(); it != graph.v.end(); it++){
        union_v.insert(*it);
    }
    for(auto it = graph.e.begin(); it != graph.e.end(); it++){
        union_e.insert(*it);
    }
    Graph result(union_v,union_e);
    return result;
}

Graph Graph::operator^(Graph& graph) {
    std::set<std::string> inter_v = this->v;
    std::set<std::pair<std::string, std::string>> inter_e = this->e;
    for(auto it = graph.v.begin(); it != graph.v.end(); it++){
        if(v.count(*it)){
            inter_v.insert(*it);
        }
    }
    for(auto it = graph.e.begin(); it != graph.e.end(); it++){
        if(e.count(*it)){
            inter_e.insert(*it);
        }
    }
    Graph result(inter_v,inter_e);
    return result;
}

Graph Graph::operator-(Graph& graph){
    std::set<std::string> diff_v = this->v;
    std::set<std::pair<std::string, std::string>> diff_e = this->e;
    for(auto it = v.begin(); it != v.end(); it++){
        if(graph.v.count(*it)){
            diff_v.erase(*it);
        }
    }
    for(auto it = e.begin(); it != e.end(); it++){
        if(graph.e.count(*it)){
            diff_e.erase(*it);
        }
    }
    Graph result(diff_v, diff_e);
    return result;
}

Graph Graph::operator*(Graph& graph) {
    std::set<std::string> product_v;
    std::set<std::pair<std::string, std::string>> product_e;
    for(auto it = v.begin(); it != v.end(); it++){
        for(auto it2 = graph.v.begin(); it2 != graph.v.end(); it2++){
            std::string str = "[";
            str.append(*it);
            str.append(";");
            str.append(*it2);
            str.append("]");
        }
    }
    for(auto it = e.begin(); it != e.end(); it++){
        for(auto it2 = graph.e.begin(); it2 != graph.e.end(); it2++) {
            std::string str1 = "[";
            str1.append(it->first);
            str1.append(";");
            str1.append(it2->first);
            str1.append("]");
            std::string str2 = "[";
            str2.append(it->second);
            str2.append(";");
            str2.append(it2->second);
            str2.append("]");
            std::pair<std::string, std::string> result(str1, str2);
            product_e.insert(result);
        }
    }
    Graph product(product_v, product_e);
    return product;
}




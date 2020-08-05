
#include "Graph.h"
#include <cassert>

using namespace mtm;

bool checkGraphName(std::string& str){
    return (not(startsWith(str, "{") and endsWith(str, "}")));
}

bool Graph::checkVertexName(std::string& str) {
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

Graph::Graph(std::string& g) {
    if (!checkGraphName(g)){
        throw InvalidGraphString();
    }
    std::set<std::string> vert;
    std::multimap<std::string, std::string> edge;
    char c = g[1];
    while(c != '|'){
        int pos = g.find(',');
        std::string candidate_vertex = g.substr(0, --pos);
        if(!checkVertexName(candidate_vertex)){
            throw InvalidVertexName();
        }
        vert.insert(candidate_vertex);
        g = g.substr(pos + 1);
        c = g[0];
    }
    while(c != '}'){
        int p1 = g.find('<'), p2 = g.find('>');
        std::string sub_str = g.substr(p1, p2);
        int delimeter = sub_str.find(',');
        std::string v1 = sub_str.substr(0, --delimeter);
        std::string v2 = sub_str.substr(++delimeter);
        if(!checkVertexName(v1) or !checkVertexName(v2)){
            throw InvalidVertexName();
        }
        if((!vert.count(v1)) or (!vert.count(v2))){
            throw IllegalEdge();
        }
        edge.insert(v1, v2);
        g = g.substr(p2);
        c = g[1];
    }    vertex = vert.size();
    edges = edge.size();
}

Graph::Graph(Graph& graph): vertex(graph.vertex), edges(graph.getEdgeSize()), v(graph.v), e(graph.e) {
}

Graph::Graph(const std::set<std::string>& v, const std::set<std::pair<std::string, std::string>>& e):vertex(v.size()), edges(e.size()),
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
    union_v.insert(graph.v.begin(), graph.v.end());
    union_e.insert(graph.e.begin(), graph.e.end());
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

Graph Graph::operator!() {
    std::set<std::string> k_vert = v;
    std::set<std::pair<std::string, std::string>> k_edge;
    for(auto it = v.begin(); it != v.end(); it++){
        for(auto it2 = v.begin(); it2 != v.end(); it2++){
            if(it != it2){
                std::pair<std::string, std::string> edge(*it, *it2);
                k_edge.insert(edge);
            }
        }
    }
    std::string emp = "{ | }";
    Graph res(emp);
    res.v = v;
    std::set_difference(k_edge.begin(), k_edge.end(),
                        e.begin(),e.end(), std::inserter(res.e, res.e.begin()));
    return res;
}

void Graph::addVertex(std::string &name) {
    name = trim(name);
    if(!checkVertexName(name)){
        throw InvalidVertexName();
    }
    if(v.count(name)){
        throw VertexAlreadyExists();
    }
    v.insert(name);
}

void Graph::addEdge(std::string &origin, std::string &dest) {
    origin = trim(origin);
    dest = trim(dest);
    if(!checkVertexName(origin) or !checkVertexName(dest)){
        throw InvalidVertexName();
    }
    if(origin == dest){
        throw SelfCircle();
    }
    std::pair<std::string, std::string> edge(origin, dest);
    e.count(edge)? throw EdgeAlreadyExists() : e.insert(edge);
}

void Graph::print(std::ostream &out) {
    for(const std::string& vert : v){
        out << vert << std::endl;
    }
    out << "$" << std::endl;
    for(const std::pair<std::string, std::string>& edge : e){
        out << edge.first << " " << edge.second << std::endl;
    }
}


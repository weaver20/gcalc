#include "Calc.h"
#include "Graph.h"

using namespace mtm;

void Calc::reset() {
    graph_memory.clear();
}


void Calc::addGraph(std::string &name, Graph g) {
    graph_memory[name] = g;
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
    for(int  i = g.length() - 1; i >= 0; i--) {
        // Parsing the string from left to right when in parallel () have the highest priority
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
    if(startWith(trim(g), "!")) { // Giving the complement operator the highest priority
        std::string complement_graph = g.substr(1);
        return !generate(trim(complement_graph));
    }
    if(startWith(trim(g), "load")){ // loading the graph in case it's required
        return load(retrieveFileName(g));
    }
    if(graph_memory.find(trim(g)) != graph_memory.end()) { //Checking whether g is a saved graph or not
        Graph gr = getGraph(trim(g));
        return gr;
    }
    //Creating a new graph according to the string that was inserted
    return Graph(trim(g));
}

void Calc::save(const std::string& file_name, const Graph graph) const{
    checkFileName(file_name);
    unsigned int v_num = graph.getVertexSize(), e_num = graph.getEdgeSize();
    std::set<std::string > vertex_set = graph.getVertexSet();
    std::set<std::pair<std::string, std::string> > edge_set = graph.getEdgeSet();
    std::ofstream outfile(file_name, std::ios_base::binary);
    if(!outfile){
        throw CorruptedFile();
    }
    outfile.write((const char*)&v_num, sizeof(unsigned int));
    outfile.write((const char*)&e_num, sizeof(unsigned int));

    // ******** Writing vertex into binary file ********
    for(const auto& vertex : vertex_set){
        unsigned int len = vertex.length(); // Saving the vertex's length as an lvalue
        outfile.write((const char*)&len, sizeof(unsigned int));
        outfile.write((const char*)vertex.c_str(), len);
    }

    // ******** Writing edges into binary file ********
    for(const auto& edge : edge_set){
        unsigned int len = edge.first.length(); // Saving the vertex's length as an lvalue
        const char* first = edge.first.c_str();
        outfile.write((const char*)&len, sizeof(unsigned int));
        outfile.write(first, len);
        len = edge.second.length(); // Saving the vertex's length as an lvalue
        const char* second = edge.second.c_str();
        outfile.write((const char*)&len, sizeof(unsigned int));
        outfile.write(second, len);
    }
}

std::string Calc::retrieveFileName(const std::string& data) {
    std::string rest = trim(data.substr(4));
    if(rest[0] != '(' or endWith(rest, ")")){
        throw InvalidFileName();
    }
    rest.pop_back();
    rest = trim(rest.substr(1));
    return rest;
}

Graph Calc::load(const std::string& file_name) const{
    checkFileName(file_name);
    std::ifstream infile(file_name, std::ios::binary);
    if(!infile){
        throw CorruptedFile();
    }
    unsigned int v_num, e_num;
    Graph loaded;
    infile.read((char*)&v_num, sizeof(unsigned int));
    infile.read((char*)&e_num, sizeof(unsigned int));
    for(unsigned int i = 0; i < v_num; i++){
        std::string v_read;
        unsigned int len; // Saving the vertex's length as an lvalue
        infile.read((char*)&len, sizeof(unsigned int));
        v_read.resize(len);
        infile.read(&v_read[0], len);
        loaded.addVertex(v_read);
    }

    for(unsigned int i = 0; i < e_num; i++){
        std::string v1_read, v2_read;
        unsigned int len1, len2; // Saving the vertex's length as an lvalue
        infile.read((char*)&len1, sizeof(unsigned int));
        v1_read.resize(len1);
        infile.read(&v1_read[0], len1);
        infile.read((char*)&len2, sizeof(unsigned int));
        v1_read.resize(len2);
        infile.read(&v2_read[0], len2);
        loaded.addEdge(v1_read, v2_read);
    }
    return loaded;
}


















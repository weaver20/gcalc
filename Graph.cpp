#include "Graph.h"
using namespace mtm;

namespace mtm {

    bool Graph::checkGraphName(const std::string &str) {
        if(str.find('|') == std::string::npos){
            if(str.find('<') !=
                std::string::npos or str.find('>') != std::string::npos) {
                throw InvalidGraphString();
            }
        }
        return (startsWith(str, "{") and endsWith(str, "}"));
    }

    bool Graph::checkVertexName(const std::string &str) {
        int parantheses = 0;
        for (const char &c : str) {
            if (parantheses < 0) {
                return false;
            }
            if (c == ';' and parantheses <= 0) {
                return false;
            }
            if (c == '[') {
                parantheses++;
            }
            else if (c == ']') {
                parantheses--;
            }
            else if(c == ';'){
                continue;
            }
            else if (!((islower(c)) or (isupper(c)) or (isdigit(c)))) {
                return false;
            }
        }
        return true;
    }

    bool Graph::checkEdgeFormat(const std::string &str) {
        return (startsWith(str, "<") and endsWith(str, ">") and numOfOccurences(str, ',') == 1);
    }
}

    Graph::Graph(std::string g) {
        if (!checkGraphName(g)) {
            throw InvalidGraphString();
        }
        std::set<std::string> vert;
        std::set<std::pair<std::string, std::string>> edge;
        std::string v_string;
        std::string e_string;
        v = vert;
        e = edge;
        size_t delimeter_pos = g.find('|');
        if(delimeter_pos == std::string::npos){
            if(g.find('<') !=
               std::string::npos or g.find('>') != std::string::npos){
                throw InvalidGraphString();
            }
            v_string = g.substr(1);
            v_string.pop_back();
            v_string = trim(v_string);
        }
        else {
            v_string = trim(g.substr(1, delimeter_pos - 1));
            e_string = trim(g.substr(delimeter_pos + 1));
            e_string.pop_back();
        }
        while (v_string.find(',') != std::string::npos){
            int pos = v_string.find(',');
            std::string candidate_vertex = trim(v_string.substr(0, pos));
            addVertex(candidate_vertex);
            v_string = trim(v_string.substr(pos + 1));
        }
        if (!v_string.empty()) {
            addVertex(v_string);
        }
        if(!e_string.empty()) {
            while (!e_string.empty()) {
                size_t p1 = e_string.find('<'), p2 = e_string.find('>');
                if(p1 == std::string::npos or p2 == std::string::npos){
                    throw IllegalEdge();
                }
                std::string sub_str = e_string.substr(p1, p2 - p1 + 1);
                int delimeter = sub_str.find(',');
                if (!checkEdgeFormat(sub_str)) {
                    throw InvalidVertexName();
                }
                sub_str = sub_str.substr(1);
                sub_str.pop_back();
                delimeter--;
                std::string v1 = trim(sub_str.substr(0, delimeter));
                std::string v2 = trim(sub_str.substr(delimeter + 1));
                addEdge(v1, v2);
                e_string = trim(e_string.substr(p2 + 1));
            }
        }
        vertex = v.size();
        edges = e.size();
    }

    Graph::Graph(const Graph &graph) : vertex(graph.vertex), edges(graph.e.size()), v(graph.v), e(graph.e) {}

    Graph::Graph(const std::set<std::string> &v, const std::set<std::pair<std::string, std::string>> &e) : vertex(
            v.size()), edges(e.size()),v(v), e(e) {
    }

    Graph &Graph::operator=(Graph graph) {
        if (this == &graph) {
            return *this;
        }
        vertex = graph.vertex;
        edges = graph.edges;
        v = graph.v;
        e = graph.e;
        return *this;
    }

    Graph Graph::operator+(Graph &graph) const{
        std::set<std::string> union_v = this->v;
        std::set<std::pair<std::string, std::string>> union_e = this->e;
        union_v.insert(graph.v.begin(), graph.v.end());
        union_e.insert(graph.e.begin(), graph.e.end());
        Graph g(union_v, union_e);
        return g;
    }

    Graph Graph::operator^(Graph &graph) const{
        Graph emp("{|}");
        std::set_intersection(v.begin(), v.end(),
                              graph.v.begin(), graph.v.end(), std::inserter(emp.v, emp.v.begin()));
        std::set_intersection(e.begin(), e.end(),
                              graph.e.begin(), graph.e.end(), std::inserter(emp.e, emp.e.begin()));
        return emp;
    }

    Graph Graph::operator-(Graph &graph) const{
        Graph emp("{|}");
        std::set_difference(v.begin(), v.end(),
                            graph.v.begin(), graph.v.end(), std::inserter(emp.v, emp.v.begin()));
        for (std::pair<std::string, std::string> edge : e) {
            try {
                emp.addEdge(edge.first, edge.second);
            }
            catch (IllegalEdge &g) {
                continue;
            }
        }
        return emp;
    }

    Graph Graph::operator*(Graph &graph) const{
        std::set<std::string> product_v;
        std::set<std::pair<std::string, std::string>> product_e;
        for (auto it = v.begin(); it != v.end(); it++) {
            for (auto it2 = graph.v.begin(); it2 != graph.v.end(); it2++) {
                std::string str = "[";
                str.append(*it);
                str.append(";");
                str.append(*it2);
                str.append("]");
                product_v.insert(str);
            }
        }
        for (auto it = e.begin(); it != e.end(); it++) {
            for (auto it2 = graph.e.begin(); it2 != graph.e.end(); it2++) {
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

    Graph Graph::operator!() const {
        std::set<std::string> k_vert = v;
        std::set<std::pair<std::string, std::string>> k_edge;
        for (auto it = v.begin(); it != v.end(); it++) {
            for (auto it2 = v.begin(); it2 != v.end(); it2++) {
                if (it != it2) {
                    std::pair<std::string, std::string> edge(*it, *it2);
                    k_edge.insert(edge);
                }
            }
        }
        std::string emp = "{ | }";
        Graph res(emp);
        res.v = v;
        res.vertex = res.v.size();
        std::set_difference(k_edge.begin(), k_edge.end(),
                            e.begin(), e.end(), std::inserter(res.e, res.e.begin()));
        res.edges = res.e.size();
        return res;
    }

    void Graph::addVertex(std::string &name) {
        name = trim(name);
        if (!checkVertexName(name)) {
            throw InvalidVertexName();
        }
        if (v.count(name)) {
            throw VertexAlreadyExists();
        }
        v.insert(name);
    }

    void Graph::addEdge(std::string &origin, std::string &dest) {
        origin = trim(origin);
        dest = trim(dest);
        if (!checkVertexName(origin) or !checkVertexName(dest)) {
            throw InvalidVertexName();
        }
        if (origin == dest) {
            throw SelfCircle();
        }
        if (!v.count(origin) or !v.count(dest)) {
            throw IllegalEdge();
        }
        std::pair<std::string, std::string> edge(origin, dest);
        e.count(edge) ? throw ParallelEdge() : e.insert(edge);
    }

    void Graph::print(std::ostream &out) {
        for (const std::string &vert : v) {
            out << vert << std::endl;
        }
        out << "$" << std::endl;
        for (const std::pair<std::string, std::string> &edge : e) {
            out << edge.first << " " << edge.second << std::endl;
        }
    }
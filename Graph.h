#ifndef GCALC_GRAPH_H
#define GCALC_GRAPH_H

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cctype>
#include <algorithm>
#include <vector>
#include "Auxilaries.h"
#include "GraphException.h"



namespace mtm{

    class Graph{
        int vertex;
        int edges;
        std::set<std::string> v;
        std::set<std::pair<std::string, std::string>> e;
        static bool checkVertexName(std::string&);
        static bool checkGraphName(std::string&);
        static bool checkEdgeFormat(std::string&);

    public:
        /**
         *  C`tor - creates an Graph according to the instructions
         * @param g - a string which represents the vertexes and edges of the graph according to the required format
         */
        explicit Graph(std::string g);
        /**
         * Copy C`tor
         */
         Graph(Graph&);
         /**
          * C'tor - receives vertex&edges sets and creates a directed graph accordingly
          */
         Graph(const std::set<std::string>& v, const std::set<std::pair<std::string, std::string>>& e);
        /**
         * Assignment operator
         * @return a reference to assigned Graph
         */
         Graph& operator=(const Graph);
         /**
          * D'tor
          */
         ~Graph() = default;
         /**
          * Union operator
          */
          Graph operator+(Graph&);
          /**
           * Intersection operator
           */
           Graph operator^(Graph&);
           /**
           * Difference operator
           */
           Graph operator-(Graph&);
           /**
            * Product operator
            */
            Graph operator*(Graph&);
            /**
            * Complement operator
            */
            Graph operator!() const;
            /**
            * Add edge
            */
            void addEdge(std::string& origin, std::string& dest);
            /**
            * Add vertex
            */
            void addVertex(std::string& name);
            /**
            * Print function
            */
            void print(std::ostream& out);
    };




}

#endif //GCALC_GRAPH_H

#ifndef GCALC_GRAPH_H
#define GCALC_GRAPH_H

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cctype>
#include "Auxilaries.h"
#include "GraphException.h"
#include "Calc.h"



namespace mtm{

    class Graph{
        std::set<std::string> v;
        std::set<std::pair<std::string, std::string> > e;

    public:
        /**
        * Default C'tor
        */
         Graph() = default;
        /**
         *  C`tor - creates an Graph according to the instructions
         * @param g - a string which represents the vertexes and edges of the graph according to the required format
         */
        explicit Graph(std::string g);
        /**
         * Copy C`tor
         */
         Graph(const Graph&);
         /**
          * C'tor - receives vertex&edges sets and creates a directed graph accordingly
          */
         Graph(std::set<std::string>  v, const std::set<std::pair<std::string, std::string> > e);
        /**
         * Assignment operator
         * @return a reference to assigned Graph
         */
         Graph& operator=(Graph);
         /**
          * D'tor
          */
         ~Graph() = default;
         /**
          * Union operator
          */
          Graph operator+(Graph&) const;
          /**
           * Intersection operator
           */
           Graph operator^(Graph&) const;
           /**
           * Difference operator
           */
           Graph operator-(Graph&) const;
           /**
            * Product operator
            */
            Graph operator*(Graph&) const;
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

            static bool checkGraphName(const std::string &str);

            static bool checkVertexName(const std::string &str);

            static bool checkEdgeFormat(const std::string &str);

            int getEdgeSize() const;

            int getVertexSize() const;

            std::set<std::string> getVertexSet() const;

            std::set<std::pair<std::string, std::string> > getEdgeSet() const;
    };


}


#endif //GCALC_GRAPH_H

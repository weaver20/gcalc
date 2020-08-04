#ifndef GCALC_GRAPH_H
#define GCALC_GRAPH_H

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cctype>


namespace mtm{

    class Graph{
        int vertex;
        int edges;
        std::set<std::string> v;
        std::set<std::pair<std::string, std::string>> e;
        static bool checkValidity(std::string);

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
         Graph(std::set<std::string> v, std::set<std::pair<std::string, std::string>> e);
        /**
         * Assignment operator
         * @return a reference to assigned Graph
         */
         Graph& operator=(const Graph&);
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
            Graph operator!();
            /**
            *  Get Vertexes number in the graph
            */
            int getVertSize();
            /**
            *  Get Edges number in the graph
            */
            int getEdgeSize();

            //Exception Classes
        class InvalidString : public std::exception {
            public:
                const char* what() const noexcept override;
        };
        class IllegalEdge : public std::exception {
            public:
                const char* what() const noexcept override;
        };
        class ParallelEdge : public std::exception {
            const char* what() const noexcept override;
        };


    };




}



















#endif //GCALC_GRAPH_H

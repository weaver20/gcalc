#ifndef GCALC_GRAPH_H
#define GCALC_GRAPH_H

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cctype>
#include <utility>
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
         * @return empty graph
        */
         Graph() = default;
        /**
         *  C`tor - creates an Graph according to the instructions
         * @param g - a string which represents the vertexes and edges of the graph according to the required format
         *  Exceptions:
         *  InvalidGraphString - if the string that was inserted is not according to thr assignment rules
         *  InvalidVertexName - if the vertex name is illegal
         *  IllegalEdge - if the edge data is illegal (for an example, an edge that origins in a vertex which is not
         *                in the graph.
         *  std::bad_alloc - in case there's a memory allocation problem.
         *  @return a graph according to the data which has been supplied
         */
        explicit Graph(std::string g);
        /**
         * Copy C`tor
         * Exceptions:
         * std::bad_alloc - in case there's a memory allocation problem.
         */
         Graph(const Graph&);
         /**
          * C'tor - receives vertex&edges sets and creates a directed graph accordingly.
          * Exceptions:
          * std::bad_alloc - in case there's a memory allocation problem.
          */
         Graph(std::set<std::string>  v, const std::set<std::pair<std::string, std::string> > e);
        /**
         * Assignment operator
         * @return a reference to assigned Graph
         * Exceptions:
         * std::bad_alloc - in case there's a memory allocation problem.
         */
         Graph& operator=(const Graph);
         /**
          * D'tor
          */
         ~Graph() = default;
         /**
          * Unites 2 graphs
          * Exceptions:
          * std::bad_alloc - in case there's a memory allocation problem.
          */
          Graph operator+(Graph&) const;
          /**
           * Intersects 2 graphs
           * Exceptions:
           * std::bad_alloc - in case there's a memory allocation problem.
           */
           Graph operator^(Graph&) const;
           /**
           * @return the difference between two graphs
           * Exception:
           * std::bad_alloc - in case there's a memory allocation problem.
           */
           Graph operator-(Graph&) const;
           /**
            * @return the product of 2 graphs
            * Exception:
            * std::bad_alloc - in case there's a memory allocation problem.
            */
            Graph operator*(Graph&) const;
            /**
            * @return the complement graph
            * Exceptions:
            * std::bad_alloc - in case there's a memory allocation problem.
            */
            Graph operator!() const;
            /**
             * Adds an edge to the graph
            * @param origin: origin vertex
             * @param dest: destination vertex
             * Exceptions:
             * std::bad_alloc - in case there's a memory allocation problem.
             * IllegalEdge - if the edge data is illegal (for an example, an edge that origins in a vertex which is not
             *               in the graph.
             * InvalidVertexName - if the vertex name is illegal
             * SelfCircle - whether the origin vertex == destination vertex
             * ParallelEdge - if there are parallel edges in the graph
            */
            void addEdge(std::string& origin, std::string& dest);
            /**
            * Adds a vertex to the graph
             * @param name: vertex name
             * Exceptions:
             * InvalidVertexName - if the vertex name is illegal
             * std::bad_alloc - in case there's a memory allocation problem.
             * VertexAlreadyExists - if the vertex is already in the graph
            */
            void addVertex(std::string& name);
            /**
            * Prints the graphs data (vertexes and edges)
             * @param out: ostream&
            */
            void print(std::ostream& out);
            /**
             *
             * @param str
             * @return true if the graph string has the proper format, false otherwise
             */
            static bool checkGraphName(const std::string &str);
            /**
             *
             * @param str - vertex name
             * @return true if the vertex name given is legal, false otherwise
             */
            static bool checkVertexName(const std::string &str);
            /**
             *
             * @param str - an edge string
             * @return true if the edge format is legal, false otherwise
             */
            static bool checkEdgeFormat(const std::string &str);
            /**
             *
             * @return graph's edge number
             */
            int getEdgeSize() const;
            /**
             *
             * @return graph's vertex number
             */
            int getVertexSize() const;
            /**
             *
             * @return graph's vertex set
             * Exception:
             * std::bad_alloc - in case there's a memory allocation problem.
             */
            std::set<std::string> getVertexSet() const;
            /**
             *
             * @return graph's edge set
             * Exception:
             * std::bad_alloc - in case there's a memory allocation problem.
             */
            std::set<std::pair<std::string, std::string> > getEdgeSet() const;
    };


}


#endif //GCALC_GRAPH_H

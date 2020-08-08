#ifndef GCALC_CALC_H
#define GCALC_CALC_H
#include "Graph.h"
#include "CalcException.h"



namespace mtm{

    class Calc {

        std::map<std::string, class Graph> graph_memory;

    public:
        /**
         * C'tor
         */
        Calc() = default;

        /**
         * D'tor
         */
        ~Calc() = default;

        /**
         * Assigment operator, there is no need for this operator
         * @return
         */
        Calc &operator=(Calc &) = delete;

        /**
         * Copy C'tor, there is no need for that C'tor
         */
        Calc(const Calc &) = default;

        /**
         * Adds a graph to the calculator's memory
         */
        void addGraph(std::string& name, Graph graph);

        void reset();

        void delete_graph(std::string graph_to_delete);

        Graph getGraph(std::string name) const;

        Graph calculate(std::string& g1, char oper, std::string& g2) const;

        friend std::ostream& operator<<(std::ostream& os, Calc& calc);

        static void checkLeftVariable(const std::string& name);

        bool isVertexIn(std::string vertex);

        void addVertexToMemory(std::string& vertex);

        static void checkSavedFunction(std::string& variable);

    };



}











#endif //GCALC_CALC_H

#ifndef GCALC_CALC_H
#define GCALC_CALC_H
#include "Graph.h"
#include "CalcException.h"
#include <stack>



namespace mtm{

    class Calc {

        std::map<std::string, class Graph> graph_memory;

    public:
        /**
         * C'tor - returns an empty calculator
         */
        Calc() = default;
        /**
        * Copy C'tor
        */
        Calc(const Calc&) = default;
        /**
        * D'tor
        */
        ~Calc() = default;
        /**
         * Assigment operator
         * @return Calc
         */
        Calc &operator=(Calc &) = delete;
        /**
         * Adds a graph to the calculator's memory
         * @param name - graph's name
         * @param graph - Graph object
         * Exception:
         * std::bad_alloc - in case there's a memory allocation problem.
         */
        void addGraph(std::string& name, Graph graph);
        /**
         * resets the calculator and  deletes all data from the memory
         */
        void reset();
        /**
         *
         * Deletes the graph associated with the given name from the calc's memory
         * @param graph_to_delete - graph name
         * Exceptions:
         * AbsentGraph - the requested graph is not in the calculator's memory
         *
         */
        void delete_graph(std::string graph_to_delete);
        /**
         *
         * @param name - graphs variable name
         * @return the graph associated with the variable name given
         * Exceptions:
         * AbsentGraph - the requested graph is not in the calculator's memory
         */
        Graph getGraph(std::string name) const;
        /**
         *
         * @param os
         * @param calc
         * @return the print data
         */
        friend std::ostream& operator<<(std::ostream& os, Calc& calc);
        /**
         *
         * @param name - the graph variable name
         * Exceptions:
         * InvalidGraphVariable - if a invalid name inserted for the graph's variable in the calculator
         */
        static void checkLeftVariable(const std::string& name);
        /**
         *
         * @param variable - the graph variable name
         * Exceptions:
         * SaveWordInserted - if a calc function name inserted
         */
        static void checkSavedFunction(std::string& variable);
        /**
         *
         * receives an arithmetic expression and evaluates its value
         * @return result graph
         * Exceptions:
         * std::bad_alloc - in case there's a memory allocation problem.
         */
        Graph generate(std::string) const;
        /**
         * Saves a Graph object data into a text file in a binary format
         * @param name - file_name
         * @param graph
         */
        void save(const std::string&, const Graph) const;
        /**
         *
         * @return a string contains only legal notes that includes the file name
         * Exceptions:
         * InvalidFileName: illegal file name inserted
         * CorruptedFile - if the file associated with the name inserted is corrupted
         */
        static std::string retrieveFileName(const std::string&);
        /**
         *
         * @param file_name
         * @return Graph object that's been loaded from binary file
         * Exceptions:
         * InvalidFileName: illegal file name inserted
         * CorruptedFile - if the file associated with the name inserted is corrupted
         */
        Graph load(const std::string& file_name) const;
    };



}











#endif //GCALC_CALC_H

%module graph
%include "PythonInterface.h"
%{
#include "PythonInterface.h"
%}

mtm::Graph* create();

void destroy(mtm::Graph* g);

mtm::Graph* addVertex(mtm::Graph* g, const char* v);

mtm::Graph* addEdge(mtm::Graph* g, const char* v1, const char* v2);

void disp(mtm::Graph* g);

mtm::Graph* graphUnion(mtm::Graph* graph_in1, mtm::Graph* graph_in2, mtm::Graph* graph_out);

mtm::Graph* graphIntersection(mtm::Graph* graph_in1, mtm::Graph* graph_in2, mtm::Graph* graph_out);

mtm::Graph* graphDifference(mtm::Graph* graph_in1, mtm::Graph* graph_in2, mtm::Graph* graph_out);

mtm::Graph* graphProduct(mtm::Graph* graph_in1, mtm::Graph* graph_in2, mtm::Graph* graph_out);

mtm::Graph* graphComplement(mtm::Graph* graph_in, mtm::Graph* graph_out);

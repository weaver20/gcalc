#include "PythonInterface.h"
using namespace mtm;
using std::cout;
using std::endl;



mtm::Graph* create(){
    Graph* g;
    try{
        g = new Graph();
    }
    catch (std::bad_alloc& e) {
        std::cerr << "   FATAL ERROR: Allocation Failure! \n" << std::endl;
        return nullptr;
    }
    return g;
}

void destroy(Graph* g){
    if(g == nullptr){
        cout << "Invalid graph pointer was sent! Please insert a valid pointer. \n" << endl;
        return;
    }
    delete g;
}

Graph* addVertex(Graph* g, const char* v){
    if(g == nullptr){
        cout << "Invalid graph pointer was sent! Please insert a valid pointer. \n" << endl;
        return nullptr;
    }
    try{
        std::string candidate_vertex = v;
        g->addVertex(candidate_vertex);
    }
    catch (GraphException& e) {
        cout << e.what() << endl;
    }
    catch (std::bad_alloc& e) {
        std::cerr << "   FATAL ERROR: Allocation Failure! \n" << std::endl;
        return nullptr;
    }
    return g;
}

Graph* addEdge(Graph* g, const char* v1, const char* v2){
    if(g == nullptr){
        cout << "Invalid graph pointer was sent! Please insert a valid pointer. \n" << endl;
        return nullptr;
    }
    try{
        std::string candidate_vertex1 = v1, candidate_vertex2 = v2;
        g->addEdge(candidate_vertex1, candidate_vertex2);
    }
    catch (GraphException& e) {
        cout << e.what() << endl;
    }
    catch (std::bad_alloc& e) {
        std::cerr << "   FATAL ERROR: Allocation Failure! \n" << std::endl;
        return nullptr;
    }
    return g;
}

void disp(Graph* g){
    if(g == nullptr){
        cout << "Invalid graph pointer was sent! Please insert a valid pointer. \n" << endl;
        return;
    }
    try{
        g->print(cout);
    }
    catch (std::bad_alloc& e) {
        std::cerr << "   FATAL ERROR: Allocation Failure! \n" << std::endl;
        return;
    }
}

Graph* graphUnion(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    if(graph_in1 == nullptr or graph_in2 == nullptr or graph_out == nullptr){
        cout << "Invalid graph pointer was sent! Please insert a valid pointer. \n" << endl;
        return nullptr;
    }
    try{
        *graph_out = *graph_in1 + *graph_in2;
    }
    catch (std::bad_alloc& e) {
        std::cerr << "   FATAL ERROR: Allocation Failure! \n" << std::endl;
        return nullptr;
    }
    return graph_out;
}

Graph* graphIntersection(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    if(graph_in1 == nullptr or graph_in2 == nullptr or graph_out == nullptr){
        cout << "Invalid graph pointer was sent! Please insert a valid pointer. \n" << endl;
        return nullptr;
    }
    try{
        *graph_out = *graph_in1 ^ *graph_in2;
    }
    catch (std::bad_alloc& e) {
        std::cerr << "   FATAL ERROR: Allocation Failure! \n" << std::endl;
        return nullptr;
    }
    return graph_out;
}

Graph* graphDifference(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    if(graph_in1 == nullptr or graph_in2 == nullptr or graph_out == nullptr){
        cout << "Invalid graph pointer was sent! Please insert a valid pointer. \n" << endl;
        return nullptr;
    }
    try{
        *graph_out = *graph_in1 - *graph_in2;
    }
    catch (std::bad_alloc& e) {
        std::cerr << "   FATAL ERROR: Allocation Failure! \n" << std::endl;
        return nullptr;
    }
    return graph_out;
}

Graph* graphProduct(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    if(graph_in1 == nullptr or graph_in2 == nullptr or graph_out == nullptr){
        cout << "Invalid graph pointer was sent! Please insert a valid pointer. \n" << endl;
        return nullptr;
    }
    try{
        *graph_out = (*graph_in1) * (*graph_in2);
    }
    catch (std::bad_alloc& e) {
        std::cerr << "   FATAL ERROR: Allocation Failure! \n" << std::endl;
        return nullptr;
    }
    return graph_out;
}

Graph* graphComplement(Graph* graph_in, Graph* graph_out){
    if(graph_in == nullptr or graph_out == nullptr){
        cout << "Invalid graph pointer was sent! Please insert a valid pointer. \n" << endl;
        return nullptr;
    }
    try{
        *graph_out = !(*graph_in);
    }
    catch (std::bad_alloc& e) {
        std::cerr << "   FATAL ERROR: Allocation Failure! \n" << std::endl;
        return nullptr;
    }
    return graph_out;
}




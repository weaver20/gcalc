
#include "GraphException.h"

const char* InvalidGraphString::what() const noexcept {
    return "    Error: Invalid graph data was inserted, please insert valid data. \n";
}

const char* InvalidVertexName::what() const noexcept {
    return "    Error: Invalid vertex name was inserted, please insert valid data. \n";
}

const char* VertexAlreadyExists::what() const noexcept {
    return "    Error: The vertex name which has been inserted already exists, please insert valid data. \n";
}

const char*  IllegalEdge::what() const noexcept {
    return "    Error: Invalid edge data was inserted, please insert valid data. \n";
}

const char*  ParallelEdge::what() const noexcept {
    return "    Error: The edge data which has been inserted already exists, please insert valid data. \n";
}

const char*  SelfCircle::what() const noexcept {
    return "    Error: Self circles are not allowed, please insert valid data. \n";
}

const char*  EmptyVertexString::what() const noexcept {
    return "    Error: No vertexes were inserted, please insert valid data. \n";
}

const char* GraphException::what() const noexcept {
    return "    Error: Graph Exception occurred! \n";
}














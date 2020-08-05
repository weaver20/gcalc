
#include "GraphException.h"

const char* InvalidGraphString::what() const noexcept {
    return "    Error: Invalid graph data was inserted, please insert valid data.";
}

const char* InvalidVertexName::what() const noexcept {
    return "    Error: Invalid vertex name was inserted, please insert valid data.";
}

const char* VertexAlreadyExists::what() const noexcept {
    return "    Error: The vertex name which has been inserted already exists, please insert valid data.";
}

const char*  IllegalEdge::what() const noexcept {
    return "    Error: Invalid edge data was inserted, please insert valid data.";
}

const char*  ParallelEdge::what() const noexcept {
    return "    Error: The edge data which has been inserted already exists, please insert valid data.";
}

const char*  SelfCircle::what() const noexcept {
    return "    Error: Self circles are not allowed, please insert valid data.";
}















#ifndef GCALC_GRAPHEXCEPTION_H
#define GCALC_GRAPHEXCEPTION_H

#include "Exception.h"

class GraphException : public Exception {
public:
    const char* what() const noexcept override;
};

class InvalidGraphString : public GraphException {
public:
    const char* what() const noexcept override;
};

class InvalidVertexName : public GraphException {
public:
    const char* what() const noexcept override;
};

class VertexAlreadyExists : public GraphException {
public:
    const char* what() const noexcept override;
};

class IllegalEdge : public GraphException {
public:
    const char* what() const noexcept override;
};

class ParallelEdge : public GraphException {
public:
    const char* what() const noexcept override;
};

class SelfCircle : public GraphException {
public:
    const char* what() const noexcept override;
};

class EmptyVertexString : public GraphException {
public:
    const char* what() const noexcept override;
};

#endif //GCALC_GRAPHEXCEPTION_H

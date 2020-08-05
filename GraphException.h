
#ifndef GCALC_GRAPHEXCEPTION_H
#define GCALC_GRAPHEXCEPTION_H

#include "Exception.h"

class InvalidGraphString : public Exception {
public:
    const char* what() const noexcept override;
};

class InvalidVertexName : public Exception {
public:
    const char* what() const noexcept override;
};

class VertexAlreadyExists : public Exception {
public:
    const char* what() const noexcept override;
};

class IllegalEdge : public Exception {
public:
    const char* what() const noexcept override;
};

class ParallelEdge : public Exception {
public:
    const char* what() const noexcept override;
};

class SelfCircle : public Exception {
public:
    const char* what() const noexcept override;
};

#endif //GCALC_GRAPHEXCEPTION_H

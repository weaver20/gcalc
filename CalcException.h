#ifndef GCALC_CALCEXCEPTION_H
#define GCALC_CALCEXCEPTION_H

#include "Exception.h"

class CalcException : public Exception {
public:
    const char *what() const noexcept override;
};

class CommandNotInFormat : public CalcException {
public:
    const char *what() const noexcept override;
};

class AssignmentOperatorAbsence : public CalcException{
public:
    const char *what() const noexcept override;
};

class InvalidFileName : public CalcException{
public:
    const char *what() const noexcept override;
};

class AbsentGraph : public CalcException{
public:
    const char *what() const noexcept override;
};

class GraphAlreadyInserted : public CalcException{
public:
    const char *what() const noexcept override;
};











































#endif //GCALC_CALCEXCEPTION_H

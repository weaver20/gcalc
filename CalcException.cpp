#include "CalcException.h"

const char* CalcException::what() const noexcept{
    return "    Error: Calc Error 404! \n";
}

const char* AssignmentOperatorAbsence::what() const noexcept{
    return "    Assignment operator was not inserted. \n";
}

const char* CommandNotInFormat::what() const noexcept{
    return "    Error: Invalid command format. \n";
}

const char* InvalidFileName::what() const noexcept{
    return "    Error: Invalid file name was inserted. \n";
}

const char* AbsentGraph::what() const noexcept{
    return "    Error: The following graph was not inserted into the calculator. \n";
}


const char* GraphAlreadyInserted::what() const noexcept{
    return "    Error: The following graph has already been inserted to the calculator. \n";
}

const char* InvalidGraphVariable::what() const noexcept{
    return "    Error: The variable name is illegal! Please insert a valid variable name. \n";
}












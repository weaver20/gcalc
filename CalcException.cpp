#include "CalcException.h"

const char* CalcException::what() const noexcept{
    return "    Error: Calc Error 404! \n";
}

const char* AssignmentOperatorAbsence::what() const noexcept{
    return "    Error: Assignment operator was not inserted. \n";
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
    return "    Error: The variable name is illegal! Please insert valid variable name. \n";
}

const char* SavedWordInserted::what() const noexcept{
    return "    Error: The usage of calc functions as variables is illegal! Please insert valid variable name. \n";
}

const char* EmptyInput::what() const noexcept{
    return "    Error: No input received! Please insert valid input. \n";
}

const char* CorruptedFile::what() const noexcept{
    return "    Error: Corrupted file data! \n";
}










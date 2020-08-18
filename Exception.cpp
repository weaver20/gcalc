#include "Exception.h"

const char* OpenFileError::what() const noexcept {
    return "Error: FATAL - Cannot open file.";
}

const char* Error::what() const noexcept {
    return "Error: FATAL - Illegal use of calculator";
}

const char* Exception::what() const noexcept {
    return "Error: FATAL";
}

#include "Exception.h"

const char* OpenFileError::what() const noexcept {
    return "FATAL Error - Cannot open file.";
}

const char* RunError::what() const noexcept {
    return "FATAL Error - Illegal use of calculator";
}

const char* Exception::what() const noexcept {
    return "FATAL Error";
}

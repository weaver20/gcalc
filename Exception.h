#ifndef GCALC_EXCEPTION_H
#define GCALC_EXCEPTION_H

#include <exception>

class Exception : public std::exception{
    public:
        const char *what() const noexcept override;
};

class RunError : public Exception {
    public:
        const char *what() const noexcept override;
};

class OpenFileError : public Exception {
    public:
        const char *what() const noexcept override;
};


#endif //GCALC_EXCEPTION_H

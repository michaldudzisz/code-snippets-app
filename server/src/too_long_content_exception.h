#ifndef TOOLONGCONTENTEXCEPTION_H
#define TOOLONGCONTENTEXCEPTION_H

#include <exception>

#include "snippet.h"

class TooLongContentException : public std::exception
{
public:

    TooLongContentException(Snippet::Field field, int length);
    const char *what() const throw();

private:
    int got_;
    std::string message_;
};

#endif
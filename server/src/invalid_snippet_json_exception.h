#ifndef INVALIDSNIPPETJSONEXCEPTION_H
#define INVALIDSNIPPETJSONEXCEPTION_H

#include <string>
#include <exception>

class InvalidSnippetJsonException : public std::exception
{
public:
    InvalidSnippetJsonException();
    const char *what() const throw();

private:
    std::string message_;
};

#endif
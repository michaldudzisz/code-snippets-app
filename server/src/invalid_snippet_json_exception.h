#ifndef INVALIDSNIPPETJSONEXCEPTION_H
#define INVALIDSNIPPETJSONEXCEPTION_H

#include <string>
#include <exception>

/** @brief Exception thrown by Snippet#fromJson when ivalid json is given to be parsed */ 

class InvalidSnippetJsonException : public std::exception
{
public:
    InvalidSnippetJsonException();
    /** Returns error message */
    const char *what() const throw();

private:
    std::string message_;
};

#endif
#ifndef TOOLONGCONTENTEXCEPTION_H
#define TOOLONGCONTENTEXCEPTION_H

#include <exception>

#include "snippet.h"

/** @brief Exception thrown when too long string is being assigned to ceratinf fields of 
 * Snippet or SnippetSearchPattern */

class TooLongContentException : public std::exception
{
public:
    /**
     * @param field Field, which fixed max size blocks the value to be assigned
     * @param length Length of given value, which was sent to be assigned 
     */
    TooLongContentException(Snippet::Field field, int length);
    /** Returns error message */
    const char *what() const throw();

private:
    int got_;
    std::string message_;
};

#endif
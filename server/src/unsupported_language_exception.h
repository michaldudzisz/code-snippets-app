#ifndef UNSUPPORTEDLANGUAGEEXCEPTION_H
#define UNSUPPORTEDLANGUAGEEXCEPTION_H

#include <string>
#include <exception>

/** Exception thrown when unsupported language is given to be assigned
 * as a snippet programming language 
 */

class UnsupportedLanguageException : public std::exception
{
public:
    /** @param lang Programming language given to be assigned */
    UnsupportedLanguageException(std::string lang);
    /** Returns error message */
    const char *what() const throw();

private:
    std::string message_;
};

#endif
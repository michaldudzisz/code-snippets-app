#ifndef UNSUPPORTEDLANGUAGEEXCEPTION_H
#define UNSUPPORTEDLANGUAGEEXCEPTION_H

#include <string>
#include <exception>

class UnsupportedLanguageException : public std::exception
{
public:
    UnsupportedLanguageException(std::string lang);
    const char *what() const throw();

private:
    std::string message_;
};

#endif
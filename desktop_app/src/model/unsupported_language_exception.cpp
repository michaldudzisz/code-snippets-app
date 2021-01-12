#include "unsupported_language_exception.h"

UnsupportedLanguageException::UnsupportedLanguageException(std::string lang)
{
    message_ = std::string("Unsupported language: ") + lang + std::string(".");
};

const char *UnsupportedLanguageException::what() const throw()
{
    return message_.c_str();
}

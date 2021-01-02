#include "repository_not_initialized_exception.h"

RepositoryNotInitializedException::RepositoryNotInitializedException(const char *info)
{
    message_ = std::string("Unable to initialize repository. ") +
               std::string(info);
};

const char *RepositoryNotInitializedException::what() const throw()
{
    return message_.c_str();
}

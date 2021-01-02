#ifndef REPOSITORY_NOT_INITIALIZED_EXCEPTION
#define REPOSITORY_NOT_INITIALIZED_EXCEPTION

#include <string>
#include <exception>

class RepositoryNotInitializedException : public std::exception
{
public:
    RepositoryNotInitializedException(const char *info);
    const char *what() const throw();

private:
    std::string message_;
};


#endif
#ifndef REPOSITORY_NOT_INITIALIZED_EXCEPTION
#define REPOSITORY_NOT_INITIALIZED_EXCEPTION

#include <string>
#include <exception>

/** @brief Exception thrown by implementation of SnippetRepositoryInterface 
 * when repository cannot be properly initialized and due to that,
 * server cannot be run */

class RepositoryNotInitializedException : public std::exception
{
public:
    /** @param info Error message */
    RepositoryNotInitializedException(const char *info);
    /** Returns error message */
    const char *what() const throw();

private:
    std::string message_;
};


#endif
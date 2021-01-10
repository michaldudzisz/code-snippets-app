#ifndef QUERY_NOT_PERFORMED_EXCEPTION
#define QUERY_NOT_PERFORMED_EXCEPTION

#include <string>
#include <exception>

/** @brief Exception thrown by implementation of SnippetRepositoryInterface when database 
 * query cannot be performed due to server/database problems. */

class QueryNotPerformedException : public std::exception
{
public:
    /** @param info Error message (eg. error got from database driver) */
    QueryNotPerformedException(const char * info);
    /** Returns error message */
    const char *what() const throw();

private:
    std::string message_;
};


#endif
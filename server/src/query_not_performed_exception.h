#ifndef QUERY_NOT_PERFORMED_EXCEPTION
#define QUERY_NOT_PERFORMED_EXCEPTION

#include <string>
#include <exception>

class QueryNotPerformedException : public std::exception
{
public:
    QueryNotPerformedException(const char * info);
    const char *what() const throw();

private:
    std::string message_;
};


#endif
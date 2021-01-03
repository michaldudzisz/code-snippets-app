#ifndef DATABASE_ERROR_EXCEPTION
#define DATABASE_ERROR_EXCEPTION

#include <string>
#include <exception>

class DatabaseErrorException : public std::exception
{
public:
    DatabaseErrorException(const char * info);
    const char *what() const throw();

private:
    std::string message_;
};


#endif
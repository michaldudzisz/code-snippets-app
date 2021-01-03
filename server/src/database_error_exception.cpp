#include "database_error_exception.h"

#include "snippet.h"

DatabaseErrorException::DatabaseErrorException(const char * info)
{
    message_ = std::string(info);
};

const char *DatabaseErrorException::what() const throw()
{
    return message_.c_str();
}

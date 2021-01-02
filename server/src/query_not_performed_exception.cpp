#include "query_not_performed_exception.h"

QueryNotPerformedException::QueryNotPerformedException(const char *info)
{
    message_ = std::string("Unable to perform database query. ") +
               std::string(info);
};

const char *QueryNotPerformedException::what() const throw()
{
    return message_.c_str();
}

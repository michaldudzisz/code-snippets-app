#include "invalid_get_request_body_exception.h"

#include "snippet.h"

InvalidGetRequestBodyException::InvalidGetRequestBodyException(){};

const char *InvalidGetRequestBodyException::what() const throw()
{
    return message_.c_str();
}

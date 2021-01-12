#include "snippet.h"
#include "too_long_content_exception.h"

TooLongContentException::TooLongContentException(Snippet::Field field,
                                                 int length) : got_(length)
{
    message_ = std::string("Too long ") + Snippet::fieldToString(field).toStdString() +
               std::string(" content! Got ") +
               std::to_string(got_) +
               std::string(" characters, maximum length of this field is ") +
               std::to_string(Snippet::fieldToItsMaxLength(field)) +
               std::string(".");
};

const char *TooLongContentException::what() const throw()
{
    return message_.c_str();
}

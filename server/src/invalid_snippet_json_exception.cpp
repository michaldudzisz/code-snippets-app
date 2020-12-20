#include "invalid_snippet_json_exception.h"

#include "snippet.h"

InvalidSnippetJsonException::InvalidSnippetJsonException()
{
    message_ = std::string("Given json object does not include all necessary fields. "
                           "Necessary fields are: author, created, lang, content.");
};

const char *InvalidSnippetJsonException::what() const throw()
{
    return message_.c_str();
}

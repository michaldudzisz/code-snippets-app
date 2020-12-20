#include "invalid_snippet_json_exception.h"

#include "snippet.h"

InvalidSnippetJsonException::InvalidSnippetJsonException()
{
    message_ = std::string("Problem with parsing json snippet object. "
                           "Necessary fields are: author, created, lang, content, and all are strings.");
};

const char *InvalidSnippetJsonException::what() const throw()
{
    return message_.c_str();
}

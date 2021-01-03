#ifndef INVALID_GET_REQUEST_BODY_EXCEPTION
#define INVALID_GET_REQUEST_BODY_EXCEPTION

#include <string>
#include <exception>

class InvalidGetRequestBodyException : public std::exception
{
public:
    InvalidGetRequestBodyException();
    const char *what() const throw();

private:
    std::string message_ = "Invalid snippet search match pattern. "
        "Pattern should have fileds: "
        "author_subsequence, "
        "title_subsequence, "
        "created_from, "
        "created_to, "
        "lang. "
        "Createds should be numeric value in secs since epoche format. "
        "Rest should be character strings with restrictions as with snippet.";
};

#endif
#ifndef DATABASE_ERROR_EXCEPTION
#define DATABASE_ERROR_EXCEPTION

#include <string>
#include <exception>

/**
 * @brief Exception thrown in ApiHandler, when something goes wrong with connection with database, 
 * eg. unable to save/pull snippet due to server/database problem.
 */ 

class DatabaseErrorException : public std::exception
{
public:
    /** @param info Information to be stored as an error message for client-side user. */
    DatabaseErrorException(const char * info);

    /** Returns error message */
    const char *what() const throw();

private:
    std::string message_;
};


#endif
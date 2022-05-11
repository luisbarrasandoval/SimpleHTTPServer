#ifndef STATUS_CODE
#define STATUS_CODE

#include <string>
enum StatusCode
{
    OK = 200,
    REDIRECT = 301,
    AUTHORIZATION_REQUIRED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
};

std::string get_status_code_message(int status_code)
{
    switch (status_code)
    {
    case OK:
        return "OK";
    case REDIRECT:
        return "REDIRECT";
    case AUTHORIZATION_REQUIRED:
        return "AUTHORIZATION_REQUIRED";
    case FORBIDDEN:
        return "FORBIDDEN";
    case NOT_FOUND:
        return "NOT_FOUND";
    case INTERNAL_SERVER_ERROR:
        return "INTERNAL_SERVER_ERROR";
    default:
    }
        return "UNKNOWN";
}


#endif
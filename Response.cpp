#ifndef RESPONSE
#define RESPONSE

#include <string>
#include "status_code.h"
#include "Header.cpp"

class Response
{
public:
    Response() {}
    void set_status_code(StatusCode status_code)
    {
        this->headers.set_status_code(status_code);
    }
    void set_header(std::string key, std::string value)
    {
        this->headers.set_header(key, value);
    }
    void send(std::string body)
    {
        this->body += body;
    }

    std::string get_body()
    {
        return body;
    }

    std::string get_raw_header()
    {

        headers.update_content_length(body.size());
        return headers.get_raw_header();
    }

private:
    std::string body;
    Header headers;
};

#endif
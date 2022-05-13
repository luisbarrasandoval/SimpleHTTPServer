#ifndef REQUESTS
#define REQUESTS

#include <map>
#include <string>
#include "Header.cpp"

class Request
{
public:
    Request(Header h)
    {
        this->headers = h;
    }

    std::map<std::string, std::string> get_querys()
    {

        std::string raw_query = headers.get_raw_querys();
        std::stringstream ss(raw_query);
        std::string token;
        while (std::getline(ss, token, '&'))
        {
            std::string key = token.substr(0, token.find('='));
            std::string value = token.substr(token.find('=') + 1);
            querys[key] = value;
        }

        return querys;
    }

private:
    std::map<std::string, std::string> querys;
    Header headers;
};

#endif
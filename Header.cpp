#include <iostream>
#include <string>
#include <sstream>
#include <map>

class Header
{
public:
    std::string path;
    std::string method;
    Header(char *raw_header)
    {
        this->raw_header = raw_header;
    }

    static Header parse_header(char *raw_header)
    {
        Header n = Header(raw_header);
        n.parse_header();
        return n;
    }

    std::string get_header(std::string key)
    {
        return this->headers[key];
    }

    std::string get_raw_header()
    {
        return this->raw_header;
    }

    void print_headers()
    {
        std::cout << "METHOD: " << this->method << std::endl;
        std::cout << "PATH: " << this->path << std::endl;
        std::cout << "======== HEADERS =========" << std::endl;
        for (auto it = headers.begin(); it != headers.end(); ++it)
        {
            std::cout << it->first << "-> " << it->second << std::endl;
        }

        std::cout << "==========================" << std::endl;
    }

private:
    std::string raw_header;

    std::map<std::string, std::string> headers;

    void parse_header()
    {

        std::stringstream ss(raw_header);
        std::string line;
        std::getline(ss, line);
        std::stringstream ss_line(line);
        std::getline(ss_line, method, ' ');
        std::getline(ss_line, path, ' ');

        while (std::getline(ss, line))
        {
            std::stringstream ss_line(line);
            std::string key;
            std::string value;
            std::getline(ss_line, key, ':');
            std::getline(ss_line, value);

            if (key != "")
            {
                headers[key] = value;
            }
        }
    }
};
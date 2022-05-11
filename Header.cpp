#ifndef HEADER_CPP
#define HEADER_CPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "status_code.h"

class Header
{
public:
    std::string path;
    std::string method;

    Header()
    {
        path = "";
        method = "";
        raw_header = "";
    }

    static Header parse_header(char *raw_header)
    {
        Header n = Header();
        n.raw_header = raw_header;
        n.parse_header();
        return n;
    }

    std::string get_path()
    {
        return path;
    }

    void set_header(std::string key, std::string value)
    {
        headers[key] = value;
    }

    std::string get_header(std::string key)
    {
        return this->headers[key];
    }

    int get_status_code()
    {
        return this->status_code;
    }

    void set_status_code(int status_code)
    {
        this->status_code = 200;
    }

    std::string get_raw_header()
    {
        std::stringstream ss;
        ss << "HTTP/1.1 " << status_code << " " << get_status_code_message(status_code) << "\r\n";
        for (auto &kv : this->headers)
        {
            ss << kv.first << ": " << kv.second << "\r\n";
        }
        return ss.str();
    }

private:
    std::string raw_header;
    int status_code;
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

#endif
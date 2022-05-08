// respuesta del servidor

#include "Header.cpp"

class Response {
public:
    Response();
    void set_status(int status);
    void set_body(std::string body);
    void add_header(std::string key, std::string value);
private:
    Header headers;
};
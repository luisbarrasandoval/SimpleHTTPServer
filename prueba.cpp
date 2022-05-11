#include <string>
#include "Header.cpp"
#include "status_code.h"

int main() {
    Header h = Header();
    h.set_header("Content-Type", "text/html");
    h.set_header("Content-Length", "12");
    h.set_header("Connection", "close");
    h.set_header("Server", "MyServer");
    h.set_status_code(StatusCode::NOT_FOUND);

    std::string html = "<html><body>Hola mundo</body></html>";
    h.set_header("Content-Length", std::to_string(html.size()));

    std::cout << h.get_raw_header() << html << std::endl;

    return 0;
}
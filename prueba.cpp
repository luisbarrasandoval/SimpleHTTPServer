#include <string>
#include "Response.cpp"
#include "status_code.h"
#include "filetypes.h"

int main() {
    Response r = Response();
    r.set_status_code(StatusCode::OK);
    r.set_header("Content-Type", HTML);
    r.send("Hola mundo");
    r.send("Hola mundo");
    std::cout << r.get_raw_header() << std::endl;
    std::cout << r.get_body() << std::endl;

    return 0;
}
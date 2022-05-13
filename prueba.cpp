#include "Header.cpp"
#include "Request.cpp"
#include "Response.cpp"
#include "status_code.h"
#include "filetypes.h"
#include <string>
#include <map>

int main()
{
    Header h = Header::parse_header("POST /log?format=json&hasfast=true&authuser=0\r\n\
Host: play.google.com\r\n\
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:91.0) Gecko/20100101 Firefox/91.0\r\n\
Accept: */*\r\n\
Accept-Language: es-ES,es-CL;q=0.5\r\n\
Accept-Encoding: gzip, deflate, br\r\n\
Referer: https://translate.google.com/\r\n\
Content-Type: application/x-www-form-urlencoded;charset=utf-8 \r\n\
Content-Length: 3418\r\n\
Origin: https://translate.google.com\r\n\
Connection: keep-alive");

    Request r = Request(h);

    auto querys = r.get_querys();
    // print query
    for (auto it = querys.begin(); it != querys.end(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    return 0;
}
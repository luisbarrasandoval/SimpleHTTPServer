#include <iostream>
#include "server.cpp"
#include "filetypes.h"

int main(int args, char *argv[])
{
    Servidor servidor = Servidor(8080);

    servidor.get("/", [](Request *req, Response *res)
    {
        res->set_status_code(StatusCode::OK);
        res->set_header("Content-Type", HTML);
        res->send("<h1>Home</h1>");
        res -> send("<a href='/pagina2?user=luis&password=1234'>Pagina 2</a>");
    });

    servidor.get("/pagina2", [](Request *req, Response *res)
    {
        res->set_status_code(StatusCode::OK);
        res->set_header("Content-Type", HTML);
        res->send("<h1>Pagina 2</h1>");
        res->send("<a href='/'>Home</a><br>");

        auto querys = req->get_querys();
            for (auto query : querys)
            {
                res->send(query.first + ": " + query.second);
                res->send("<br>");
            }
    });

    servidor.run();

    return 0;
}
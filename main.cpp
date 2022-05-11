#include "server.cpp"
#include "filetypes.h"

int main(int args, char *argv[])
{
    Servidor servidor = Servidor(8080);

    servidor.get("/hola", [](Request req, Response res) {
        res.set_status_code(StatusCode::OK);
        res.set_header("Content-Type", HTML);
        res.send("Hola mundo");
    });

    servidor.run();

    return 0;
}
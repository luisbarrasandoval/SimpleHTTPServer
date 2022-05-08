#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.cpp"

int main(int args, char *argv[])
{
    Servidor servidor = Servidor(8080);
    
    servidor.get("/hola", []() {
        return "Hola mundo";
    });

    servidor.run();

    return 0;
}
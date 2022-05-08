#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.cpp"

int main(int args, char *argv[])
{
    Servidor servidor = Servidor(8080);

    servidor.run();

    return 0;
}
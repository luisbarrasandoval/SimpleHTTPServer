#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Header.cpp"

class Servidor
{
public:
    Servidor(int port)
    {
        init_socket(port);
        bind_socket();
        listen_socket();
    }

    void run()
    {
        main_loop();
    }

private:
    int sockfd;
    struct sockaddr_in server_address;

    void init_socket(int port)
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            perror("Error al crear el socket");
            exit(1);
        }

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        server_address.sin_addr.s_addr = INADDR_ANY;
    }

    void bind_socket()
    {
        if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        {
            perror("Error al bindear el socket");
            exit(1);
        }
    }

    void listen_socket()
    {
        if (listen(sockfd, 5) < 0)
        {
            perror("Error al escuchar el socket");
            exit(1);
        }
    }

    void main_loop()
    {
        char buffer[1024];

        while (true)
        {
            struct sockaddr_in client_address;
            socklen_t client_address_length = sizeof(client_address);

            int client_sockfd = accept(sockfd, (struct sockaddr *)&client_address, &client_address_length);
            if (client_sockfd < 0)
            {
                perror("Error al aceptar el cliente");
                exit(1);
            }

            memset(buffer, 0, sizeof(buffer));
            int n = read(client_sockfd, buffer, sizeof(buffer));
            if (n < 0)
            {
                perror("Error al leer del socket cliente");
                exit(1);
            }

            Header header = Header::parse_header(buffer);
            header.print_headers();

            char response[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>Hola mundo</body></html>";
            n = write(client_sockfd, response, strlen(response));
            if (n < 0)
            {
                perror("Error al escribir en el socket cliente");
                exit(1);
            }

            close(client_sockfd);
        }
    }
};
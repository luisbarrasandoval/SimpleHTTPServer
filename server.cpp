#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <functional>
#include "Header.cpp"
#include <map>

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

    // function
    void get(std::string path, std::function<std::string(void)> func)
    {
        routes[path] = func;
    }

private:
    int sockfd;
    struct sockaddr_in server_address;
    std::map<std::string, std::function<std::string(void)>> routes;

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

            // routes
            std::string path = header.path;
            std::string method = header.method;
            std::string response = "";

            if (routes.find(path) != routes.end())
            {
                response = routes[path]();
            }
            else
            {
                response = "404 Not Found";
            }

            // response
            std::string response_header = "HTTP/1.1 200 OK\r\n\r\n";
            std::string response_body = response;
            std::string response_full = response_header + response_body;

            // send

            n = write(client_sockfd, response_full.c_str(), response_full.size());
            if (n < 0)
            {
                perror("Error al escribir en el socket cliente");
                exit(1);
            }

            close(client_sockfd);
        }
    }
};
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 80           /* The port where our server will listen */
#define MAX_CONNECTIONS 5 /* The max number of connnections that a server will queue before it starts dropping */

int main()
{
    /* Define the socket file descriptors and socket structure */
    int socket_fd;
    struct sockaddr_in server_address;

    /* ### Create the socket
    The socket() is a blocking system call which creates a socket file descriptor.

    - The first variable, AF_INET is a system defined argument for address family which denotes
    that the socket will be used for IPv4 protocol communication.

    - The second variable, SOCK_STREAM is the socket type which is an enum for TCP byte stream.
    We can also use SOCK_DGRAM for UDP datagrams.

    - The third variable, 0 indicates that the default protocol should be used to create the socket.
    */
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("server: error while creating socket\n");
        exit(1);
    }

    /* ### Bind the socket to an address
    We assign the address family, port and address which needs to be bind to the socket.

    Then we bind the socket file descriptor with the socket address structure using bind().

    The bind() is a blocking system call.
    */
    server_address.sin_family = AF_INET;
    server_address.sin_port = PORT;
    server_address.sin_addr.s_addr = INADDR_ANY;
    bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address));

    /* ### Listen on the specified address
    The listen() is a blocking system call with which we start listening
    from the config that we bind in the bind() function.

    The function accepts max connections which is the no of connections the socket
    will queue before it starts refusing for more connections.
    */
    int listen_st;
    listen_st = listen(socket_fd, MAX_CONNECTIONS);
    if (listen_st < 0)
    {
        perror("server: error while listening socket\n");
        exit(1);
    }

    printf("server: Waiting for connections on port %i\n", PORT);

    /* ### Accept the connection
    Once the server starts listening, it will keep on waiting for a connection, thus a blocking call.
    The accept() will accept the connection and return a new socket descriptor for that connection.
    */
    while (1)
    {
        int client_fd;
        client_fd = accept(socket_fd, NULL, NULL);
        if (client_fd < 0)
        {
            perror("server: error while accepting the connection\n");
            exit(1);
        }

        printf("server: Connected with a client\n");

        /* ### Read the connection
        The read() system call reads the file descriptor and saves the value in the buffer that is passed to it.
        */
        int bytes_read;
        char request_buf[1024];
        bytes_read = read(client_fd, request_buf, sizeof(request_buf));
        if (bytes_read < 0)
        {
            perror("server: error while reading the request data\n");
            exit(1);
        }

        printf("server: Request Data:\n%s\n", request_buf);

        /* ### Parse the request data and handle the business logic
        Here, we add all our routing and business logic

        For now, I will add a simple hello world response for each request to the server
        */
        char response_buf[1024];
        strcpy(response_buf, "HTTP/1.1 200 OK\r\n");
        strcat(response_buf, "Content-Type: text/html\r\n");
        strcat(response_buf, "\r\n");
        strcat(response_buf, "<h1>Hello, world!</h1>");

        /* ### Write back the response to the client
        The write() system call writes the response buffer to the file descriptor.
        */
        int bytes_written;
        bytes_written = write(client_fd, response_buf, strlen(response_buf));
        if (bytes_written < 0)
        {
            perror("server: error while writing the response data\n");
            exit(1);
        }

        printf("server: Successfully written to client\n");

        /* ### Close the connection
        We finally close the connection after writing the response back to the client.
        */
        close(client_fd);
    }
    close(socket_fd);
}
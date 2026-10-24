#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>


// TCP server that listens on port 6379, just like the real redis
int main( int argc, char **argv) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;


    // what the fuck is AF??
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Failed to create server socker" << std::endl;
        return 1; // return 1 because server_fd is 1?? not sure how else to explain this.
    }

    // Since the tester restarts your program quite often, setting SO_REUSEADDR
    // ensures that we don't run into 'Address already in use' errors
    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        std::cerr << "setsockopt failed" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(6379);

    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) !=0) {
        std::cerr << "Feiled to bind to port 6379" << std::endl;
        return 1;
    }

    int connection_backlog = 5;
    // what is server_fd???
    if (listen(server_fd, connection_backlog) != 0) {
        std::cerr << "listen failed" << std::endl;
        return 1;
    }

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    std::cout << "waiting for a client to connect..." << std::endl;

    // You can use print statements as follows for debugging, th'll be visibile when running tests.
    std::cout << "Logs from your program will appear here!" << std::endl;

}

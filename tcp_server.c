#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SECRET_KEY "0123456789abcdef"

void handle_errors(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void encrypt_decrypt(char *data, size_t data_len) {
    for (size_t i = 0; i < data_len; ++i) {
        data[i] ^= SECRET_KEY[i % strlen(SECRET_KEY)];
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        handle_errors("socket failed");
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        handle_errors("setsockopt failed");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        handle_errors("bind failed");
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        handle_errors("listen failed");
    }

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        handle_errors("accept failed");
    }

    int read_len = read(new_socket, buffer, BUFFER_SIZE);
    if (read_len < 0) {
        handle_errors("read failed");
    }

    // Decrypt the message
    encrypt_decrypt(buffer, read_len);
    printf("Received (decrypted): %s\n", buffer);

    // Encrypt the response
    char *response = "Hello from server";
    encrypt_decrypt(response, strlen(response));

    send(new_socket, response, strlen(response), 0);
    printf("Encrypted response sent\n");

    close(new_socket);
    close(server_fd);

    return 0;
}


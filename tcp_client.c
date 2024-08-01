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
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        handle_errors("socket creation error");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        handle_errors("invalid address / address not supported");
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        handle_errors("connection failed");
    }

    char *message = "Hello from client";
    encrypt_decrypt(message, strlen(message));
    send(sock, message, strlen(message), 0);
    printf("Encrypted message sent\n");

    int read_len = read(sock, buffer, BUFFER_SIZE);
    if (read_len < 0) {
        handle_errors("read failed");
    }

    // Decrypt the response
    encrypt_decrypt(buffer, read_len);
    printf("Received (decrypted): %s\n", buffer);

    close(sock);

    return 0;
}


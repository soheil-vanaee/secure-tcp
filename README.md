
# Secure TCP Client-Server Example in C

This repository contains a simple TCP client-server example written in C with basic security hardening techniques. The server and client communicate over a TCP connection with simple XOR encryption for data transmission.

## Features

- Basic TCP client-server communication
- Simple XOR encryption for data transmission
- Basic input validation
- Buffer management to prevent overflow

## Requirements

- GCC (GNU Compiler Collection)
- OpenSSL library

## Getting Started

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/secure-tcp-client-server.git
   cd secure-tcp-client-server
   ```

2. **Install OpenSSL** (if not already installed):
   ```bash
   sudo apt-get update
   sudo apt-get install libssl-dev
   ```

### Compilation

1. **Compile the server**:
   ```bash
   gcc -o tcp_server tcp_server.c -lssl -lcrypto
   ```

2. **Compile the client**:
   ```bash
   gcc -o tcp_client tcp_client.c -lssl -lcrypto
   ```

### Running the Programs

1. **Run the server**:
   ```bash
   ./tcp_server
   ```

2. **Run the client**:
   ```bash
   ./tcp_client
   ```

### How It Works

1. **Server**:
   - Listens on port `8080`.
   - Accepts incoming connections.
   - Receives an encrypted message from the client.
   - Decrypts the message and prints it.
   - Sends an encrypted response back to the client.

2. **Client**:
   - Connects to the server on `127.0.0.1:8080`.
   - Sends an encrypted message to the server.
   - Receives an encrypted response from the server.
   - Decrypts the response and prints it.

### Encryption

The example uses a simple XOR encryption with a predefined key (`SECRET_KEY`). This is not suitable for real-world applications where stronger encryption algorithms like AES should be used.

### Error Handling

The code includes basic error handling using the `handle_errors` function to print error messages and terminate the program if necessary.

### Buffer Management

Buffers are managed to prevent overflows, and the buffer size is checked during read/write operations.

## Security Considerations

This example demonstrates basic security practices. For production use, consider the following:

- Use a stronger encryption algorithm (e.g., AES).
- Implement comprehensive input validation.
- Improve error handling and logging.
- Securely manage and store encryption keys.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [OpenSSL](https://www.openssl.org/) for encryption libraries.

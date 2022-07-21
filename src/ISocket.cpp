//
// Created by Semih Akkoç on 6/30/22.
//

#include "ISocket.h"
#include <thread>


bool TCPServer::open() {


    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = INADDR_ANY;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Failed Socket");
        return false;
    }

//    int opt = 1;
//    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
//        perror("Failed Reserving Socket");
//        return false;
//    }

    if (bind(sockfd, (struct sockaddr *) &adr, sizeof(adr)) != 0) {
        perror("Failed Binding");
        return false;
    }
    else
        std::cout << "Socket successfully binded." << std::endl;

    if (listen(sockfd, 5) != 0) { // Here, we set the maximum size for the backlog queue to 5.
        perror("Failed Listen");
        return false;
    }
    else
        std::cout << "Server listening..." << std::endl;

    // Connection Timeout
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    clilen = sizeof(adr2);
    newsockfd = accept(sockfd, (struct sockaddr *) &adr2, (socklen_t *) &clilen);

    if (newsockfd < 0) {
        perror("Failed Accepting");
        return false;
    }

    printf("Server: got connection from %s port %d\n", inet_ntoa(adr2.sin_addr), ntohs(adr2.sin_port));
    return true;
}


void TCPServer::send(uint8_t * data) {
    if(::send(this->newsockfd, data, strlen((const char *) data), MSG_NOSIGNAL) == -1)
        std::cout << "Data could not sent." << std::endl;
    else
        std::cout << "Data successfully sent." << std::endl;
}


uint8_t * TCPServer::recv() {
    n = ::recv(newsockfd, buffer, 1024, 0);
    if (n < 0)
        perror("Failed Reading from Socket");

    return (uint8_t *) buffer;
}


TCPServer::~TCPServer() {
    close(newsockfd);
    shutdown(sockfd, SHUT_RDWR);
}


bool TCPClient::open() {
    if (server == NULL) {
        perror("Error no such host.");
        return false;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket failed.");
        return false;
    }
    else
        std::cout << "Socket successfully created." << std::endl;

    adr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &adr.sin_addr.s_addr, server->h_length);

    if (inet_pton(AF_INET, server->h_name, &adr.sin_addr) <= 0) {
        perror("Invalid address");
        return false;
    }
    else
        std::cout << "Socket has valid address." << std::endl;

    if (connect(sockfd, (sockaddr *) &adr, sizeof(adr)) != 0) {
        perror("ERROR connecting");
        return false;
    }
    else
        std::cout << "Socket successfully connected." << std::endl;

    return true;
}


void TCPClient::send(uint8_t * data) {
    n = ::write(sockfd, data, strlen((char *) data));
    if (n < 0)
        perror("ERROR writing to socket");
}


uint8_t * TCPClient::recv() {
    bzero(buffer,4097);
    n = ::recv(sockfd, buffer, 4096, 0);
    if (n < 0)
        perror("ERROR reading from socket");
    return (uint8_t *) buffer;
}


TCPClient::~TCPClient() {
    close(sockfd);
}



bool UDPServer::open() {
    memset(&adr, 0, sizeof(adr));
    memset(&adr2, 0, sizeof(adr2));

    adr.sin_family = AF_INET; // IPv4
    adr.sin_addr.s_addr = INADDR_ANY;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Failed Socket");
        return false;
    }
    else
        std::cout << "Socket created successfully." << std::endl;


    if (bind(sockfd, (const sockaddr *) &adr, sizeof(adr)) < 0) {
        perror("Failed Binding");
        return false;
    }
    else
        std::cout << "Bind successful." << std::endl;

    return true;
}


void UDPServer::send(uint8_t *data) {         // there is no MSG_CONFIRM flag, no flag initiated (0)
    sendto(sockfd, (const char *) data, strlen((const char *) data), MSG_SEND, (const sockaddr *) &adr2, sizeof(adr2));
}



uint8_t * UDPServer::recv() {
    n = recvfrom(sockfd, (char *) buffer, 1024, MSG_WAITALL, (sockaddr *) &adr2, (socklen_t *) sizeof(adr2));
    buffer[n] = '\0';
    return (uint8_t *) buffer;
}


UDPServer::~UDPServer() {
    close(sockfd);
}


bool UDPClient::open() {
    memset(&adr, 0, sizeof(adr));

    // filling the server information
    adr.sin_family = AF_INET; // IPv4
    adr.sin_addr.s_addr = INADDR_ANY;


    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Failed Socket");
        return false;
    }
    else
        std::cout << "Socket successfully created." << std::endl;

    return true;
}


void UDPClient::send(uint8_t *data) {
    sendto(sockfd, (const char *) data, strlen((const char *) data), MSG_SEND, (const sockaddr *) &adr, sizeof(adr));
}


uint8_t *UDPClient::recv() {
    n = recvfrom(sockfd, (char *) buffer, 1024, MSG_WAITALL, (sockaddr *) &adr, (socklen_t *) sizeof(adr));
    buffer[n] = '\0';
    return (uint8_t *) buffer;
}


UDPClient::~UDPClient() {
    close(sockfd);
}

ISocket *SocketFactory::create(SocketType type, bool is_server, int port, const char * hostname) {
    switch (type)
    {
        case TCP: {
            if (is_server) { // server
                    TCPServer * server_socket = new TCPServer();
                    server_socket->adr.sin_port = htons(port);
                    bool state = server_socket->open();
                    if (!state)
                        exit(EXIT_FAILURE);
                    return server_socket;
            }
            else { // client
                    TCPClient * client_socket = new TCPClient();
                    client_socket->adr.sin_port = htons(port);
                    client_socket->server = gethostbyname(hostname);
                    client_socket->adr.sin_addr.s_addr = inet_addr(hostname);
                    bool state = client_socket->open();
                    if (!state)
                        exit(EXIT_FAILURE);
                    return client_socket;
            }
        }
        case UDP: {
            if (is_server) { // server
                UDPServer * server_socket = new UDPServer();
                server_socket->adr.sin_port = htons(port);
                bool state = server_socket->open();
                if (!state)
                    exit(EXIT_FAILURE);
                return server_socket;
            }
            else { // client
                UDPClient * client_socket = new UDPClient();
                client_socket->adr.sin_port = htons(port);
                bool state = client_socket->open();
                if (!state)
                    exit(EXIT_FAILURE);
                return client_socket;
            }
        }
        default: {
            perror("Wrong type! For UDP enter: UDP , TCP enter: TCP");
            exit(EXIT_FAILURE);
        }
    }
}

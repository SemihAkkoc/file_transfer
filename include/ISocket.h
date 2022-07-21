//
// Created by Semih Akkoç on 6/30/22.
//



#ifndef LEARNING_ISOCKET_H
#define LEARNING_ISOCKET_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <cstring>


enum SocketType {
    TCP,
    UDP
};

class ISocket {
public:
    virtual ~ISocket() {};
    virtual bool open()=0;
    virtual void send(uint8_t * data)=0;
    virtual uint8_t * recv()=0;

public:
    int sockfd, portno, n;
    socklen_t clilen;
    sockaddr_in adr;
    char buffer[4096]= {0};
};

class TCPClient : public ISocket {
public:
    ~TCPClient() override;
    bool open() override;
    void send(uint8_t * data) override;
    uint8_t * recv() override;

public:
    hostent * server;
};

class TCPServer : public ISocket {
public:
    ~TCPServer() override;
    bool open() override;
    void send(uint8_t * data) override;
    uint8_t * recv() override;

private:
    int newsockfd;
    sockaddr_in adr2;
};

class UDPClient : public ISocket {
public:
    ~UDPClient() override;
    bool open() override;
    void send(uint8_t * data) override;
    uint8_t * recv() override;
public:
};

class UDPServer : public ISocket {
public:
    ~UDPServer() override;
    bool open() override;
    void send(uint8_t * data) override;
    uint8_t * recv() override;

private:
    sockaddr_in adr2;
};


class ISocketFactory {
public:
    virtual ISocket * create(SocketType type, bool is_server, int port, const char * hostname)=0;
};

class SocketFactory : public ISocketFactory {
public:
    ISocket * create(SocketType type, bool is_server, int port, const char * hostname) override;
private:
    uint8_t * buffer = new uint8_t[8];
};


#endif //LEARNING_ISOCKET_H

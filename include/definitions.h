//
// Created by Semih Akkoç on 6/28/22.
//


#ifndef LEARNING_DEFINITIONS_H
#define LEARNING_DEFINITIONS_H

#include <iostream>
#include <fstream>
#include "ISocket.h"
#include "definitions.h"

struct socket_type {
    SocketType s_type;
    bool is_server;
    int port;
    std::string pathname;
    bool error = false;
};

void inline check(std::ifstream* my_stream) {
    (!my_stream) ? std::cout << "A problem has occurred." << std::endl : std::cout << "Successfully opened file." << std::endl;
}

void inline check(std::ofstream* my_stream) {
    (!my_stream) ? std::cout << "A problem has occurred." << std::endl : std::cout << "Successfully opened file." << std::endl;
}

int inline file_size(std::ifstream * my_stream) {
    my_stream->seekg(0, my_stream->end);
    int length = my_stream->tellg();
    my_stream->seekg(0, my_stream->beg);
    return length;
}

inline const char * lower(const char * str) {
    size_t len = strlen(str);
    char * new_str = new char[len] ;
    for (int i=0; i<len; i++) { // memcpy
        new_str[i] = (char) std::tolower(str[i]);
    }
    return new_str;
}

socket_type inline check(int argc, char * argv[]) {

    socket_type * current = new socket_type;
    int total = 0;
    int port = 0;
    std::string pathname;

    if(argc == 5) {
        const char * wanted[6] = {"tcp", "udp", "port", "s", "c", "file"};
        for (int i = 0; i < argc; i++) {
            if (i != 0) {
                if (i == 1 || i == 3) {
                    for (int j = 0; j < sizeof(wanted) / sizeof(*wanted); j++) {
                        if (!strcmp(wanted[j], lower(&(argv[i])[1]))) {
                            total += j * j;
                        }
                    }
                }
                else if (i == 2) {
                    size_t len = strlen(argv[i]);
                    if (!strcmp(wanted[2], lower((std::string(argv[i]).substr(1, 4)).c_str())) &&
                        !strcmp("=", lower((std::string(argv[i]).substr(5, 1)).c_str()))) {
                        total += 1;
                        port = std::stoi(std::string(argv[i]).substr(6, len));
                    }
                }
                else if (i == 4) {
                    size_t len = strlen(argv[i]);
                    if (!strcmp(wanted[5], lower((std::string(argv[i]).substr(1, 4)).c_str())) &&
                            !strcmp("=", lower((std::string(argv[i]).substr(5, 1)).c_str()))) {
                        total += 1;
                        pathname = std::string(argv[i]).substr(6, len);
                    }
                }
            }
        }
    }
    switch (total) {
        case 11: {
            current->s_type = TCP;
            current->is_server = true;
            break;
        }
        case 18: {
            current->s_type = TCP;
            current->is_server = false;
            break;
        }
        case 12: {
            current->s_type = UDP;
            current->is_server = true;
            break;
        }
        case 19: {
            current->s_type = UDP;
            current->is_server = false;
            break;
        }
        default: {
            current->error = true;
            break;
        }
    }

    current->pathname = pathname;
    current->port = port;
    return * current;
}

#endif //LEARNING_DEFINITIONS_H

#include "FileReader.h"
#include "FileWriter.h"


/*
 *  In order to run this executable, arguments need to be given in the following order shown below. 
 *
 * ./file_transfer -tcp -port=5000 -s -file="pathname"
 * ./file_transfer -tcp -port=5000 -c -file="pathname"
 * ./file_transfer -udp -port=5000 -s -file="pathname"
 * ./file_transfer -udp -port=5000 -c -file="pathname"
 */


int main(int argc, char * argv[]) {
    socket_type my = check(argc, argv);
    if (!my.error) {
        if (my.is_server) {
            // initiate start by user input
            FileReader my_filereader(my.pathname.c_str());
            FileReaderSocket my_filereader_socket(my_filereader);
            my_filereader_socket.init(my.s_type, my.is_server, my.port);
            my_filereader.start();
        }
        else {
            FileWriterSocket my_filewriter_socket(my.s_type, my.is_server, my.port);
            FileWriter my_filewriter(my_filewriter_socket, my.pathname.c_str());
            my_filewriter_socket.start();
        }
    }
    else {
        perror("Wrong input!");
    }

    return 0;
}

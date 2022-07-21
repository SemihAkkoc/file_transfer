//
// Created by Semih Akkoç on 6/29/22.
//

#include "IFile.h"

File::File(char const * filename, char mode) {
    switch(mode) {
        case 'r': {
            try {
                std::ifstream * f = new std::ifstream(filename, std::ios::in | std::ios::binary);
                this->rf = f;
            }
            catch (int e) {
                const char * err_message = std::string("There is no such filename: " + std::string(filename)).c_str();
                perror(err_message);
            }
            this->length_of_the_buffer = length_of_the_file(this->rf);
            check(this->rf);
            break;
        }
        case 'w': {
            std::ofstream *f = new std::ofstream(filename, std::ios::out | std::ios::binary);
            this->wf = f;
            check(this->wf);
            break;
        }
        default: {
            break;
        }
    }
}

File::File(char const * filename, char const * destination) {
    File rf(filename, 'r');
    uint8_t * buffer = rf.read();
    this->length_of_the_buffer = rf.length_of_the_buffer;
    std::string destination_location = std::string(destination) + "/" + std::string(filename);
    File wf(destination_location.c_str(), 'w');
    wf.write(buffer, this->length_of_the_buffer);
}

File::File(const char *filename, const char *new_filename, const char *destination) {
    File rf(filename, 'r');
    uint8_t * buffer = rf.read();
    this->length_of_the_buffer = rf.length_of_the_buffer;
    std::string destination_location = std::string(destination) + "/" + std::string(new_filename);
    File wf(destination_location.c_str(), 'w');
    wf.write(buffer, this->length_of_the_buffer);
}

File::~File() {
    if (buffer != nullptr) {
        delete[] buffer;
    }
}

uint8_t * File::read() {
    this->buffer = new uint8_t[this->length_of_the_buffer];
    this->rf->read((char *) this->buffer, this->length_of_the_buffer);
    this->rf->close();
    std::cout << "Reading from the file is done." << std::endl;
    return this->buffer;
}

void File::write(uint8_t * buffer_, int length) {
    this->wf->write((char *) buffer_, length);
    this->wf->close();
}

int File::length_of_the_file(std::ifstream * f_) {
    int length = file_size(f_);
    return length;
}



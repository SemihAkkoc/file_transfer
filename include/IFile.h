
//
// Created by Semih Akkoç on 6/29/22.
//


#ifndef LEARNING_IFILE_H
#define LEARNING_IFILE_H

#include <iostream>
#include <fstream>
#include "definitions.h"
// look at uint8_t and virtual classes

class IFile{
public:
    virtual uint8_t * read()=0;
    virtual void write(uint8_t * buffer, int length)=0;
};

class File : public IFile {
public:
    ~File();
    File(char const * filename, char mode);
    File(char const * filename, char const * destination);
    File(char const * filename, char const * new_filename, char const * destination);
    uint8_t * read() override;
    void write(uint8_t * buffer, int length) override;
private:
    int length_of_the_file(std::ifstream* rf);

public:
    int length_of_the_buffer = 0;
    uint8_t * buffer = NULL;
private:
    std::ifstream * rf;
    std::ofstream * wf;
};

#endif //LEARNING_IFILE_H

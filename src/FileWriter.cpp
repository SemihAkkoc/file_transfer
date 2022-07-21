//
// Created by Semih Akkoç on 7/20/22.
//

#include "FileWriter.h"

FileWriterSocket::FileWriterSocket(SocketType type, bool is_server, int port, const char * hostname) {
    this->socket = this->factory.create(type, is_server, port, hostname);
}

void FileWriterSocket::start() {
    buffer = this->socket->recv();  // there may be problems with buffer
    this->notify();
}

void FileWriterSocket::attach(IObserver * observer) {
    observers.push_back(observer);
}

void FileWriterSocket::detach(IObserver * observer) {
    observers.remove(observer);
}

void FileWriterSocket::notify() {
    std::list<IObserver *>::iterator iterator = observers.begin();
    while (iterator != observers.end()) {
        (*iterator)->update((const char *) buffer);
        iterator++;
    }
}

FileWriter::FileWriter(FileWriterSocket &subject, const char * filename) : writer(subject) {
    this->writer.attach(this);
    this->file_writer = new File(filename, 'w');
    this->worker = new Worker();
    worker->setHandler(this);
}

void FileWriter::handle(void *) {
    file_writer->write(this->buffer, strlen((const char *) this->buffer));
    this->done = true;
}

void FileWriter::update(const char * message) {
    buffer = (uint8_t *) message;
    worker->start();
    while(!done);
    worker->stop();
    std::cout << "File transfer successful." << std::endl;
}
//
// Created by Semih Akkoç on 7/18/22.
//

#include "FileReader.h"

FileReader::FileReader(const char * filename) {
    this->file_reader = new File(filename, 'r');
    this->worker = new Worker();
    worker->setHandler(this);
}

void FileReader::handle(void *) {
    file_reader->read();
    this->notify();
}

void FileReader::attach(IObserver * observer) {
    observers.push_back(observer);
}

void FileReader::detach(IObserver * observer) {
    observers.remove(observer);
}

void FileReader::notify() {
    std::list<IObserver *>::iterator iterator = observers.begin();
    while (iterator != observers.end()) {
        (*iterator)->update((const char *) this->file_reader->buffer);
        iterator++;
    }
}

void FileReader::start() {
    this->worker->start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    this->worker->stop();
}

FileReaderSocket::FileReaderSocket(FileReader &subject) : reader(subject) {
    this->reader.attach(this);
}

void FileReaderSocket::init(SocketType type, bool is_server, int port, const char * hostname) {
    this->socket = this->factory.create(type, is_server, port, hostname);
}

void FileReaderSocket::update(const char * message) {
//    std::cout << message << std::endl;
//    for (int i=0; i<10; i++) {
//        std::cout << "data sent -> " << i + 1 << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    this->socket->send((uint8_t *) message);
//    }
}

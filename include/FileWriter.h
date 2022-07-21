//
// Created by Semih Akkoç on 7/20/22.
//

#ifndef LEARNING_FILEWRITER_H
#define LEARNING_FILEWRITER_H

#include "IWorker.h"
#include "IFile.h"
#include "ISocket.h"
#include "IObserver.h"
#include <list>

class FileWriterSocket : public ISubject {
public:
    FileWriterSocket(SocketType type, bool is_server, int port = 8080, const char * hostname = "127.0.0.1");
    void attach(IObserver * observer) override;
    void detach(IObserver * observer) override;
    void notify() override;
    void start();
private:
    SocketFactory factory;
    ISocket * socket;
    std::list<IObserver *> observers;
    uint8_t * buffer = NULL;

};

class FileWriter : public IHandler, public IObserver {
public:
    FileWriter(FileWriterSocket &subject, const char * filename="text.txt");
    void update(const char * message) override;
    void handle(void *) override;

public:
    bool done = false;
    IWorker * worker;
private:
    FileWriterSocket &writer;
    File * file_writer;
    uint8_t * buffer = NULL;
};



#endif //LEARNING_FILEWRITER_H

//
// Created by Semih Akkoç on 7/18/22.
//

#ifndef LEARNING_FILEREADER_H
#define LEARNING_FILEREADER_H

#include "IWorker.h"
#include "IFile.h"
#include "ISocket.h"
#include "IObserver.h"
#include <list>

class FileReader : public IHandler, public ISubject {
public:
    FileReader(const char * filename);
    void handle(void *) override;
    void attach(IObserver * observer) override;
    void detach(IObserver * observer) override;
    void notify() override;
    void start();

public:
    IWorker * worker;
private:
    std::list<IObserver *> observers;
    File * file_reader;
};


class FileReaderSocket : public IObserver {
public:
    FileReaderSocket(FileReader &subject);
    void init(SocketType type, bool is_server, int port = 5600, const char * hostname = "127.111.2.1");
    void update(const char * message) override;

private:
    SocketFactory factory;
    ISocket * socket;
    FileReader &reader;
};

#endif //LEARNING_FILEREADER_H

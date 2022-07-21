//
// Created by Semih Akkoç on 7/4/22.
//


#ifndef LEARNING_IWORKER_H
#define LEARNING_IWORKER_H

#include "IHandler.h"
#include <thread>
#include <vector>
#include <mutex>


class IWorker {
public:
    virtual ~IWorker() {};
    virtual void start()=0;
    virtual void run()=0;
    virtual void stop()=0;
    virtual void setHandler(IHandler * handle)=0;
};


class Worker : public IWorker {
public:
    ~Worker() {};
    Worker();
    void start() override;
    void run() override;
    void stop() override;
    void setHandler(IHandler * handler) override;

public:
    std::thread * worker_thread = nullptr;

private:
    std::mutex mtx;
    std::atomic<bool> isRunning;

protected:
    IHandler * handler;
};




#endif //LEARNING_IWORKER_H

//
// Created by Semih Akkoç on 7/4/22.
//

#include "IWorker.h"

Worker::Worker() : isRunning(false) {}

void Worker::start() {

    std::lock_guard<std::mutex> lock(this->mtx);
    isRunning = true;
    worker_thread = new std::thread(&Worker::run, this);

}

void Worker::run() {

//    while (isRunning) {
    if(this->handler)
        handler->handle(nullptr);
//    }

}

void Worker::stop() {

    std::lock_guard<std::mutex> lock(this->mtx);
    isRunning = false;
    if (worker_thread->joinable())
        worker_thread->join();
    else
        worker_thread->detach();

}

void Worker::setHandler(IHandler *handler) {
    this->handler = handler;
}
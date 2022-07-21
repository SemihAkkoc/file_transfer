//
// Created by Semih Akkoç on 7/18/22.
//

#ifndef LEARNING_IOBSERVER_H
#define LEARNING_IOBSERVER_H

class IObserver {
public:
    virtual ~IObserver() {};
    virtual void update(const char * message)=0;
};

class ISubject {
public:
    virtual ~ISubject() {};
    virtual void attach(IObserver * observer)=0;
    virtual void detach(IObserver * observer)=0;
    virtual void notify()=0;
};

#endif //LEARNING_IOBSERVER_H

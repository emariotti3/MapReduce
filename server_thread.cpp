#include "server_thread.h"

Thread::Thread(){}

void *Thread::runner(void *data){
    Thread *self = (Thread*)data;
    self->run();
    void* dummyPtr = NULL;
    return dummyPtr;
}

void Thread::start(){
    pthread_create(&thread, NULL, Thread::runner, this);
}

void Thread::join(){
    pthread_join(thread, NULL);
}


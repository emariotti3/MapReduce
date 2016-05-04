#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Env;
class Context;

class Thread{
    public:
        Thread();
        void start();
        void join();
        static void *runner(void *data);
        virtual void run() = 0;
    protected:
    private:
        pthread_t thread;
        Thread(const Thread&);
        Thread& operator=(const Thread&);
};

#endif // THREAD_H

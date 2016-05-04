#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex{
    public:
        Mutex();
        void lock();
        void unlock();
        virtual ~Mutex();
    protected:
    private:
        pthread_mutex_t mutex;
        Mutex(const Mutex&);
        Mutex& operator=(const Mutex&);
};

#endif // MUTEX_H

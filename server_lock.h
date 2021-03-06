#ifndef LOCK_H
#define LOCK_H

#include "server_mutex.h"

class Lock{
    public:
        explicit Lock(Mutex &mutex);
        virtual ~Lock();
    protected:
    private:
        Mutex &mutex;
        Lock(const Lock&);
        Lock& operator=(const Lock&);
};

#endif // LOCK_H

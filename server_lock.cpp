#include "server_lock.h"

Lock::Lock(Mutex &mutex):
mutex(mutex){
    mutex.lock();
}

Lock::~Lock(){
    mutex.unlock();
}

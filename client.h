#ifndef CLIENT_H
#define CLIENT_H

#include "common_system_error.h"
#include "common_socket.h"
#include "client_mapper.h"
#include <stdio.h>
#include <string>

class Client{
    public:
        Client(char hostname[], char port[]);
        void run();
        virtual ~Client();
    protected:
    private:
        char *hostname;
        char *port;
        Mapper mapper;
};

#endif // CLIENT_H

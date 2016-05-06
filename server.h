#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <iostream>

#include "server_reducer.h"
#include "server_city_info_receiver.h"
#include "server_client_acceptor.h"
#include "common_system_error.h"

#define SERVER_MODE "server"
#define SERVER_MODE_POS 0
#define SERVER_PORT_POS 1

class Server{
    public:
        Server(std::string &port);
        void addInfoReceiver(Socket *listener);
        void run();
        virtual ~Server();
    protected:
    private:
        std::string &port;
        int max_threads;
        //std::map<int, Reducer*> reducers;
        std::vector<CityInfoReceiver*> cities;
};

#endif // SERVER_H


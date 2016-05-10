#ifndef CLIENTACCEPTOR_H
#define CLIENTACCEPTOR_H

#include <vector>
#include "common_socket.h"
#include "server_city_info_receiver.h"
#include <string>

class Server;

class ClientAcceptor: public Thread{
    public:
        ClientAcceptor(char port[], Server &server);
        void run();
        void endClientAccept();
        virtual ~ClientAcceptor();
    protected:
    private:
        char *port;
        Socket *acceptor;
        Server &server;
        bool accept_mode;
        std::vector<Socket*> created;
};

#endif // CONNECTIONACCEPTOR_H

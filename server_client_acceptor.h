#ifndef CLIENTACCEPTOR_H
#define CLIENTACCEPTOR_H

#include <vector>
#include "common_socket.h"
#include "server_city_info_receiver.h"

class ClientAcceptor{
    public:
        ClientAcceptor(std::string hostname, std::string port);
        void acceptClients(std::vector<CityInfoReceiver*> &cities);
        virtual ~ClientAcceptor();
    protected:
    private:
        std::string hostname;
        std::string port;
        std::string end_signal;
        std::vector<Socket*> created;
};

#endif // CONNECTIONACCEPTOR_H

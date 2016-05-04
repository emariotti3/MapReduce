#ifndef CLIENT_H
#define CLIENT_H

#include "common_socket.h"
#include "client_mapper.h"
#include <stdio.h>

#define CLIENT_MODE "client"

class Client{
    public:
	//int main (int argc, char *argv[]);
        Client(std::string hostname, std::string port);
        void run();
        virtual ~Client();
    protected:
    private:
        std::string hostname;
        std::string port;
        Mapper mapper;
};


int main(int argc, char *argv[]){
    std::stringstream stream(*argv);
    const std::string client_mode = CLIENT_MODE;

	std::string mode = "";
	stream >> mode;
	bool mode_is_client = client_mode.compare(mode);

    if (!mode_is_client){
        //exception!
    }

    std::string hostname = "";
    std::string port = "";
    stream >> hostname;
    stream >> port;
    Client client(hostname, port);
    client.run();
    return 0;
}

#endif // CLIENT_H

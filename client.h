#ifndef CLIENT_H
#define CLIENT_H

#include "common_system_error.h"
#include "common_socket.h"
#include "client_mapper.h"
#include <stdio.h>

#define CLIENT_MODE "client"
#define CLIENT_MODE_POS 0
#define CLIENT_HOST_POS 1
#define CLIENT_PORT_POS 2

class Client{
    public:
        Client(std::string &hostname, std::string &port);
        void run();
        virtual ~Client();
    protected:
    private:
        std::string hostname;
        std::string port;
        Mapper mapper;
};

int main(int argc, char *argv[]){
	try{
		std::string mode(argv[CLIENT_MODE_POS]);
		const std::string client_mode = CLIENT_MODE;
		bool mode_is_client = client_mode.compare(mode);

		if (!mode_is_client){
			std::string error = "Invalid mode! Expected mode was 'client'!";
			throw SystemError(error, __FILE__, __LINE__);
		}
		
		std::string hostname(argv[CLIENT_HOST_POS]);
		std::string port(argv[CLIENT_PORT_POS]);
		
		Client client(hostname, port);
		client.run();
	}catch(SystemError &e){
		std::cout << e.what();
	}
    return 0;
}


#endif // CLIENT_H

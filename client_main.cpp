#ifndef CLIENT_MAIN_H
#define CLIENT_MAIN_H

#include "client.h"
#include <string>

#define CLIENT_HOST_POS 1
#define CLIENT_PORT_POS 2

int main(int argc, char *argv[]){
	try{
		char *hostname = argv[CLIENT_HOST_POS];
		char *port = argv[CLIENT_PORT_POS];		
		Client client(hostname, port);
		client.run();
	}catch(SystemError &e){
		std::cout << e.what();
	}
    return 0;
}

#endif // CLIENT_MAIN_H

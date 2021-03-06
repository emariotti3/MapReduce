#ifndef SERVER_MAIN_H
#define SERVER_MAIN_H

#include "server.h"
#include <string>

#define SERVER_PORT_POS 1

int main(int argc, char *argv[]){
	try{
		char *port = argv[SERVER_PORT_POS];
		Server s(port);
		s.run();
	}catch(SystemError &e){
		std::cout << e.what();
	}
    return 0;
}

#endif // SERVER_MAIN_H

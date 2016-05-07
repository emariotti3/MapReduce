#include "server.h"

#ifndef SERVER_MAIN_H
#define SERVER_MAIN_H

#define SERVER_MODE "server"
#define SERVER_MODE_POS 0
#define SERVER_PORT_POS 1

int main(int argc, char *argv[]){
	try{
		std::string mode(argv[SERVER_MODE_POS]);
		const std::string server_mode = SERVER_MODE;
		bool mode_is_server = server_mode.compare(mode);

		if (!mode_is_server){
			std::string error = "Invalid mode! Expected mode was 'server'!";
			throw SystemError(error, __FILE__, __LINE__);
		}

		std::string port(argv[SERVER_PORT_POS]);
		
		Server s(port);
		s.run();
	}catch(SystemError &e){
		std::cout << e.what();
	}
    return 0;
}

#endif // SERVER_MAIN_H

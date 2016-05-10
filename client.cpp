#include "client.h"
#include "common_system_error.h"
#include <queue>
#include <sstream>
#include <string>

Client::Client(char hostname[], char port[]):
hostname(hostname),
port(port)
{}

void Client::run(){
    std::string end_pairs = "End\n"; 
    std::queue<std::string> keys_values;
    this->mapper.remap(std::cin, keys_values);
    keys_values.push(end_pairs);
	
    Socket client(this->hostname, this->port, false);
	
	bool connected = client.socket_connect();
	
	if (!connected){
        std::string error = "Connection to server was unsuccessful!";
        throw new SystemError(error, __FILE__, __LINE__);
    }
    
    while (!keys_values.empty()){
        std::string key_value = keys_values.front();
        keys_values.pop();
        char *kv_char = &(key_value)[0u];
        client.socket_send(kv_char, key_value.size());
    }
}

Client::~Client(){}


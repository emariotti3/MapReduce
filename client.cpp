#include "client.h"
#include "common_system_error.h"
#include <queue>
#include <sstream>

Client::Client(std::string hostname, std::string port):
hostname(hostname),
port(port)
{}

void Client::run(){
    Socket client(this->hostname, this->port, false);
    std::string end_pairs = "End\n";
    bool connected = client.socket_connect();
    if(!connected){
        std::string error = "Connection to server was unsuccessful!";
        throw new SystemError(error, __FILE__, __LINE__);
    }
    std::queue<std::string> keys_values;
    this->mapper.remap(std::cin, keys_values);
    keys_values.push(end_pairs);

    while(!keys_values.empty()){
        std::string key_value = keys_values.front();
        keys_values.pop();
        char *kv_char = &(key_value)[0u];
        client.socket_send(kv_char, key_value.size());
    }
}

Client::~Client(){}


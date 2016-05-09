#include "common_socket_info.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

SocketInfo::SocketInfo(){
    memset(&this->hints, 0, sizeof(struct addrinfo));
    this->hints.ai_family = AF_INET;
    this->hints.ai_socktype = SOCK_STREAM;
}

void SocketInfo::generateInfo(std::string &hostname, std::string &port, bool set_flags){
    this->hints.ai_flags = set_flags? AI_PASSIVE:0;
    getaddrinfo(hostname.c_str(), port.c_str(), &this->hints, &this->addr);
}

SocketInfo::~SocketInfo(){
    freeaddrinfo(this->addr);
}

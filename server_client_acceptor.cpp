#include "server_client_acceptor.h"
#include "server_thread.h"
#include "server.h"
#include <iostream>

#define HOSTNAME "localhost"

ClientAcceptor::ClientAcceptor(std::string &port, Server &server):
port(port),
server(server){
	std::string host = HOSTNAME;
	this->acceptor = new Socket(&host, port, true);
	this->acceptor->socket_bind();
    this->acceptor->socket_listen();
    this->accept_mode = true;
}

void ClientAcceptor::run(){
    while(this->accept_mode){
		std::string host = HOSTNAME;
        Socket *listener = new Socket(&host, this->port, true);
        acceptor->socket_accept(*listener);
        this->server.addInfoReceiver(listener);
        //this->created.push_back(listener);
    }
}

void ClientAcceptor::endClientAccept(){
	this->acceptor->socket_shutdown();
	this->accept_mode = false;
}

ClientAcceptor::~ClientAcceptor(){
	delete this->acceptor;
    //delete[] &this->created;
}


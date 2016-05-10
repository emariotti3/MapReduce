#include "server_client_acceptor.h"
#include "server_thread.h"
#include "server.h"
#include <iostream>
#include <string>

ClientAcceptor::ClientAcceptor(char port[], Server &server):
port(port),
server(server){
	this->acceptor = new Socket(NULL, port, true);
	this->acceptor->socket_bind();
    this->acceptor->socket_listen();
    this->accept_mode = true;
}

void ClientAcceptor::run(){
    while (this->accept_mode){
        Socket *listener = new Socket(NULL, this->port, true);
        acceptor->socket_accept(*listener);
        if (this->accept_mode){
			this->server.addInfoReceiver(listener);
		}
        this->created.push_back(listener);
    }
}

void ClientAcceptor::endClientAccept(){
	this->acceptor->socket_shutdown();
	this->accept_mode = false;
}

ClientAcceptor::~ClientAcceptor(){
	delete this->acceptor;
	for (size_t i = 0; i < this->created.size(); i++){
		delete this->created[i];
	}
}


#include "server_client_acceptor.h"
#include <iostream>

ClientAcceptor::ClientAcceptor(std::string hostname, std::string port):
hostname(hostname),
port(port){
    this->end_signal = "q";
}

void ClientAcceptor::acceptClients(std::vector<CityInfoReceiver*> &cities){
    Socket acceptor(this->hostname, this->port, true);
    std::string input = "";
    std::cin >> input;
    while(input.compare(this->end_signal) != 0){
        Socket *listener = new Socket(this->hostname, this->port, true);
        acceptor.socket_accept(*listener);
        CityInfoReceiver *info_rec = new CityInfoReceiver(*listener);
        info_rec->start();
        cities.push_back(info_rec);
        this->created.push_back(listener);
        std::cin >> input;
    }
    acceptor.socket_shutdown();
    for(size_t i = 0; i < cities.size(); i++){
        cities[i]->join();
    }
}

ClientAcceptor::~ClientAcceptor(){
    delete[] &this->created;
}


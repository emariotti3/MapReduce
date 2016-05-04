#include "server.h"
#include <string>
#include <sstream>

Server::Server(std::string port):
port(port){
    this->hostname = "localhost";
    this->max_threads = 4;
}

void Server::run(){
    ClientAcceptor acceptor(this->hostname, this->port);
    std::vector<CityInfoReceiver*> city_info_rec;
    acceptor.acceptClients(city_info_rec);

    int max_days = 31;
    for(int i = 1; i <= max_days; i++){
        for(size_t j = 0; j < city_info_rec.size(); j++){
            bool city_has_info_day = city_info_rec[j]->hasWeatherForDay(i);
            bool day_reducer_exists = (reducers.count(i) > 0 );
            if(city_has_info_day && !day_reducer_exists){
                this->reducers.insert(std::map<int, Reducer*>::value_type(i, new Reducer(i)));
            }
            if(city_has_info_day){
                this->reducers[i]->add(city_info_rec[j]->getWeatherForDay(i));
            }
        }
    }
    size_t executed_reducers = 0;
    size_t pos = 0;
    while(executed_reducers < reducers.size()){
        pos = executed_reducers + this->max_threads;
        for(size_t i = executed_reducers; i < pos; i++){
            this->reducers[i]->start();
        }
        for(size_t i = executed_reducers; i < pos; i++){
            this->reducers[i]->join();
            executed_reducers++;
        }
    }
}

Server::~Server(){
    delete[] &this->reducers;
}


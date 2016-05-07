#include "server.h"
#include "server_city_info_receiver.h"
#include <string>
#include <sstream>

#define END_SIGNAL "q"
#define MAX_THREADS 4

Server::Server(std::string &port):
port(port){
    this->max_threads = MAX_THREADS;
}

void Server::addInfoReceiver(Socket *listener){
	Lock l(this->mutex);
	CityInfoReceiver *info_rec = new CityInfoReceiver(*listener, *this);
	this->cities.push_back(info_rec);
	info_rec->start();
}

void Server::addInfoWeather(std::string &info_weather){
	Lock l(this->mutex);
	CityWeather *city_weather = this->city_wf.newCityWeather(info_weather);
	int key = city_weather->getDay();
	if(this->daily_weather_info.count(key) > 0){
		this->daily_weather_info[key].push_back(city_weather);
	}else{
		std::vector<CityWeather*> values;
		values.push_back(city_weather);
		this->daily_weather_info.insert(std::map<int, std::vector<CityWeather*> >::value_type(key, values));
	}
}


void Server::run(){
	std::string end_accept = END_SIGNAL;
    ClientAcceptor acceptor(this->port, *this);
    acceptor.start();
	
	std::string input = "";
	while (input.compare(END_SIGNAL) != 0){
		std::cin >> input;
	}
	
	acceptor.endClientAccept();
	acceptor.join();
	
	for(size_t i = 0; i < cities.size(); i++){
        cities[i]->join();
    }
///-------------------refactor!------------///

/*
    for(int i = 1; i <= MAX_DAYS_MONTH; i++){
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
    }*/
}

Server::~Server(){
    //delete[] &this->reducers;
}


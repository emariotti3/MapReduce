#include "server.h"
#include "server_city_info_receiver.h"
#include "server_ranking_maker.h"
#include <string>
#include <sstream>

#define END_SIGNAL "q"
#define MAX_THREADS 4

typedef std::map<int, std::vector<CityWeather*> *> WeatherMap;
typedef std::vector<CityWeather*> CityWeatherList;

Server::Server(std::string &port):
port(port){
    this->max_threads = MAX_THREADS;
}

void Server::addInfoReceiver(Socket *listener){
	CityInfoReceiver *info_rec = new CityInfoReceiver(*listener, *this);
	this->cities.push_back(info_rec);
	info_rec->start();
}

void Server::addInfoWeather(std::string &info_weather){
	Lock l(this->mutex);
	CityWeather *city_weather = this->city_wf.newCityWeather(info_weather);
	int key = city_weather->getDay();
	if(this->daily_weather_info.count(key) > 0){
		this->daily_weather_info[key]->push_back(city_weather);
	}else{
		CityWeatherList values;
		this->daily_weather_info.insert(WeatherMap::value_type(key, &values));
		this->daily_weather_info[key]->push_back(city_weather);
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
    
    RankingMaker rankingMaker;
    rankingMaker.printOrderByTempertaure(this->daily_weather_info);
}

Server::~Server(){}


#include "server.h"
#include "server_city_info_receiver.h"
#include "server_ranking_maker.h"
#include <string>
#include <sstream>

#define END_SIGNAL "q"

typedef std::multimap<int, CityWeather*> WeatherMap;
typedef std::multimap<int, CityWeather*>::iterator WeatherMapIt;
typedef std::vector<CityWeather*> CityWeatherList;
typedef std::map<int, Reducer*> ReducerMap;
typedef std::map<int, Reducer*>::iterator ReducerMapIt;

Server::Server(std::string &port){
	this->city_wf = new CityWeatherFactory();
	this->acceptor = new ClientAcceptor(port, *this);
}

void Server::addInfoReceiver(Socket *listener){
	CityInfoReceiver *info_rec = new CityInfoReceiver(*listener, *this);
	this->cities.push_back(info_rec);
	info_rec->start();
}

void Server::addInfoWeather(std::string &info_weather){
	Lock l(this->mutex);
	CityWeather *city_weather = this->city_wf->newCityWeather(info_weather);
	int key = city_weather->getDay();
	this->daily_weather_info.insert(WeatherMap::value_type(key, city_weather));
}

void Server::run(){
	std::string end_accept = END_SIGNAL;
    acceptor->start();
	
	std::string input = "";
	while (input.compare(END_SIGNAL) != 0){
		std::cin >> input;
	}
	
	acceptor->endClientAccept();
	acceptor->join();
	
	for(size_t i = 0; i < cities.size(); i++){
        cities[i]->join();
    }
    
    RankingMaker rankingMaker(&this->daily_weather_info);
    rankingMaker.printOrderByTempertaure();
}

Server::~Server(){
	for (size_t i = 0; i < this->cities.size(); i++){
		delete this->cities[i];
	}
	delete this->city_wf;
	delete this->acceptor;
}


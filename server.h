#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include "server_reducer.h"
#include "server_city_weather_factory.h"
#include "server_client_acceptor.h"
#include "common_system_error.h"
#include "server_mutex.h"
#include "server_lock.h"

typedef std::multimap<int, CityWeather*> WeatherMap;
typedef std::vector<CityInfoReceiver*> CityInfoReceiverList;

class CityInfoReceiver;

class Server{
    public:
        Server(std::string &port);
        void addInfoReceiver(Socket *listener);
        void addInfoWeather(std::string &info_weather);
        void run();
        virtual ~Server();
    protected:
    private:
		Mutex mutex;
        CityInfoReceiverList cities;
        WeatherMap daily_weather_info;
        CityWeatherFactory *city_wf;
        ClientAcceptor *acceptor;
};

#endif // SERVER_H


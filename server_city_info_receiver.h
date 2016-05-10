#ifndef CITYINFORECEIVER_H
#define CITYINFORECEIVER_H

#include <string>
#include <map>
#include <vector>
#include "common_socket.h"
#include "server_thread.h"
#include "server_city_weather.h"

class Server;
typedef std::vector<std::string> strList;

class CityInfoReceiver: public Thread{
    public:
        CityInfoReceiver(Socket &listener, Server &server);
        void run();
        bool hasWeatherForDay(const int &day);
        CityWeather* getWeatherForDay(const int &day);
        virtual ~CityInfoReceiver();
    private:
        Socket &listener;
        Server &server;
        
        void split(strList &buffer, std::string &str);
};

#endif // CITYINFORECEIVER_H

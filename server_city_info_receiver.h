#ifndef CITYINFORECEIVER_H
#define CITYINFORECEIVER_H

#include <map>
#include <vector>
#include "common_socket.h"
#include "server_thread.h"
#include "server_city_weather.h"

class Server;

class CityInfoReceiver: public Thread{
    public:
        CityInfoReceiver(Socket &listener, Server &server);
        void run();
        bool hasWeatherForDay(const int &day);
        CityWeather* getWeatherForDay(const int &day);
        virtual ~CityInfoReceiver();
    private:
        std::string end_signal;
        char eof_info;
        Socket &listener;
        Server &server;
        
        void split(std::vector<std::string> &buffer, std::string &str);
};

#endif // CITYINFORECEIVER_H

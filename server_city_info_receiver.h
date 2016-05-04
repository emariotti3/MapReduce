#ifndef CITYINFORECEIVER_H
#define CITYINFORECEIVER_H

#include <map>
#include "common_socket.h"
#include "server_thread.h"
#include "server_city_weather.h"

class CityInfoReceiver: public Thread{
    public:
        CityInfoReceiver(Socket &listener);
        void run();
        bool hasWeatherForDay(int day);
        CityWeather* getWeatherForDay(int &day);
        virtual ~CityInfoReceiver();
    protected:
    private:
        std::string end_signal;
        std::map<int, CityWeather*> daily_info;
        Socket &listener;
};

#endif // CITYINFORECEIVER_H

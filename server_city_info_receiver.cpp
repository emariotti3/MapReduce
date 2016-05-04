#include "server_city_info_receiver.h"
#include <queue>
#include <string>
#include <iostream>
#include <exception>
#include <typeinfo>

#define MAX_SIZE_BYTES 1000

CityInfoReceiver::CityInfoReceiver(Socket &listener):
listener(listener){
    this->end_signal = "End\n";
}

void CityInfoReceiver::run(){
    char eof_info = '\n';
    std::string weather_info = "";
    std::queue<std::string> day_weather_info;
    while(weather_info.compare(weather_info.size() - this->end_signal.size(), std::string::npos, this->end_signal.c_str()) != 0){
        char received[MAX_SIZE_BYTES];
        this->listener.socket_receive(received, sizeof(char));
        this->listener.socket_receive(received, MAX_SIZE_BYTES, &eof_info, sizeof(char));
        weather_info += received;
    }
    std::string word = "";
    std::stringstream s(weather_info);

    while(s >> word){
        int temp, day= 0;
        std::string city_name = "";
        day = atoi(word.c_str());
        s >> city_name;
        s >> temp;
        CityWeather *city_weather = new CityWeather(city_name, temp);
        this->daily_info.insert(std::map<int, CityWeather*>::value_type(day, city_weather));
    }
}

bool CityInfoReceiver::hasWeatherForDay(const int &day){
    return (this->daily_info.count(day) > 0);
}

CityWeather* CityInfoReceiver::getWeatherForDay(const int &day){
    //if(this->hasWeatherForDay(day)){
        return this->daily_info[day];
    //}
    //throw exception!
}

CityInfoReceiver::~CityInfoReceiver(){}

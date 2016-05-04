#include "server_city_info_receiver.h"
#include <queue>

#define MAX_SIZE_BYTES 1000

CityInfoReceiver::CityInfoReceiver(Socket &listener):
listener(listener){
    this->end_signal = "End\n";
}

void CityInfoReceiver::run(){
    char eof_info = '\n';
    std::string weather_info = "";
    std::queue<std::string> day_weather_info;
    while(weather_info.compare(this->end_signal) != 0){
        weather_info = "";
        char letter[MAX_SIZE_BYTES];
        this->listener.socket_receive(letter, sizeof(char));
        //while(strncmp(letter, &eof_info, MAX_SIZE_BYTES) != 0){
            //weather_info.append(&letter);
            this->listener.socket_receive(letter, MAX_SIZE_BYTES, &eof_info, sizeof(char));
        //}
        day_weather_info.push(weather_info);
    }
    while(!day_weather_info.empty()){
        std::stringstream key_value(day_weather_info.front());
        day_weather_info.pop();
        int day, temp = 0;
        std::string city_name = "";
        key_value >> day;
        key_value >> city_name;
        key_value >> temp;
        CityWeather *city_weather = new CityWeather(city_name, temp);
        this->daily_info.insert(std::map<int, CityWeather*>::value_type(day, city_weather));
    }
}

bool CityInfoReceiver::hasWeatherForDay(int day){
    return (this->daily_info.count(day) > 0);
}

CityWeather* CityInfoReceiver::getWeatherForDay(int &day){
    //if(this->hasWeatherForDay(day)){
        return this->daily_info[day];
    //}
    //throw exception!
}

CityInfoReceiver::~CityInfoReceiver(){}

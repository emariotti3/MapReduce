#include "server_city_info_receiver.h"
#include <queue>
#include <string>
#include <iostream>
#include <exception>
#include <typeinfo>
#include <vector>
#include "server_city_weather.h"
#include "server_city_weather_factory.h"
#include "server.h"

#define MAX_BYTES 100
#define SIZE_RECEIVE sizeof(char)
#define END_SIGNAL "End\n"
#define END '\n'

typedef std::vector<std::string> strList;

CityInfoReceiver::CityInfoReceiver(Socket &listener, Server &server):
listener(listener),
server(server){}

void CityInfoReceiver::split(strList &buffer, std::string &str){
	char *saveptr;
	char *str_ptr  = (char*)str.c_str();
	char *found_token_ptr = strtok_r(str_ptr, "\n", &saveptr);
	while (found_token_ptr != NULL){
		std::string token = found_token_ptr;
		buffer.push_back(token);
		found_token_ptr = strtok_r(NULL, "\n", &saveptr);
	}
}

void CityInfoReceiver::run(){
    std::string weather_info = "";
    char received[MAX_BYTES];
	char end = END;
    while (weather_info.find(END_SIGNAL) == std::string::npos){
		std::fill(received,received + MAX_BYTES, '\0');
        this->listener.socket_receive(received, MAX_BYTES, &end, SIZE_RECEIVE);
        weather_info += received;
    }
    //Extract END_SIGNAL from weather_info string:
    std::string end_signal(END_SIGNAL);
    size_t subs_size = (weather_info.size() - end_signal.size());
    weather_info = weather_info.substr(0, subs_size);
	
	//Split weather_info string:
	strList day_weather_info;
	split(day_weather_info, weather_info);
	
    for (size_t i = 0; i < day_weather_info.size(); i++){			
		this->server.addInfoWeather(day_weather_info[i]);
	}
}

CityInfoReceiver::~CityInfoReceiver(){}

#include "server_city_info_receiver.h"
#include <queue>
#include <string>
#include <iostream>
#include <exception>
#include <typeinfo>
#include "server_city_weather.h"
#include "server_city_weather_factory.h"
#include "server.h"

#define MAX_SIZE_BYTES 100

CityInfoReceiver::CityInfoReceiver(Socket &listener, Server &server):
listener(listener),
server(server){
    this->end_signal = "End\n";
    this->eof_info = '\n';
}

void CityInfoReceiver::split(std::vector<std::string> &buffer, std::string &str){
	char *str_ptr  = (char*)str.c_str();
	char *found_token_ptr = strtok(str_ptr, "\n");
	while (found_token_ptr != NULL){
		std::string token = found_token_ptr;
		buffer.push_back(token);
		found_token_ptr = strtok (NULL, "\n");
	}
}

void CityInfoReceiver::run(){
    std::string weather_info = "";
    while (weather_info.find(this->end_signal) == std::string::npos){
        char received[MAX_SIZE_BYTES] = {};
        this->listener.socket_receive(received, MAX_SIZE_BYTES, &this->eof_info, sizeof(char));
        weather_info += received;
    }
    //Extract end_signal from weather_info string:
    size_t subs_size = (weather_info.size() - (this->end_signal).size());
    weather_info = weather_info.substr(0, subs_size);
	
	//Split weather_info string:
	std::vector<std::string> day_weather_info;
	split(day_weather_info, weather_info);
	
    for(size_t i = 0; i < day_weather_info.size(); i++){			
		this->server.addInfoWeather(day_weather_info[i]);
	}
	return;
}

CityInfoReceiver::~CityInfoReceiver(){}

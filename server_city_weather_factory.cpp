#include "server_city_weather_factory.h"
#include "server_city_weather.h"
#include <stdlib.h>
#include <sstream>
#include <string>

CityWeather* CityWeatherFactory::newCityWeather(std::string &pair_key_value){
	std::stringstream s(pair_key_value);
	int temp, day = 0;
    std::string city_name = "";
    s >> day;
    s >> city_name;
    s >> temp;
    CityWeather *city_weather = new CityWeather(day, city_name, temp);
    this->created.push_back(city_weather);
    return city_weather;
}

CityWeatherFactory::~CityWeatherFactory(){
	for (size_t i = 0; i < this->created.size(); i++){
		delete this->created[i];
	}
}


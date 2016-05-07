#include "server_city_weather.h"

CityWeather::CityWeather(int &day, std::string &city, int &temp):
day(day),
city_name(city),
temperature(temp)
{}

int& CityWeather::getDay(){
	return this->day;
}

CityWeather::~CityWeather(){}

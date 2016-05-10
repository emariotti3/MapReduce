#include "server_city_weather.h"
#include <string>

CityWeather::CityWeather(int day, std::string city, int temp):
day(day),
city_name(city),
temperature(temp)
{}

const int& CityWeather::getDay() const{
	return this->day;
}

const int& CityWeather::getTemperature() const{
	return this->temperature;
}

const std::string& CityWeather::getCityName() const{
	return this->city_name;
}

CityWeather::~CityWeather(){}

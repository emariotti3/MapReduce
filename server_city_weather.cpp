#include "server_city_weather.h"

CityWeather::CityWeather(int day, std::string city, int temp):
day(day),
city_name(city),
temperature(temp)
{}

bool CityWeather::operator<(CityWeather *cw_2){
	if (this->temperature == cw_2->getTemperature()){
		return this->city_name.compare(cw_2->getCityName());
	}
	return (this->temperature < cw_2->getTemperature());
}

bool CityWeather::operator==(CityWeather *cw_2){
	return (this->temperature == cw_2->temperature);
}

int& CityWeather::getDay(){
	return this->day;
}

int& CityWeather::getTemperature(){
	return this->temperature;
}

std::string& CityWeather::getCityName(){
	return this->city_name;
}

CityWeather::~CityWeather(){}

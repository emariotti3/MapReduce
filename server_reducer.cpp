#include "server_reducer.h"
#include "server_city_weather.h"
#include <algorithm>

typedef std::vector<CityWeather*> CityWeatherList;
typedef std::vector<CityWeather*>::reverse_iterator CityWeatherListIt;

std::stringstream& Reducer::getResult(){
	return this->result;
}

void Reducer::add(CityWeather *cw){
	this->cities.push_back(cw);
}

void Reducer::run(){
	//Orders cities in ascending temperature order:
	std::sort (this->cities.begin(), this->cities.end());
	CityWeatherListIt it_begin = this->cities.rbegin();
	CityWeatherListIt it_end = this->cities.rend();
	CityWeather *hottest_city = *it_begin;
	std::string names = "";
	while ((it_begin != it_end) && ((*hottest_city) == (*it_begin))){
		names += (*it_begin)->getCityName() + "/";
		it_begin++;
	}
	this->result << hottest_city->getDay();
	this->result << ": " << names.substr(0, names.size()-1);
	this->result << " (" << hottest_city->getTemperature();
	this->result << ")";
}

Reducer::~Reducer(){}

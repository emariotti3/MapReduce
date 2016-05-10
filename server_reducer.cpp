#include "server_reducer.h"
#include "server_city_weather.h"
#include <algorithm>
#include <string>
#include <vector>

typedef std::vector<CityWeather*> CityWeatherList;
typedef std::vector<CityWeather*>::reverse_iterator CityWeatherListIt;

std::stringstream& Reducer::getResult(){
	return this->result;
}

void Reducer::add(CityWeather *cw){
	this->cities.push_back(cw);
}

bool cmp(const CityWeather* cw_1, const CityWeather* cw_2){
	if (cw_1->getTemperature() == cw_2->getTemperature()){
		return cw_1->getCityName() < cw_2->getCityName();
	}
	return (cw_1->getTemperature() < cw_2->getTemperature());
}

bool operator == (const CityWeather& cw_1, const CityWeather& cw_2){
	return (cw_1.getTemperature() == cw_2.getTemperature());
}

void Reducer::sort_cities(){
	std::sort(this->cities.begin(), this->cities.end(), &cmp);
}

void Reducer::run(){
	//Orders cities in ascending temperature order:
	this->sort_cities();
	CityWeatherListIt it_begin = this->cities.rbegin();
	CityWeatherListIt it_end = this->cities.rend();
	CityWeather *hottest_city = *it_begin;
	std::string names = "";
	while ( (it_begin != it_end) && ((*hottest_city) == *(*it_begin)) ){
		names = (*it_begin)->getCityName() + "/" + names;
		it_begin++;
	}
	this->result << hottest_city->getDay();
	this->result << ": " << names.substr(0, names.size()-1);
	this->result << " (" << hottest_city->getTemperature();
	this->result << ")";
}

Reducer::~Reducer(){}

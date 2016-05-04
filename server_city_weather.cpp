#include "server_city_weather.h"

CityWeather::CityWeather(std::string &city, int &temp):
city_name(city),
temperature(temp)
{}

CityWeather::~CityWeather(){}

#ifndef CITYWEATHERFACTORY_H
#define CITYWEATHERFACTORY_H

#include "server_city_weather.h"
#include <vector>
#include <string>

typedef std::vector<CityWeather*> CityWeatherList;

class CityWeatherFactory{
    public:
        CityWeather *newCityWeather(std::string &pair_key_value);
        ~CityWeatherFactory();
    private:
		CityWeatherList created;
};

#endif // CITYWEATHERFACTORY_H


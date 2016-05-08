#ifndef CITYWEATHERFACTORY_H
#define CITYWEATHERFACTORY_H

#include "server_city_weather.h"
#include <vector>
#include <string>

class CityWeatherFactory{
    public:
        CityWeather *newCityWeather(std::string pair_key_value);
        ~CityWeatherFactory();
    private:
		std::vector<CityWeather*> created;
};

#endif // CITYWEATHERFACTORY_H


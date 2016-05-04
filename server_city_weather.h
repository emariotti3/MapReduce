#ifndef CITYWEATHER_H
#define CITYWEATHER_H

#include <string>

class CityWeather{
    public:
        CityWeather(std::string &city, int &temp);
        virtual ~CityWeather();
    protected:
    private:
        std::string &city_name;
        int &temperature;
};

#endif // CITYWEATHER_H

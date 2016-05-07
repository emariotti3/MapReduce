#ifndef CITYWEATHER_H
#define CITYWEATHER_H

#include <string>

class CityWeather{
    public:
        CityWeather(int &day, std::string &city, int &temp);
        int& getDay();
        virtual ~CityWeather();
    protected:
    private:
		int &day;
        std::string &city_name;
        int &temperature;
};

#endif // CITYWEATHER_H

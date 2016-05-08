#ifndef CITYWEATHER_H
#define CITYWEATHER_H

#include <string>

class CityWeather{
    public:
        CityWeather(int day, std::string city, int temp);
		//bool operator < (const CityWeather &cw_2) const;
        //bool operator == (const CityWeather *cw_2) const;
        const int& getTemperature() const;
        const int& getDay() const;
        const std::string& getCityName() const;
        virtual ~CityWeather();
    protected:
    private:
		int day;
        std::string city_name;
        int temperature;
};

bool operator < (const CityWeather &,const CityWeather &);

#endif // CITYWEATHER_H

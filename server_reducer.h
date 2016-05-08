#ifndef REDUCER_H
#define REDUCER_H

#include "server_reducer.h"
#include "server_thread.h"
#include "server_city_weather.h"
#include <vector>
#include <sstream>

typedef std::vector<CityWeather*> CityWeatherList;

class Reducer: public Thread{
    public:
        std::stringstream& getResult();
        void add(CityWeather *cw);
        void sort_cities();
        void run();
        virtual ~Reducer();
    protected:
    private:
		CityWeatherList cities;
		std::stringstream result;
};



#endif // REDUCER_H

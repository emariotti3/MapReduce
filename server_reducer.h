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
        //Reducer(CityWeatherList &cities);
        std::stringstream& getResult();
        void add(CityWeather *cw);
        void run();
        virtual ~Reducer();
    protected:
    private:
		CityWeatherList cities;
		std::stringstream result;
};

#endif // REDUCER_H

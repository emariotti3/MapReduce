#ifndef REDUCER_H
#define REDUCER_H

#include "server_city_weather.h"
#include "server_thread.h"

class Reducer: public Thread{
    public:
        Reducer(int &id);
        void add(CityWeather *cityWeather);
        void run();
        virtual ~Reducer();
    protected:
    private:
        int &id;
};

#endif // REDUCER_H

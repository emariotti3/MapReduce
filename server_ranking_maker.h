#ifndef RANKINGMAKER_H
#define RANKINGMAKER_H

#include "server_city_weather.h"
#include "server_reducer.h"
#include <map>
#include <vector>

typedef std::multimap<int, CityWeather*> WeatherMap;
typedef std::map<int, Reducer*> ReducerMap;

class RankingMaker{
	public:
		RankingMaker(WeatherMap *weather_info);
		void printOrderByTempertaure();
		~RankingMaker();
	private:
		ReducerMap reducers;
};

#endif // RANKINGMAKER_H

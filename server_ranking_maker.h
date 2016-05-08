#ifndef RANKINGMAKER_H
#define RANKINGMAKER_H

#include "server_city_weather.h"
#include <map>
#include <vector>

class RankingMaker{
	public:
		void printOrderByTempertaure(std::multimap<int, CityWeather*> &weather_info);
		~RankingMaker();
	private:
};

#endif // RANKINGMAKER_H

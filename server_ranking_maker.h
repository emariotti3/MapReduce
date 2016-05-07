#ifndef RANKINGMAKER_H
#define RANKINGMAKER_H

#include "server_city_weather.h"
#include <map>
#include <vector>

class RankingMaker{
	public:
		void printOrderByTempertaure(std::map<int, std::vector<CityWeather*>* > &weather_info);
		~RankingMaker();
	private:
};

#endif // RANKINGMAKER_H

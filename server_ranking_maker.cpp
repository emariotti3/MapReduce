#include "server_ranking_maker.h"
#include "server_reducer.h"
#include <vector>
#include <iostream>

typedef std::map<int, std::vector<CityWeather*> > WeatherMap;
typedef std::map<int, std::vector<CityWeather*> >::iterator WeatherMapIt;

void RankingMaker::printOrderByTempertaure(WeatherMap &weather_info){	
	std::vector<Reducer*> reducers;
	WeatherMapIt it_begin = weather_info.begin();
	WeatherMapIt it_end = weather_info.end();
	for (WeatherMapIt it = it_begin; it != it_end; it++){
		Reducer *reducer = new Reducer(it->second);
		reducers.push_back(reducer);
	}
	for (size_t i = 0; i < reducers.size(); i++){
		reducers[i]->start();
	}
	for (size_t i = 0; i < reducers.size(); i++){
		reducers[i]->join();
		std::cout << reducers[i]->getResult().str() << '\n';
	}
	//delete[] &reducers;
}

RankingMaker::~RankingMaker(){}

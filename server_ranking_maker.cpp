#include "server_ranking_maker.h"
#include "server_reducer.h"
#include <vector>
#include <iostream>

typedef std::vector<Reducer*>::iterator ReducerListIt;
typedef std::vector<CityWeather*> CityWeatherList;
typedef std::map<int, std::vector<CityWeather*> *> WeatherMap;
typedef std::map<int, std::vector<CityWeather*> *>::iterator WeatherMapIt;

void RankingMaker::printOrderByTempertaure(WeatherMap &weather_info){	
	std::vector<Reducer*> reducers;
	WeatherMapIt it_begin = weather_info.begin();
	WeatherMapIt it_end = weather_info.end();
	for (; it_begin != it_end; it_begin++){
		Reducer reducer(*it_begin->second);
		reducers.push_back(&reducer);
		reducer.start();
	}
	ReducerListIt it_begin_red = reducers.begin();
	ReducerListIt it_end_red = reducers.end();
	for (; it_begin_red != it_end_red; it_begin_red++){
		(*it_begin_red)->join();
		std::cout << it_begin_red->getResult().str() << '\n';
	}
	//delete[] &reducers;
}

RankingMaker::~RankingMaker(){}

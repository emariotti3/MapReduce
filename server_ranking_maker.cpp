#include "server_ranking_maker.h"
#include "server_reducer.h"
#include <vector>
#include <iostream>
#include <map>

typedef std::multimap<int, CityWeather*> WeatherMap;
typedef std::multimap<int, CityWeather*>::iterator WeatherMapIt;
typedef std::map<int, Reducer*> ReducerMap;
typedef std::map<int, Reducer*>::iterator ReducerMapIt;

void RankingMaker::printOrderByTempertaure(WeatherMap &weather_info){
	ReducerMap reducers;
	WeatherMapIt it = weather_info.begin();
	WeatherMapIt it_end = weather_info.end();
	for (; it != it_end; it++){
		Reducer *reducer;
		if (reducers.find(it->first)!= reducers.end()){
			reducer = reducers.find(it->first)->second;
		}
		else{
			reducer = new Reducer();
			reducers.insert(ReducerMap::value_type(it->first, reducer));
		}
		reducer->add(it->second);
	}
	ReducerMapIt it_begin_red = reducers.begin();
	ReducerMapIt it_end_red = reducers.end();
	for (; it_begin_red != it_end_red; ++it_begin_red){
		it_begin_red->second->start();
	}	
	it_begin_red = reducers.begin();
	for (; it_begin_red != it_end_red; ++it_begin_red){
		it_begin_red->second->join();
		std::cout << it_begin_red->second->getResult().str() << '\n';
	}	

	//delete[] &reducers;
}

RankingMaker::~RankingMaker(){}

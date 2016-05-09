#include "server_ranking_maker.h"
#include <vector>
#include <iostream>
#include <map>

#define MAX_THREADS 5

typedef std::multimap<int, CityWeather*> WeatherMap;
typedef std::multimap<int, CityWeather*>::iterator WeatherMapIt;
typedef std::map<int, Reducer*> ReducerMap;
typedef std::map<int, Reducer*>::iterator ReducerMapIt;

RankingMaker::RankingMaker(WeatherMap *weather_info){
	WeatherMapIt it = weather_info->begin();
	WeatherMapIt it_end = weather_info->end();
	for (; it != it_end; ++it){
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
}

void RankingMaker::printOrderByTempertaure(){
	size_t delta_thread = MAX_THREADS > reducers.size() ? reducers.size() : MAX_THREADS;
	ReducerMapIt it_begin_red = reducers.begin();
	ReducerMapIt it_end_red = reducers.end();
	ReducerMapIt it_aux_red = reducers.begin();
	std::advance(it_aux_red, delta_thread);	
	while (it_begin_red != it_end_red){
		size_t move = 0;
		for (; it_begin_red != it_aux_red; ++it_begin_red){
			it_begin_red->second->start();
			move++;
		}	
		std::advance(it_begin_red, -move);	
		for (; it_begin_red != it_aux_red; ++it_begin_red){
			it_begin_red->second->join();
			std::cout << it_begin_red->second->getResult().str() << '\n';
		}
		size_t dst_end = std::distance(it_begin_red, it_end_red);
		delta_thread = dst_end < MAX_THREADS ? dst_end : MAX_THREADS;
		std::advance(it_aux_red, delta_thread);	
	}
}

RankingMaker::~RankingMaker(){
	ReducerMapIt it = reducers.begin();
	ReducerMapIt it_end = reducers.end();
	for (; it != it_end; ++it){
		delete &(*it->second);
	}
}

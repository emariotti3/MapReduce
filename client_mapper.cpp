#include "client_mapper.h"
#include <sstream>
#include <iostream>
#include <queue>
#include <string>

Mapper::Mapper(){
    this->pos_key = 2;
}

void Mapper::remap(std::istream &input, std::queue<std::string> &new_pairs){
    int i;
    std::string line = "";
    std::string word = "";
    std::getline(input, line);
    while (!input.eof()){
        std::string new_key = "";
        std::string new_value = "";
        std::stringstream ss(line);
        i = 0;
        while (ss >> word){
            if (this->pos_key == i){
                new_key = word;
            }else{
                new_value = new_value + " " + word;
            }
            i++;
        }
        std::string new_pair = new_key + new_value + "\n";
        new_pairs.push(new_pair);
        std::getline(input, line);
    }
}

Mapper::~Mapper(){}

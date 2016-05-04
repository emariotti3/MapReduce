#ifndef MAPPER_H
#define MAPPER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <queue>

class Mapper{
    public:
        Mapper();
        void remap(std::istream &input, std::queue<std::string> &new_pairs);
        virtual ~Mapper();
    protected:
    private:
        int pos_key;
        bool next_line(std::istream &input, std::string &line);
};

#endif // MAPPER_H

#ifndef ASTAR_H
#define ASTAR_H


#include "base.hpp"


std::vector<int> A_star(
    Map *map, 
    int nodeIdFrom, int nodeIdTo, 
    OC_Container& OC,
    size_t adj_buf_prealloc = 100
);


#endif

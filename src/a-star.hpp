#ifndef ASTAR_H
#define ASTAR_H


#include "matrixmap.hpp"


class Search {
    public :
        Search() = delete;
        Search(BinaryMatrixMap *map);

        void setTargets(int nodeIdFrom, int nodeIdTo);
        void setTargets(const point& from, const point& to);
        void run();
        std::vector<int>   getPath();
        // std::vector<point> getPath();

    private :
        BinaryMatrixMap  *map;
        bool set_targets;
        int nodeIdFrom, nodeIdTo;
        std::vector<int> path;

};


std::vector<int> A_star(
    Map *map, 
    int nodeIdFrom, int nodeIdTo, 
    OC_Container& OC
);


#endif

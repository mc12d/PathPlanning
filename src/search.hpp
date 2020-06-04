#ifndef SEARCH_H
#define SEARCH_H


#include "a-star.hpp"
#include "matrixmap.hpp"
#include "container.hpp"


class AStarSearch {
public:
    AStarSearch(const char* map_filename);
    AStarSearch(std::vector<bool> data, size_t witdh, size_t height);
    
    void setTargets(const point& from, const point& to);
    void setHeuristic(std::function<double(const point&, const point&)> hr);
    std::vector<int> run();
    std::vector<point> getPath() const;
    void exportPathBMP(const char* filename) const;
    
    point idToPoint(int id) const;
    int   pointToId(const point& point) const;

private:
    int from , to;
    BinaryMatrixMap map;
    std::vector<int> path;

};


#endif
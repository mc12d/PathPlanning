#ifndef BBASE_H
#define BBASE_H


#include <vector>
#include <iterator>
#include <fstream>
#include <stdexcept>
#include <functional>
#include <cmath>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>


typedef struct {
    size_t x, y;
} point;


class Map {
public :
    virtual double getCost(int nodeFrom, int nodeTo)               const = 0;
    virtual double heurDist(int nodeFrom, int nodeTo)              const = 0;
    virtual void   getAdj (int nodeId, int *adj_buf, int *adj_deg) const = 0;
    virtual ~Map() {};
};


class OC_Container {
public :
    virtual void open(int nodeId, int parentId, double gval, double fval) = 0;
    virtual void close(int nodeId)                                        = 0;
    virtual int top()                                                     = 0;
    virtual void pop()                                                    = 0;
    virtual double getGValue(int nodeId) const                            = 0;
    virtual bool isClosed(int nodeId) const                               = 0;
    virtual bool isOpened(int nodeId) const                               = 0;
    virtual bool empty() const                                            = 0;
    virtual int  parent(int nodeId) const                                 = 0;
    virtual ~OC_Container() {};

};


#endif
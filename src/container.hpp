#ifndef CONTAINER_HPP
#define CONTAINER_HPP


#include "base.hpp"


struct node {
    int id;
    double fval;
};


struct node_info {
    int parent;
    double gval;
};


bool operator > (const node& a, const node& b);


class OC_STL : public OC_Container {
public :
    OC_STL();
    OC_STL(size_t prealloc);
    void   open(int nodeId, int parentId, double gval, double fval);
    void   close(int nodeId);
    void   pop();
    int    top();
    double getGValue(int nodeId) const;
    bool   isClosed(int nodeId) const;
    bool   isOpened(int nodeId) const;
    bool   empty() const;
    int    parent(int nodeId) const;

private :
    std::priority_queue<node, std::vector<node>, std::greater<node>> prq;
    std::unordered_map<int, node_info> node_info_map;
    std::unordered_set<int> opened, closed;

};


#endif

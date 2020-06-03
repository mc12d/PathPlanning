#include "container.hpp"

#include <functional>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>


const size_t DEFAULT_PREALLOC = 4096;


OC_STL::OC_STL()
: opened(DEFAULT_PREALLOC)
, closed(DEFAULT_PREALLOC)    
{}


void OC_STL::open(int nodeId, int parentId, double gval, double fval) {
    prq.push({nodeId, fval});
    opened.insert(nodeId);
    node_info_map[nodeId] = {parentId, gval};
}


void OC_STL::close(int nodeId) {
    // node_info_map.erase(nodeId);
    opened.erase(nodeId);
    closed.insert(nodeId);
}


double OC_STL::getGValue(int nodeId) const {
    if (!isOpened(nodeId))
        throw std::invalid_argument("[OC_STL::getGValue] nodeId does not exist");
    return node_info_map.at(nodeId).gval;
}


void OC_STL::pop() {
    if (opened.empty())
        throw std::runtime_error("[OC_STL::pop] Pop from empty container");

    for (int id = prq.top().id; closed.find(id) != closed.end(); id = prq.top().id)
        prq.pop();

    int id = prq.top().id;
    prq.pop();
    // node_info_map.erase(id);
    opened.erase(id);
}


int OC_STL::top() {
    if (opened.empty())
        throw std::runtime_error("[OC_STL::top] Top from empty container");
    
    for (int id = prq.top().id; closed.find(id) != closed.end(); id = prq.top().id)
        prq.pop();
    
    return prq.top().id;
}


bool OC_STL::isClosed(int nodeId) const {
    return closed.find(nodeId) != closed.end();
}


bool OC_STL::empty() const {
    return opened.empty();
}


bool OC_STL::isOpened(int nodeId) const {
    return opened.find(nodeId) != opened.end();
}


int OC_STL::parent(int nodeId) const {
    // if (!isOpened(nodeId))
    //    throw std::invalid_argument("[OC_STL::parent] nodeId does not exist");
    return node_info_map.at(nodeId).parent;
}


bool operator > (const node& a, const node& b) {
        return a.fval > b.fval;
}

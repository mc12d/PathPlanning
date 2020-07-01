#include "a-star.hpp"


std::vector<int> construct_path(OC_Container& oc, Map& map, int nodeFrom, int nodeTo);


std::vector<int> A_star(
    Map& map, 
    int nodeFrom, int nodeTo, 
    OC_Container& OC,
    size_t adj_buf_prealloc
) {
    map.heurDist(nodeFrom, nodeTo);
    OC.open(nodeFrom, nodeFrom, 0, map.heurDist(nodeFrom, nodeTo));

    int    cur_id, adj_cur;
    int    deg, adj_buf[adj_buf_prealloc];
    double cur_gval, adj_gval;

    while(!OC.empty()) {
        cur_id   = OC.top();
        cur_gval = OC.getGValue(cur_id);

        if (cur_id == nodeTo) {
            return construct_path(OC, map, nodeFrom, nodeTo);
        }
        
        OC.pop();
        OC.close(cur_id);

        map.getAdj(cur_id, adj_buf, &deg);
        for (int i = 0; i < deg; i++) {
            adj_gval = cur_gval + map.getCost(cur_id, adj_buf[i]);
            if (
                (!OC.isClosed(adj_buf[i]) && !OC.isOpened(adj_buf[i])) ||
                (OC.getGValue(adj_buf[i]) > adj_gval)
            ) {
                OC.open(adj_buf[i], cur_id, adj_gval, adj_gval + map.heurDist(adj_buf[i], nodeTo));
            }
        }
    }
    return {};
}


std::vector<int> construct_path(OC_Container& oc, Map& map, int nodeFrom, int nodeTo) {
    std::vector<int> path;
            for (int id = nodeTo; id != nodeFrom; id = oc.parent(id)) {
                path.push_back(id);
            }   
            path.push_back(nodeFrom);
            std::reverse(path.begin(), path.end());
            return path;
}
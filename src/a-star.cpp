#include "a-star.hpp"


std::vector<int> A_star(
    Map *map, 
    int nodeIdFrom, int nodeIdTo, 
    OC_Container& OC
) {
    OC.open(nodeIdFrom, nodeIdFrom, 0, map->heurDist(nodeIdFrom, nodeIdTo));

    int    cur_id, adj_cur;
    int    deg, adj_buf[MAX_BMAP_ADJ];
    double cur_gval, adj_gval;

    while(!OC.empty()) {
        cur_id = OC.top();
        cur_gval = OC.getGValue(cur_id);

        if (cur_id == nodeIdTo) {
            std::vector<int> path;
            for (int id = nodeIdTo; id != nodeIdFrom; id = OC.parent(id)) {
                path.push_back(id);
            }   
            path.push_back(nodeIdFrom);
            std::reverse(path.begin(), path.end());
            return path;
        }
        
        OC.pop();
        OC.close(cur_id);
        map->getAdj(cur_id, adj_buf, &deg);

        for (int i = 0; i < deg; i++) {
            if(!OC.isClosed(adj_buf[i])) {
                if (
                    !OC.isOpened(adj_buf[i]) || 
                    (
                        OC.isOpened(adj_buf[i]) && 
                        cur_gval + map->getCost(cur_id, adj_buf[i]) < OC.getGValue(adj_buf[i])    
                    )
                ) {
                    adj_gval = cur_gval + map->getCost(cur_id, adj_buf[i]);
                    OC.open(adj_buf[i], cur_id, adj_gval, adj_gval + map->heurDist(adj_buf[i], nodeIdTo));
                }
                
            }
        }
    }
    return {};
}

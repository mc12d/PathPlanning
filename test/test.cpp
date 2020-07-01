#include "../src/matrixmap.hpp"
#include "../src/container.hpp"
#include "../src/a-star.hpp"
#include "../src/search.hpp"
#include "catch.hpp"
#include <fstream>


TEST_CASE("MatrixMap") {
    int w = 5, h = 4;
    std::vector<bool> mtx1 = {
        0, 0, 0, 0, 0, 
        0, 1, 1, 0, 0, 
        0, 0, 1, 1, 0,
        0, 0, 0, 1, 0
    };

    auto map = BinaryMatrixMap(mtx1, w, h);

    SECTION("getAdj") {
        int deg, *adj = new int[8];
        map.getAdj(0, adj, &deg);

        REQUIRE(deg == 2);
        REQUIRE(adj[0] == 1);
        REQUIRE(adj[1] == 5);
    }

    SECTION("heurDist") {
        map.setHeuristic(Heuristic::Euclidian);
        double dist = map.heurDist(0, 19);

        REQUIRE(dist == 5.0);
    }
}


TEST_CASE("OC_STL") {
    auto oc = OC_STL();
    oc.open(0, 0, 0, 5);
    oc.open(1, 0, 1, 4.56);
    oc.open(5, 0, 1, 4.56);
    
    REQUIRE(oc.isOpened(0));
    REQUIRE(oc.isOpened(5));
    REQUIRE(oc.isOpened(1));

    oc.close(1);
    try {
        oc.close(1);
    } catch(std::invalid_argument e) {
        INFO(e.what());
    }
    REQUIRE(oc.isClosed(1));
    REQUIRE_FALSE(oc.isOpened(1));
    
    auto nodeid = oc.top();
    REQUIRE(nodeid == 5);
    REQUIRE(oc.getGValue(nodeid) == 1);

    oc.pop();
    oc.pop();
    REQUIRE(oc.empty());
}


TEST_CASE("A_star") {
    int w = 7, h = 4;
    std::vector<bool> mtx1 = {
        0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 1, 1,
        0, 0, 1, 1, 0, 1, 0,
        0, 0, 0, 1, 0, 1, 1
    };

    auto map = BinaryMatrixMap(mtx1, w, h);
    auto oc  = OC_STL();

    map.setHeuristic(Heuristic::Euclidian);

    std::vector<int> res;

    std::vector<int> gr_truth_0_11 = {0, 7, 15};
    std::vector<int> gr_truth_4_23 = {4, 10, 2, 1, 7, 15, 23};
    std::vector<int> gr_truth_4_20 = {};

    res = A_star(map, 0, 15, oc);
    REQUIRE(res == gr_truth_0_11);

    oc = OC_STL();
    res = A_star(map, 4, 23, oc);
    REQUIRE(res == gr_truth_4_23);

    oc = OC_STL();
    res = A_star(map, 4, 20, oc);
    REQUIRE(res == gr_truth_4_20);

    oc = OC_STL();
    res = A_star(map, 0, 0, oc);
    REQUIRE(res == std::vector<int>({0}));
    
}


TEST_CASE("A_star_city") {
    auto map = BinaryMatrixMap("../test/Shanghai_2_1024.map");

    REQUIRE(map.getSize().x == 1024);
    REQUIRE(map.getSize().y == 1024);

    map.exportBMP("map.bmp");
    map.setHeuristic(Heuristic::Manhattan);

    int from = 0, to = 1024 * 1024 - 1;
    REQUIRE(!map.getValue(from));
    REQUIRE(!map.getValue(to));

    auto oc = OC_STL();
    std::vector<int> p = A_star(map, to, from, oc);
    WARN("A_star_city : Found path length : " + std::to_string(p.size()));
}


TEST_CASE("Search") {
    auto s = AStarSearch("../test/Shanghai_2_1024.map");

    REQUIRE(s.pointToId({2, 2}) == 1024 * 2 + 2);
    REQUIRE(s.idToPoint(1025).x == 1);
    REQUIRE(s.idToPoint(1025).y == 1);
    REQUIRE(s.idToPoint(1024 * 1024 - 1) == point({1023, 1023}));

    s.setTargets({0, 0}, {1023, 1023});
    s.setHeuristic(Heuristic::Euclidian);
    auto path = s.run();
    REQUIRE(path.size() == 1150);

    s.exportPathBMP("path.bmp");
}


class customGraph : public Map {
    virtual double getCost(int nodeFrom, int nodeTo) const {
        if (nodeFrom > nodeTo) std::swap(nodeFrom, nodeTo);
        if (nodeFrom == 0 && nodeTo == 1) return 5;
        if (nodeFrom == 0 && nodeTo == 4) return 2;
        if (nodeFrom == 0 && nodeTo == 2) return 3;
        if (nodeFrom == 1 && nodeTo == 4) return 2;
        if (nodeFrom == 1 && nodeTo == 3) return 2;
        if (nodeFrom == 2 && nodeTo == 3) return 5;

        throw std::invalid_argument("getCost : edge does not exist");
    }
    virtual double heurDist(int nodeFrom, int nodeTo) const {
        if (nodeFrom == 0 && nodeTo == 3) return 7;
        if (nodeFrom == 1 && nodeTo == 3) return 0;
        if (nodeFrom == 2 && nodeTo == 3) return 5;
        if (nodeFrom == 3 && nodeTo == 3) return 0;
        if (nodeFrom == 4 && nodeTo == 3) return 4;
        throw std::invalid_argument("heurDist : No such node : " + 
            std::to_string(nodeFrom) + " " + std::to_string(nodeTo));
    }
    virtual void   getAdj (int nodeId, int *adj_buf, int *adj_deg) const {
        switch(nodeId) {
            case 0 : 
                adj_buf[0] = 1, adj_buf[1] = 4, adj_buf[2] = 2;
                *adj_deg = 3;
                break;
            case 1 :
                adj_buf[0] = 0, adj_buf[1] = 3, adj_buf[2] = 4;
                *adj_deg = 3;
                break;
            case 2 :
                adj_buf[0] = 0, adj_buf[1] = 3;
                *adj_deg = 2;
                break;
            case 3 :
                adj_buf[0] = 2, adj_buf[1] = 1;
                *adj_deg = 2;
                break;
            case 4 :
                adj_buf[0] = 0, adj_buf[1] = 1;
                *adj_deg = 2;
                break;
            default :
                throw std::invalid_argument("getAdg : No such node.");
        }
    }
};


TEST_CASE("custom_graph") {
    customGraph gr;
    OC_STL oc;

    auto res = A_star(gr, 0, 3, oc);
    std::vector<int> res_gr = {0, 4, 1, 3};
    REQUIRE(res == res_gr);
}

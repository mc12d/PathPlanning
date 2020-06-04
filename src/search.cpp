#include "search.hpp"


AStarSearch::AStarSearch(const char* map_filename)
: map(map_filename)
{}


AStarSearch::AStarSearch(std::vector<bool> data, size_t width, size_t height)
: map(data, width, height)
{}


void AStarSearch::setTargets(const point& from, const point& to) {
    this->from = map.getSize().x * from.y + from.x;
    this->to   = map.getSize().x * to.y   + to.x;
}


void AStarSearch::setHeuristic(std::function<double(const point&, const point&)> hr) {
    map.setHeuristic(hr);
}


std::vector<int> AStarSearch::run() {
    OC_STL OC;
    path = A_star(map, from, to, OC);
    return path;
}


std::vector<point> AStarSearch::getPath() const {
    std::vector<point> res;
    for (auto v : path)
        res.push_back({
            v % map.getSize().x,
            v / map.getSize().x
        });
    return res;
}


void AStarSearch::exportPathBMP(const char* filename) const {
    unsigned char* map_array_raw = map.exportImageArray();
    int w = map.getSize().x,
        h = map.getSize().y;
    auto map_array = (unsigned char (*)[w][COLOR_BYTES]) map_array_raw;

    for (int i = 0, x, y; i < path.size(); i++) {
        x = path[i] % w, y = path[i] / w;
        map_array[h - 1 - y][x][0] = 0;
        map_array[h - 1 - y][x][1] = 0;
        map_array[h - 1 - y][x][2] = 255;
    }

    generateBitmapImage(map_array_raw, map.getSize().y, map.getSize().x, filename);
}


point AStarSearch::idToPoint(int id) const {
    return {id % map.getSize().x, id / map.getSize().x};
}


int AStarSearch::pointToId(const point& point) const {
    return point.y * map.getSize().x + point.x;
}

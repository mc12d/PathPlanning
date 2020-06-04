#ifndef MATRIXMAP_H
#define MATRIXMAP_H


#include "base.hpp"


const int MAX_BMAP_ADJ = 8;
const int COLOR_BYTES  = 3;


namespace Heuristic {
    double Euclidian(const point& a, const point& b);
    double Manhattan(const point& a, const point& b);
    double Dijkstra(const point& a, const point& b);
}


class BinaryMatrixMap : public Map {
public :
    BinaryMatrixMap() = delete;
    BinaryMatrixMap(std::vector<bool> data, size_t width, size_t height);
    BinaryMatrixMap(const char* map_file_name);

    double         getCost(int nodeFrom, int nodeTo)               const;
    void           getAdj (int nodeId, int *adj_buf, int *adj_deg) const;
    void           exportBMP(const char *file_name)                const;
    unsigned char* exportImageArray()                              const;
    point          getSize()                                       const;
    double         heurDist(int nodeId_1, int nodeId_2)            const;
    bool           getValue(int nodeId)                            const;

    void           setHeuristic(std::function<double(const point&, const point&)>);

private :
    size_t W, H;
    std::vector<bool> data;
    std::function<double(const point&, const point&)> hr;

};


void generateBitmapImage(unsigned char *image, int height, int width, const char* imageFileName);


#endif

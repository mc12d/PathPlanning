#include "matrixmap.hpp"


double BinaryMatrixMap::getCost(int nodeFrom, int nodeTo) const {
    // check adjacency?
    return 1;
}


void BinaryMatrixMap::getAdj(int nodeId, int *adj_buf, int *adj_deg) const {
    if (nodeId < 0 || nodeId >= data.size())
        throw std::invalid_argument("getAdj : node id is out of range");
    if (adj_buf == NULL)
        throw std::invalid_argument("getAdj : adj_buf must be preallocated");

    // assuming there is no paths from the obstacle cell
    if (data[nodeId])
        return;

    int topL = nodeId - W - 1,
        topC = nodeId - W,
        topR = nodeId - W + 1,
        midL = nodeId - 1,
        midR = nodeId + 1,
        botL = nodeId + W - 1,
        botC = nodeId + W,
        botR = nodeId + W + 1;
    
    // checking adjacency requirements
    *adj_deg = 0;
    if (topL >= 0 && nodeId % W != 0)                if (!data[topL]) {adj_buf[*adj_deg] = topL; (*adj_deg)++;}
    if (topC >= 0)                                   if (!data[topC]) {adj_buf[*adj_deg] = topC; (*adj_deg)++;}
    if (topR >= 0 && nodeId % W != W - 1)            if (!data[topR]) {adj_buf[*adj_deg] = topR; (*adj_deg)++;}
    if (midL >= 0 && nodeId % W != 0)                if (!data[midL]) {adj_buf[*adj_deg] = midL; (*adj_deg)++;}
    if (midR < data.size() && (nodeId % W != W - 1)) if (!data[midR]) {adj_buf[*adj_deg] = midR; (*adj_deg)++;}
    if (botL < data.size() && (nodeId % W != 0))     if (!data[botL]) {adj_buf[*adj_deg] = botL; (*adj_deg)++;}
    if (botC < data.size())                          if (!data[botC]) {adj_buf[*adj_deg] = botC; (*adj_deg)++;}
    if (botR < data.size() && nodeId % W != W - 1)   if (!data[botR]) {adj_buf[*adj_deg] = botR; (*adj_deg)++;}   
}


BinaryMatrixMap::BinaryMatrixMap(const char* map_file_name) {
    std::ifstream inp(map_file_name, std::ios_base::in);
    std::string buf;

    inp >> buf >> buf;
    inp >> buf >> H;
    inp >> buf >> W;
    inp >> buf;

    do {
        inp >> buf;
        for (int i = 0; i < buf.size(); i++)
            data.push_back(buf[i] == '.' || buf[i] == 'G');
    } while (!inp.eof());
    
    inp.close();
}


BinaryMatrixMap::BinaryMatrixMap(std::vector<bool> data, size_t width, size_t height)
: data(data)
, W(width)
, H(height) {
    if (data.size() % width != 0 || data.size() % height != 0)
        throw std::invalid_argument("BinaryMatrixMap : dimensions are not compatible");
}


unsigned char* BinaryMatrixMap::exportImageArray() const {
    unsigned char* img_raw =  new unsigned char[H*W*COLOR_BYTES];
    auto           img = (unsigned char (*)[W][COLOR_BYTES]) img_raw;

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++) {
            if(data[i * W + j]) 
                img[H - 1 - i][j][0] = 255, img[H - 1 - i][j][1] = 255, img[H - 1 - i][j][2] = 255;
            else
                img[H - 1 - i][j][0] = 0,   img[H - 1 - i][j][1] = 0,   img[H - 1 - i][j][2] = 0;
        }
    return img_raw;
}


void BinaryMatrixMap::exportBMP(const char *file_name) const {
    unsigned char* img_raw = exportImageArray();
    generateBitmapImage(img_raw, H, W, file_name);
    delete[] img_raw;
}


point BinaryMatrixMap::getSize() const {
    return {H, W};
}


double BinaryMatrixMap::heurDist(int nodeId_1, int nodeId_2) const {
    if (nodeId_1 >= data.size() || nodeId_2 >= data.size() || nodeId_1 < 0 || nodeId_2 < 0)
        throw std::invalid_argument("[BinaryMatrixMap] node id is out of range");

    return hr(
        {nodeId_1 % W, nodeId_1 / W}, 
        {nodeId_2 % W, nodeId_2 / W}
    );
}


void BinaryMatrixMap::setHeuristic(std::function<double(const point&, const point&)> hr) {
    this->hr = hr;
}


double Heuristic::Euclidian(const point& a, const point& b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}


double Heuristic::Manhattan(const point& a, const point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}


double Heuristic::Dijkstra(const point& a, const point& b) {
    return 0;
}
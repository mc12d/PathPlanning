#include "./src/search.hpp"
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
    const char *map_file_name = NULL,
               *out_file_name = NULL,
               *heur          = NULL;
    int opt, x;
    point from, to;

    if (argc <= 5) {
        std::cout << "Map file name and source/destination coordinates must be specified at least. Exiting.\n";
        return 0;
    }

    map_file_name = argv[1];
    from.x = atoi(argv[2]);
    from.y = atoi(argv[3]);
    to.x   = atoi(argv[4]);
    to.y   = atoi(argv[5]);

    while ((opt = getopt(argc, argv, "h:o:")) != -1)
        switch(opt) {
            case 'h' : heur          = optarg; break;
            case 'o' : out_file_name = optarg; break;
        }
    
    std::function<double(const point&, const point&)> hr;
    if      (heur == NULL)              hr = Heuristic::Dijkstra;
    else if (std::string(heur) == "eu") hr = Heuristic::Euclidian;
    else if (std::string(heur) == "mh") hr = Heuristic::Manhattan;
    else {
        std::cout << "Entered heuristic is not valid. Exiting.\n";
        return 0;
    }

    auto search = AStarSearch(map_file_name);
    search.setTargets(from, to);
    search.setHeuristic(hr);
    search.run();

    if (out_file_name == NULL) 
        out_file_name = "out.bmp";
    search.exportPathBMP(out_file_name);
    std::cout << "Complete. Output is " + std::string(out_file_name) << std::endl;
    auto path = search.getPath();
    if (path.empty())
        std::cout << "Note : no valid path found!" << std::endl;

    return 0;
}

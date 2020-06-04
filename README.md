### Path planning A* test task

#### Currently implemented algorithms :
 - A_Star

#### To build
~~~
git clone https://github.com/v3arms/PathPlanning.git
cd PathPlanning
mkdir build
cd build
cmake ..
make
~~~

cmake, g++, linux environment required

#### To run tests
~~~
cd build
./test
(./test -s for verbosity)
(./test -h for another options)
~~~

#### Usage
To build path with A* algorithm:
~~~
cd build
./main map_file_name x_from y_from x_to y_to (-h eu|mh -o output_file_name)
~~~
Program reads map specified as `map_file_name`, source/destination coordinates ((0, 0) is top left) and outputs constructed path as .bmp image `output_file_name` (or `out.bmp` by default)

Notes:

 - `map_file_name` must satisfy the format described [here](https://movingai.com/benchmarks/formats.html).

 - `-h` option allows to set heuristic function on grid (Euclidian or Manhattan distance accordingly). By default zero function is set and A* works as Dijkstra algorithm.

 - To visualize map file you can run `./vis map_file_name` and open `map.bmp` file in build directory.

 - Some sample maps can be found in `maps` directory.
 
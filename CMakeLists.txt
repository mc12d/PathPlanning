cmake_minimum_required(VERSION 2.6)
project(A-star)

set(SRC_LIST_TEST ./src/matrixmap.cpp ./src/writebmp.cpp ./test/testmain.cpp ./test/test.cpp ./src/container.cpp ./src/a-star.cpp ./src/search.cpp)
set(SRC_LIST ./src/matrixmap.cpp ./src/writebmp.cpp ./src/container.cpp ./src/a-star.cpp ./src/search.cpp ./main.cpp)
set(SRC_LIST_VIS ./src/matrixmap.cpp ./src/writebmp.cpp ./vis.cpp)

add_executable(test ${SRC_LIST_TEST})
add_executable(main ${SRC_LIST})
add_executable(vis  ${SRC_LIST_VIS})


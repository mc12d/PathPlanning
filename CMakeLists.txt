cmake_minimum_required(VERSION 2.6)
project(A-star)

set(SRC_LIST_TEST ./src/matrixmap.cpp ./src/writebmp.cpp ./test/testmain.cpp ./test/test.cpp ./src/container.cpp ./src/a-star.cpp)

add_executable(test ${SRC_LIST_TEST})

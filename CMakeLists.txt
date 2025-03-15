cmake_minimum_required(VERSION 3.22)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_executable(main.out main.cpp
        src/grafo_lista.cpp
        include/grafo_lista.h
        include/grafo.h
        src/grafo_matriz.cpp
        include/grafo_matriz.h
        src/grafo.cpp
        include/no_grafo.h
        include/aresta_grafo.h
        src/no_grafo.cpp
        src/aresta_grafo.cpp)

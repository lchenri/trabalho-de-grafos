cmake_minimum_required(VERSION 3.30)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_executable(main src/main.cpp
        src/grafo_lista.cpp
        include/grafo_lista.h
        include/lista_encadeada.h
        include/grafo.h
        src/grafo_matriz.cpp
        include/grafo_matriz.h
        src/lista_encadeada.cpp)

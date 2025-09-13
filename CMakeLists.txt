cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        Colecciones/Canciones.cpp
        Colecciones/Canciones.h
        Estructuras/NodoCancion.cpp
        Estructuras/NodoCancion.h
        Colecciones/Playlist.cpp
        Colecciones/Playlist.h
        Colecciones/Usuario.cpp
        Colecciones/Usuario.h
        Estructuras/listaSimpleCancion.cpp
        Estructuras/listaSimpleCancion.h
        Colecciones/usuarios.cpp
        Colecciones/usuarios.h)

#ifndef UNTITLED_PLAYLIST_H
#define UNTITLED_PLAYLIST_H

#include <string>
#include "Canciones.h"
#include "../Estructuras/ListaSimpleCancion.h"


class Playlist {

    private:
        std::string nombrePlaylist;
        ListaSimpleCancion* canciones;

    public:
        Playlist(std::string n = "");
        ~Playlist();

        std::string getNombrePlaylist() const;
        void setNombrePlaylist(const std::string& n);

        void agregarCanciones(const Canciones& c);
        bool eliminarCancionesPorIndice(int indice);
        int  totalCanciones() const;
        bool getCancion(int indice, Canciones& out) const;
    };

#endif
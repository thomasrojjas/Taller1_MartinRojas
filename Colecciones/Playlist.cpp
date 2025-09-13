#include "Playlist.h"

Playlist::Playlist(std::string n) {
    nombrePlaylist = n;
    canciones = new ListaSimpleCancion();
}

Playlist::~Playlist() {
    delete canciones;
}

std::string Playlist::getNombrePlaylist() const {
    return nombrePlaylist;
}

void Playlist::setNombrePlaylist(const std::string& n) {
    nombrePlaylist = n;
}

void Playlist::agregarCanciones(const Canciones& c) {
    canciones->push_back(c);
}

bool Playlist::eliminarCancionesPorIndice(int indice) {
    return canciones->removeAt(indice);
}

int Playlist::totalCanciones() const {
    return canciones->size();
}

bool Playlist::getCancion(int indice, Canciones& out) const {
    return canciones->getAt(indice, out);
}
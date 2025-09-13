#include "Canciones.h"

Canciones::Canciones(std::string n, std::string al, std::string ar, std::string dur) {
    nombre = n;
    album = al;
    artista = ar;
    duracion = dur;
}

std::string Canciones::getNombre() const {
    return nombre;
}

std::string Canciones::getAlbum() const {
    return album;
}

std::string Canciones::getArtista() const {
    return artista;
}

std::string Canciones::getDuracion() const {
    return duracion;
}

bool Canciones::esIgual(Canciones otra) const {
    return nombre == otra.getNombre() && artista == otra.getArtista();
}

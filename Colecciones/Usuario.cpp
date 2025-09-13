#include "Usuario.h"

Usuario::Usuario() {

    username = "";
    email = "";
    password = "";

    cap = 3;
    cant = 0;

    playlists = new Playlist*[cap];
    for (int i = 0; i < cap; i++) {
        playlists[i] = 0;
    }
}

Usuario::Usuario(const std::string& u, const std::string& e, const std::string& p) {

    username = u;
    email = e;
    password = p;

    cap = 3;
    cant = 0;

    playlists = new Playlist*[cap];
    for (int i = 0; i < cap; i++) {
        playlists[i] = 0;
    }
}

Usuario::~Usuario() {

    for (int i = 0; i < cant; i++) {
        delete playlists[i];
        playlists[i] = 0;
    }
    delete[] playlists;
    playlists = 0;
}

std::string Usuario::getUsername() const {
    return username;
}

std::string Usuario::getEmail() const {
    return email;
}

bool Usuario::checkPassword(const std::string& p) const {
    return p == password;
}

std::string Usuario::getPassword() const {
    return password;
}

int Usuario::totalPlaylists() const {
    return cant;
}

bool Usuario::crearPlaylist(const std::string& nombre) {

    //verificamos si estamos en el maximo de playlist
    if (cant >= cap) {
        return false;
    }

    //verificamos si existe una playlist con ese nombre
    for (int i = 0; i < cant; i++) {
        if (playlists[i]->getNombrePlaylist() == nombre) {
            return false;
        }
    }

    //creamos nueva playlist, guardamos y iteramos cantidad
    playlists[cant] = new Playlist(nombre);
    cant = cant + 1;
    return true;
}

bool Usuario::eliminarPlaylistPorIndice(int indice) {

    //revisamos que el indice ingresado sea valido
    if (indice < 0 || indice >= cant) {
        return false;
    }

    //liberamos memoria de la playlist en la posicion ingresada
    delete playlists[indice];

    //corremos hacia la izquierda los datos
    for (int i = indice; i < cant - 1; i++) {
        playlists[i] = playlists[i + 1];
    }

    //ultima casilla queda disponinle y disminuimos cantidad
    playlists[cant - 1] = 0;
    cant = cant - 1;
    return true;
}

bool Usuario::renombrarPlaylistPorIndice(int indice, const std::string& nuevoNombre) {

    //validamos que el indice ingresado sea valido
    if (indice < 0 || indice >= cant) {
        return false;
    }

    //recorremos y verificamos que no exista otra playlist con el mismo nombre
    for (int i = 0; i < cant; i++) {
        if (i != indice && playlists[i]->getNombrePlaylist() == nuevoNombre) {
            return false;
        }
    }

    //cambiar el nombre usando metodos set
    playlists[indice]->setNombrePlaylist(nuevoNombre);
    return true;
}

Playlist* Usuario::getPlaylistPtr(int indice) {

    //validamos que la posicion ingresada sea valida
    if (indice < 0 || indice >= cant) {
        return 0;
    }

    //devolvemos el puntero a esa playlist
    return playlists[indice];
}
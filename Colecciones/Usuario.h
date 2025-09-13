#ifndef UNTITLED_USUARIO_H
#define UNTITLED_USUARIO_H

#include <string>
#include "Playlist.h"

class Usuario {
private:
    std::string username;
    std::string email;
    std::string password;

    Playlist** playlists;
    int cap;
    int cant;

public:
    Usuario();
    Usuario(const std::string& u, const std::string& e, const std::string& p);
    ~Usuario();

    std::string getUsername() const;
    std::string getEmail() const;
    bool checkPassword(const std::string& p) const;
    std::string getPassword() const;

    int  totalPlaylists() const;
    bool crearPlaylist(const std::string& nombre);
    bool eliminarPlaylistPorIndice(int indice);
    bool renombrarPlaylistPorIndice(int indice, const std::string& nuevoNombre);
    Playlist* getPlaylistPtr(int indice);

};

#endif // UNTITLED_USUARIO_H

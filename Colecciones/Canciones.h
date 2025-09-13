#ifndef UNTITLED_CANCIONES_H
#define UNTITLED_CANCIONES_H

#include <string>

class Canciones {

private:
    std::string nombre;
    std::string album;
    std::string artista;
    std::string duracion;

public:
    Canciones(std::string n = "", std::string al = "", std::string ar = "", std::string dur = "");

    std::string getNombre() const;
    std::string getAlbum() const;
    std::string getArtista() const;
    std::string getDuracion() const;

    bool esIgual(Canciones otra) const;
};

#endif
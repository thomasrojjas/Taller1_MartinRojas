#ifndef UNTITLED_LISTASIMPLECANCION_H
#define UNTITLED_LISTASIMPLECANCION_H
#include "NodoCancion.h"


class ListaSimpleCancion {

private:
    NodoCancion* cabeza;
    NodoCancion* cola;
    int largo;

public:
    ListaSimpleCancion();
    ~ListaSimpleCancion();

    void push_back(const Canciones& c);
    bool removeAt(int indice);
    bool getAt(int indice, Canciones& out) const;
    int size() const;
    void clear();

    int  buscarPorNombreArtista(const std::string& nom, const std::string& art) const;
};
#endif //UNTITLED_LISTASIMPLECANCION_H
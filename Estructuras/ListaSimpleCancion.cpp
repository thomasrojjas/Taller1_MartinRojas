#include "ListaSimpleCancion.h"

ListaSimpleCancion::ListaSimpleCancion() {
    cabeza = 0;
    cola = 0;
    largo = 0;
}

ListaSimpleCancion::~ListaSimpleCancion() {
    clear();
}

void ListaSimpleCancion::push_back(const Canciones& c) {

        Canciones* cancionNueva = new Canciones(c);

        NodoCancion* nodoNuevo = new NodoCancion;
        nodoNuevo->data = cancionNueva;
        nodoNuevo->siguiente = 0;

        if (cabeza == 0) {
            //lista vacia cabeza y cola apuntan al nuevo
            cabeza = nodoNuevo;
            cola   = nodoNuevo;
        }
        else {
            //agregar al final
            cola->siguiente = nodoNuevo;
            cola = nodoNuevo;
        }

        largo = largo + 1;
}

bool ListaSimpleCancion::removeAt(int indice) {

        if (indice < 0 || indice >= largo) {
            return false;
        }

        //eliminar el primero
        if (indice == 0) {
            NodoCancion* nodoAEliminar = cabeza;
            cabeza = cabeza->siguiente;

            if (cola == nodoAEliminar) {
                //si solo habia un elemento la cola tambien cambia
                cola = cabeza;
            }

            delete nodoAEliminar->data;
            delete nodoAEliminar;

            largo = largo - 1;
            return true;
        }

        //buscar el nodo anterior al que queremos borrar
        NodoCancion* anterior = cabeza;
        for (int i = 0; i < indice - 1; i++) {
            anterior = anterior->siguiente;
        }

        NodoCancion* objetivo = anterior->siguiente;  //el que vamos a borrar
        anterior->siguiente = objetivo->siguiente;  //saltamos el objetivo

        if (objetivo == cola) {
            cola = anterior;  // si borramos el último, movemos la cola
        }

        delete objetivo->data;
        delete objetivo;

        largo = largo - 1;
        return true;
}

bool ListaSimpleCancion::getAt(int indice, Canciones& cancion) const {

    if (indice < 0 || indice >= largo) {
        return false;
    }

    NodoCancion* cursor = cabeza;
    for (int i = 0; i < indice; i++) {
        cursor = cursor->siguiente;
    }

    cancion = *(cursor->data);  // copiamos el contenido al parametro de salida
    return true;
}

int ListaSimpleCancion::size() const {
    return largo;
}

void ListaSimpleCancion::clear() {

    NodoCancion* actual = cabeza;

    while (actual != 0) {
        NodoCancion* siguiente = actual->siguiente;

        delete actual->data;
        delete actual;

        actual = siguiente;
    }

    cabeza = 0;
    cola   = 0;
    largo  = 0;
}

int ListaSimpleCancion::buscarPorNombreArtista(const std::string& nombre, const std::string& artista) const {

    NodoCancion* cursor     = cabeza;
    int indiceAux  = 0;

    while (cursor != 0) {
        if (cursor->data->getNombre() == nombre && cursor->data->getArtista() == artista) {
            return indiceAux;  // encontrado
        }

        cursor = cursor->siguiente;
        indiceAux = indiceAux + 1;
    }

    return -1;  // no encontrado
}
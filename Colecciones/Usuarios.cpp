#include "Usuarios.h"

Usuarios::Usuarios() {

    //al inicio no hay usuarios
    cantidad = 0;

    //dejamos todos los punteros del arreglo en 0
    for (int i = 0; i < max; i++) {
        arreglo[i] = 0;
    }
}

Usuarios::~Usuarios() {

    //liberamos cada usuario creado con new
    for (int i = 0; i < cantidad; i++) {
        delete arreglo[i];
        arreglo[i] = 0;
    }
}

int Usuarios::size() const {
    return cantidad;
}

Usuario* Usuarios::getAt(int indice) const {

    //si el indice esat fuera del rango devolvemos 0
    if (indice < 0 || indice >= cantidad) {
        return 0;
    }
    return arreglo[indice];
}

int Usuarios::buscarPorUsername(const std::string& username) const {

    //recorremos desde 0 hasta el max
    for (int i = 0; i < cantidad; i++) {
        if (arreglo[i]->getUsername() == username) {
            return i;  //si se encuentra se retorna
        }
    }
    return -1;
}

int Usuarios::buscarPorEmail(const std::string& email) const {

    //recorremos el arreglo y comparamos el email
    for (int i = 0; i < cantidad; i++) {
        if (arreglo[i]->getEmail() == email) {
            return i;
        }
    }
    return -1;
}

bool Usuarios::agregarUsuario(Usuario* usuarioNuevo) {

    //caso puntero nulo
    if (usuarioNuevo == 0) {
        return false;
    }

    //caso de que este lleno
    if (cantidad >= max) {
        return false;
    }

    //si el usarname ya existe
    if (buscarPorUsername(usuarioNuevo->getUsername()) != -1) {
        return false;
    }

    //finalmente guardamos nuevo usuario y aumentamos cantidad
    arreglo[cantidad] = usuarioNuevo;
    cantidad = cantidad + 1;
    return true;
}

int Usuarios::autenticar(const std::string& username, const std::string& password) const {

    //buscamos el indice del usuario por su nombre
    int indiceEncontrado = buscarPorUsername(username);
    if (indiceEncontrado == -1) {
        return -1;  //usuario no existe
    }

    //verificamos la contraseña del usuario encontrado
    if (arreglo[indiceEncontrado]->checkPassword(password)) {
        return indiceEncontrado;
    }

    else {
        return -1;
    }
}

bool Usuarios::eliminarPorIndice(int indice) {

    //verificamos que haya datos
    if (indice < 0 || indice >= cantidad) {
        return false;
    }

    //liberamos meoria de ese usuario
    delete arreglo[indice];

    //corremos los datos a la izquierda
    for (int i = indice; i < cantidad - 1; i++) {
        arreglo[i] = arreglo[i + 1];
    }

    //ultima posicion a 0 y disminuimos contador
    arreglo[cantidad - 1] = 0;
    cantidad = cantidad - 1;
    return true;
}

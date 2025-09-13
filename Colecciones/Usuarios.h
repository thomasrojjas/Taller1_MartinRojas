#ifndef UNTITLED_USUARIOS_H
#define UNTITLED_USUARIOS_H
#include "Usuario.h"


class Usuarios {

    private:
    static const int MAX = 10;   // capacidad fija (cámbialo si quieres)
    Usuario* arreglo[MAX];
    int cantidad;

    public:
    Usuarios();
    ~Usuarios();

    int size() const;
    Usuario* getAt(int indice) const;

    bool agregarUsuario(Usuario* usuarioNuevo);  // falla si está lleno o si username ya existe
    int  buscarPorUsername(const std::string& username) const;
    int  buscarPorEmail(const std::string& email) const;
    int  autenticar(const std::string& username, const std::string& password) const;
    bool eliminarPorIndice(int indice);

};


#endif //UNTITLED_USUARIOS_H
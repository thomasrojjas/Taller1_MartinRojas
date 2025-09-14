#ifndef UNTITLED_USUARIOS_H
#define UNTITLED_USUARIOS_H
#include "Usuario.h"


class Usuarios {

    private:
    static const int max = 10;
    Usuario* arreglo[max];
    int cantidad;

    public:
    Usuarios();
    ~Usuarios();

    int size() const;
    Usuario* getAt(int indice) const;

    bool agregarUsuario(Usuario* usuarioNuevo);
    int  buscarPorUsername(const std::string& username) const;
    int  buscarPorEmail(const std::string& email) const;
    int  autenticar(const std::string& username, const std::string& password) const;
    bool eliminarPorIndice(int indice);

};


#endif //UNTITLED_USUARIOS_H
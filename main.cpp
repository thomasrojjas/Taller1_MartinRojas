#include <fstream>
#include <iostream>
#include <string>

#include "Colecciones/Canciones.h"
#include "Colecciones/Playlist.h"
#include "Colecciones/Usuario.h"
#include "Colecciones/Usuarios.h"

//VALIDACIONES DE CONTRASENIA

bool tieneNumero(const std::string& s) {

    //recorremos y si tiene un numero entre 0 y 9 es valido, de lo contrario no se permite el paso
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            return true;
        }
    }
    return false;
}

bool tieneMayuscula(const std::string& s) {

    //recorremos y verificamos si tiene una mayuscula de rango entre A a la Z. De lo contrario no se permite el paso.
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            return true;
        }
    }
    return false;
}

bool tieneSigno(const std::string& s) {

    //recorremos cada caracter del texto
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];

        //creamos letraMinus,letraMayus y digito. para luego comparar
        bool letraMinus = (c >= 'a' && c <= 'z');
        bool letraMayus = (c >= 'A' && c <= 'Z');
        bool digito     = (c >= '0' && c <= '9');

        //si no es Minus, Mayus ni digito se deduce que es un signo
        if (!letraMinus && !letraMayus && !digito) {
            return true;
        }
    }
    return false;
}

bool emailValidoBasico(const std::string& correo) {
    int posArroba = -1;   //posicion del primer @ que encontremos
    int posPunto  = -1;   //posicion del ultimo . que encontremos

    int tam = correo.length(); //tamanio del texto

    //recorremos para ubicar @ y .
    for (int i = 0; i < (int)correo.size(); i++) {
        char c = correo[i];

        if (c == '@' && posArroba == -1) {
            posArroba = i;     //guarda la primera @ encontrada
        }

        if (c == '.') {
            posPunto = i;      //se queda con el ultimo .
        }
    }

    //restricciones basicas
    //debe existir @ y no puede estar al inicio o solo
    if (posArroba <= 0) {
        return false;
    }

    //debe haber un . despues del @ y no pegado
    if (posPunto <= posArroba + 1) {
        return false;
    }

    //debe terminar en com o cl
    if (tam >= 3 && correo[tam - 3] == 'c' && correo[tam - 2] == 'o' && correo[tam - 1] == 'm') {
        return true;
    }

    if (tam >= 2 && correo[tam - 2] == 'c' && correo[tam - 1] == 'l') {
        return true;
    }

    return false;
}



//GUARDAR DATOS

//ESCRITURA USUARIOS
bool guardarUsuariosTXT(const Usuarios& sistema) {
    std::ofstream out("users.txt");
    if (!out.is_open()) {
        std::cout << "no se pudo escribir users.txt";
        return false;
    }

    out << "id,username,email,password";
    for (int i = 0; i < sistema.size(); i++) {
        Usuario* u = sistema.getAt(i);
        out << (i+1) << ","
            << u->getUsername() << ","
            << u->getEmail()    << ","
            << u->getPassword();
    }
    out.close();
    return true;
}

//ESCRITURA PLAYLIST
bool guardarPlaylistsTXT(const Usuarios& sistema) {
    std::ofstream out("playlists.txt");
    if (!out.is_open()) {
        std::cout << "no se pudo escribir playlists.txt";
        return false;
    }

    //escribimos la cabecera del txt
    out << "username,playlist,nombre,album,artista,duracion\n";

    //recorre todos los usuarios
    for (int indiceUsuario = 0; indiceUsuario < sistema.size(); indiceUsuario++) {
        Usuario* usuario = sistema.getAt(indiceUsuario);

        //recorre todas las playlist del usuario
        for (int indicePlaylist = 0; indicePlaylist < usuario->totalPlaylists(); indicePlaylist++) {
            Playlist* playlist = usuario->getPlaylistPtr(indicePlaylist);

            //recorre todas las canciones de la playlist
            for (int indiceCancion = 0; indiceCancion < playlist->totalCanciones(); indiceCancion++) {
                Canciones cancionTemporal;

                //escribimos playlist con sus canciones
                playlist->getCancion(indiceCancion, cancionTemporal);

                out << usuario->getUsername()           << ","
                    << playlist->getNombrePlaylist()     << ","
                    << cancionTemporal.getNombre()       << ","
                    << cancionTemporal.getAlbum()        << ","
                    << cancionTemporal.getArtista()      << ","
                    << cancionTemporal.getDuracion();
            }
        }
    }

    out.close();
    return true;
}



//LECTURA DE ARCHIVHO

bool lecturaArchivoUsuariosTXT(Usuarios& sistema) {

    std::ifstream archivo("users.txt");
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir users.txt";
        return false;
    }

    // Leer la cabecera
    std::string cabecera;
    std::getline(archivo, cabecera);  //saltamos la cabecera para empezar con los datos reales

    int cargados = 0;  //contador de usuarios cargados

    //lectura de archivo importante
    while (true) {
        std::string id;
        std::string user;
        std::string mail;
        std::string pass;

        if (!std::getline(archivo, id,   ',')) {
            break;  //si no se pudo leer el id salimos del while
        }
        if (!std::getline(archivo, user, ',')) {
            break;  //leemos username hasta la coma si falla salimos del while
        }
        if (!std::getline(archivo, mail, ',')) {
            break;  //leemos email hasta la coma si falla salimos del while
        }
        if (!std::getline(archivo, pass)) {
            break;  //leemos password hasta fin de línea si falla salimos del while
        }

        Usuario* u = new Usuario(user, mail, pass);  //creamos el usuario con los datos leidos
        if (sistema.agregarUsuario(u)) {
            cargados++;  //si se pudo agregar sumamos al contador
        }
        else {
            delete u;  //si no eliminamos y liberamos memoria
        }
    }

    std::cout << "Usuarios cargados: " << cargados;
    archivo.close();
    return true;
}

bool lecturaArchivoCanciones(Playlist* pl) {
    std::ifstream archivo("canciones.txt");
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir canciones.txt";
        return false;
    }

    //leemos la cabecera
    std::string cabecera;
    std::getline(archivo, cabecera);

    int cargadas = 0;  //contador de canciones cargadas

    //lectura de canciones
    while (true) {
        std::string nombre;
        std::string album;
        std::string artista;
        std::string durTxt;

        if (!std::getline(archivo, nombre,  ',')) {
            break;  //leemos nombre hasta la coma
        }
        if (!std::getline(archivo, album,   ',')) {
            break;  //leemos album hasta la coma
        }
        if (!std::getline(archivo, artista, ',')) {
            break;  //leemos artista hasta la coma
        }
        if (!std::getline(archivo, durTxt)) {
            break;  //leemos duracion hasta fin de línea
        }

        //creamos la cancion y la agregamos
        Canciones c(nombre, album, artista, durTxt);
        pl->agregarCanciones(c);  //la metemos a la playlist
        cargadas = cargadas + 1;  //contamos una más
    }

    std::cout << "Canciones cargadas: " << cargadas; //mostramos cuantas se cargaron
    archivo.close();
    return true;
}



//MOSTRAR PLAYLISY Y CANCIONES

void mostrarPlaylists(Usuario* u) {
    //obtenemos total de playlist
    int total = u->totalPlaylists();

    //si es 0 se especifica que no hay playlist
    if (total == 0) {
        std::cout << "(sin playlists)";
        return;
    }

    //de lo contrario se recorre y muestra la playlist con su total de canciones
    for (int i = 0; i < total; i++) {
        Playlist* p = u->getPlaylistPtr(i);
        std::cout << i << ") " << p->getNombrePlaylist()
                  << " [" << p->totalCanciones() << "]";
    }
}

void mostrarCanciones(Playlist* pl) {
    //obtenemos total de canciones
    int n = pl->totalCanciones();

    //si es 0 se especifica que no hay canciones
    if (n == 0) {
        std::cout << "(sin canciones)";
        return;
    }

    Canciones cancion;
    for (int i = 0; i < n; i++) {
        if (pl->getCancion(i, cancion)) {
            std::cout << i << ") " << cancion.getNombre()
                      << " — " << cancion.getArtista()
                      << " [" << cancion.getAlbum() << "] ("
                      << cancion.getDuracion() << ")";
        }
    }
}



//MENUS

void menuPlaylist(Playlist* pl, Usuarios& sistema) {
    while (true) {
        std::cout << "--- PLAYLIST: " << pl->getNombrePlaylist() << " ---";
        std::cout << "1) Ver canciones";
        std::cout << "2) Agregar cancion";
        std::cout << "3) Eliminar cancion por indice";
        std::cout << "4) Cargar canciones desde archivo (canciones.txt)";
        std::cout << "5) Buscar cancion (nombre + artista)";
        std::cout << "0) Volver";
        std::cout << "Opcion: ";

        int op;
        std::cin >> op;

        if (op == 0) {
            break;
        }

        if (op == 1) {
            mostrarCanciones(pl);
        }

        if (op == 2) {
            std::string nombre, album, artista, durTxt;
            std::cout << "nombre (sin comas ni espacios): ";  std::cin >> nombre;
            std::cout << "album (sin comas ni espacios): ";   std::cin >> album;
            std::cout << "artista (sin comas ni espacios): "; std::cin >> artista;
            std::cout << "duracion (mm:ss): ";                std::cin >> durTxt;

            Canciones c(nombre, album, artista, durTxt);
            pl->agregarCanciones(c);
            std::cout << "cancion agregada";
            guardarPlaylistsTXT(sistema);
        }

        if (op == 3) {
            if (pl->totalCanciones() == 0) {
                std::cout << "no hay canciones";
            }
            else {
                int indice;
                std::cout << "indice a eliminar" << (pl->totalCanciones()-1) << "): ";
                std::cin >> indice;

                if (indice >= 0 && indice < pl->totalCanciones() && pl->eliminarCancionesPorIndice(indice)) {
                    std::cout << "eliminada";
                    guardarPlaylistsTXT(sistema);
                }
                else {
                    std::cout << "no se pudo eliminar";
                }
            }
        }

        if (op == 4) {
            if (lecturaArchivoCanciones(pl)) {
                std::cout << "archivo cargado";
                guardarPlaylistsTXT(sistema);
            }
            else {
                std::cout << "no se pudo cargar";
            }
        }

        if (op == 5) {
            std::string nom, art;
            std::cout << "nombre exacto: ";
            std::cin >> nom;
            std::cout << "artista exacto: ";
            std::cin >> art;

            Canciones cancion;
            int posicion = -1;
            for (int i = 0; i < pl->totalCanciones(); i++) {
                if (pl->getCancion(i, cancion) && cancion.getNombre() == nom && cancion.getArtista() == art) {
                    posicion = i; break;
                }
            }
            if (posicion != -1) {
                std::cout << "encontrada en posicion: " << posicion;
            }
            else {
                std::cout << "no encontrada";
            }
        }

        else {
            std::cout << "opcion invalida";
        }
    }
}

void menuUsuario(Usuario* u, Usuarios& sistema) {
    while (true) {
        std::cout << "--- USUARIO: " << u->getUsername() << " ---";
        std::cout << "1) listar playlists";
        std::cout << "2) crear playlist";
        std::cout << "3) renombrar playlist";
        std::cout << "4) eliminar playlist";
        std::cout << "5) entrar a una playlist";
        std::cout << "0) cerrar sesion y volver al menu principal";
        std::cout << "opcion: ";

        int op;
        std::cin >> op;

        if (op == 0) {
            break;
        }

        if (op == 1) {
            mostrarPlaylists(u);
        }

        if (op == 2) {
            if (u->totalPlaylists() >= 3) {
                std::cout << "tope de 3 playlists alcanzado";
            }
            else {
                std::string nombre;
                std::cout << "nombre nueva playlist: ";
                std::cin >> nombre;

                if (u->crearPlaylist(nombre)) {
                    std::cout << "creada"; guardarPlaylistsTXT(sistema);
                }
                else {
                    std::cout << "no se pudo crear";
                }
            }
        }

        if (op == 3) {
            if (u->totalPlaylists() == 0) std::cout << "No hay playlists\n";
            else
            {
                mostrarPlaylists(u);
                int indice;
                std::cout << "indice a renombrar" << (u->totalPlaylists()-1) << "): ";
                std::cin >> indice;

                std::string nuevo;
                std::cout << "nuevo nombre: ";
                std::cin >> nuevo;

                if (u->renombrarPlaylistPorIndice(indice, nuevo)) { std::cout << "renombrada"; guardarPlaylistsTXT(sistema); }
                else std::cout << "no se pudo renombrar";
            }
        }

        if (op == 4) {
            if (u->totalPlaylists() == 0) {
                std::cout << "no hay playlists";
            }
            else {
                mostrarPlaylists(u);
                int indice;
                std::cout << "indice a eliminar" << (u->totalPlaylists()-1) << "): ";
                std::cin >> indice;

                if (u->eliminarPlaylistPorIndice(indice)) {
                    std::cout << "eliminada"; guardarPlaylistsTXT(sistema);
                }
                else std::cout << "no se pudo eliminar";
            }
        }

        if (op == 5) {
            if (u->totalPlaylists() == 0) {
                std::cout << "no hay playlists";
            }
            else {
                mostrarPlaylists(u);
                int indice;
                std::cout << "indice a abrir" << (u->totalPlaylists()-1) << "): ";
                std::cin >> indice;

                Playlist* pl = u->getPlaylistPtr(indice);
                if (pl != 0) {
                    menuPlaylist(pl, sistema);
                }
                else {
                    std::cout << "indice invalido";
                }
            }
        }
        else std::cout << "opcion invalida";
    }
}


//REGISTRO / LOGIN

void registrar(Usuarios& sistema) {
    if (sistema.size() >= 10) {
        std::cout << "capacidad maxima alcanzada";
        return;
    }

    std::string user, mail, pass, pass2;

    std::cout << "username: ";
    std::cin >> user;

    if (sistema.buscarPorUsername(user) != -1) {
        std::cout << "username en uso. Intenta con otro...";
        return;
    }

    std::cout << "email (sin comas ni espacios): ";
    std::cin >> mail;
    if (!emailValidoBasico(mail)) {
        std::cout << "email invalido";
        return;
    }

    if (sistema.buscarPorEmail(mail) != -1) {
        std::cout << "email ya registrado";
        return;
    }

    std::cout << "password (con numero, mayuscula y signo): ";
    std::cin >> pass;
    std::cout << "confirmar password: ";
    std::cin >> pass2;
    if (pass != pass2) {
        std::cout << "no coinciden";
        return;
    }
    if (!tieneNumero(pass) || !tieneMayuscula(pass) || !tieneSigno(pass)) {
        std::cout << "password no cumple requisitos";
        return;
    }

    Usuario* u = new Usuario(user, mail, pass);
    if (sistema.agregarUsuario(u)) {
        std::cout << "registro confirmado";
        guardarUsuariosTXT(sistema);
    }
    else {
        std::cout << "no se pudo registrar";
        delete u;
    }
}

bool iniciarSesion(Usuarios& sistema, Usuario*& sesion) {
    int intentos = 0;
    while (intentos < 3) {
        std::string user, pass;
        std::cout << "username: "; std::cin >> user;
        std::cout << "password: "; std::cin >> pass;

        int idx = sistema.autenticar(user, pass);
        if (idx != -1) {
            sesion = sistema.getAt(idx);
            std::cout << "login correcto";
            return true;
        }
        std::cout << "credenciales invalidas";
        intentos++;
    }
    return false;
}


//MAIN

int main() {
    Usuarios sistema;
    Usuario* sesion = 0;

    lecturaArchivoUsuariosTXT(sistema); // si no existe, sigue igual

    while (true) {
        std::cout << "--- MENU PRINCIPAL ---";
        std::cout << "1) iniciar sesion";
        std::cout << "2) registrarse";
        std::cout << "0) cerrar el programa";
        std::cout << "opcion: ";

        int op;
        std::cin >> op;

        if (op == 0) {
            break;
        }

        if (op == 1) {
            if (iniciarSesion(sistema, sesion)) {
                menuUsuario(sesion, sistema);
                sesion = 0; // salir deja al usuario deslogueado
            }
        }

        if (op == 2) {
            registrar(sistema);
        }

        else {
            std::cout << "opcion invalida";
        }
    }

    std::cout << "Hasta luego";
    return 0;
}
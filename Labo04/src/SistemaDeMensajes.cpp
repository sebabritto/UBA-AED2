#include "SistemaDeMensajes.h"

#if /*EJ == 4 || EJ == 5*/ EJ < 6
#include "Proxy.h"
#elif EJ == 6
#include "Proxy2.h"
#endif


// Completar...
SistemaDeMensajes::SistemaDeMensajes() {
    for(int i = 0; i < 4; i++){
        _conns[i] = nullptr;
    }
}

/*void SistemaDeMensajes::registrarJugador(int id, string ip) {
    _conns[id] = new ConexionJugador(ip);
    //Otra forma de hacerlo
    //ConexionJugador* c1 = new ConexionJugador(ip);
    //_conns[id] = c1;
}*/

void SistemaDeMensajes::enviarMensaje(int id, string mensaje) {
    (*_conns[id]).enviarMensaje(mensaje);
    //_conns[id]->enviarMensaje(mensaje);
}

bool SistemaDeMensajes::registrado(int id) const {
    return _conns[id] != nullptr;
}

string SistemaDeMensajes::ipJugador(int id) const {
    return _conns[id]->ip();
    //return (*_conns[id]).ip();
}

//Ejercicio 2
SistemaDeMensajes::~SistemaDeMensajes() {
    for(int i = 0; i < 4; i++){
        delete _conns[i];
    }

    for(int j = 0; j < _proxys.size(); j++){
        delete _proxys[j];
    }
}

//Ejercicio 3

void SistemaDeMensajes::desregistrarJugador(int id) {
    /*for(Proxy* c: _proxys){
        if(c->devolverJugador() == _conns[id]){
            delete c;
            c = nullptr;
        }
    }*/
    delete _conns[id];
    _conns[id] = nullptr;
}

void SistemaDeMensajes::registrarJugador(int id, string ip) {
    if(_conns[id] == nullptr){
        _conns[id] = new ConexionJugador(ip);
    }else{
        ConexionJugador* temp = _conns[id];

        delete _conns[id];

        ConexionJugador* nuevo = new ConexionJugador(ip);
        _conns[id] = nuevo;
        #if EJ == 6
        for(Proxy* c: _proxys){
            if(c->devolverJugador() == temp){
                delete c;
                c = new Proxy(&nuevo);
            }
        }
        #endif
    }
}

//Ejercicio 4

Proxy* SistemaDeMensajes::obtenerProxy(int id) {

    #if /*EJ == 4 || EJ == 5*/ EJ < 6
        Proxy* p = new Proxy(_conns[id]);
    #elif EJ == 6
        Proxy* p = new Proxy(&_conns[id]);
    #endif

    //ordenar vector o crear un metodo en Proxy2 q te devuelva el id
    //para ordenar un vector tendria q tener al menos un identificador para la conexion jugador para poder
    //diferenciar uno de otro, es mejor devolver el puntero conexion jugador de proxy2
    _proxys.push_back(p);

    return p;
}

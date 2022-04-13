#include "SistemaDeMensajes.h"
#include "Proxy2.h"
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
    delete _conns[id];
    _conns[id] = nullptr;
}

void SistemaDeMensajes::registrarJugador(int id, string ip) {
    if(_conns[id] == nullptr){
        _conns[id] = new ConexionJugador(ip);
    }else{
        for(Proxy* c: _proxys){
            if(c){

            }
        }
        delete _conns[id];
        _conns[id] = new ConexionJugador(ip);

    }
}

//Ejercicio 4

Proxy* SistemaDeMensajes::obtenerProxy(int id) {
    //return new Proxy(_conns[id]);
    //ConexionJugador** c1 = &_conns[id];
    Proxy* p = new Proxy(&_conns[id]);

    //ordenar vector o crear un metodo en Proxy2 q te devuelva el id
    _proxys.push_back(p);

    return p;
}
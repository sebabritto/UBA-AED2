#include "aed2_Servidor.h"

using namespace std;

aed2_Servidor::aed2_Servidor(): _servidor(Servidor()){}

void aed2_Servidor::nuevaPartida(Jugador j, set<int> horizontales, set<int> verticales){
    _servidor.agregarSC(j, horizontales, verticales);
}

void aed2_Servidor::agregarCasa(Jugador j, Casilla c){
    _servidor.agregarCasa(j, c);
}

void aed2_Servidor::agregarComercio(Jugador j, Casilla c){
    _servidor.agregarComercio(j, c);
}

void aed2_Servidor::avanzarTurno(Jugador j){
    _servidor.avanzarTurno(j);
}

void aed2_Servidor::unir(Jugador j1, Jugador j2){
    _servidor.unir(j1,j2);

}

set<int> aed2_Servidor::riosHorizontales(Jugador j) const{
    return _servidor.riosHorizontales(j);
}

set<int> aed2_Servidor::riosVerticales(Jugador j) const{
    return _servidor.riosVerticales(j);
}

set<Casilla> aed2_Servidor::casas(Jugador j) const {
    //set<Casilla> res = set<Casilla> set((_servidor.casas(j)).begin,_servidor.casas(j)).end);
    //return res;
    return _servidor.casas(j);
}

set<Casilla> aed2_Servidor::comercios(Jugador j) const{
    /*set<Casilla> res = set<Casilla> set((_servidor.comercios(j)).begin,_servidor.comercios(j)).end);
    return res;*/
    return _servidor.comercios(j);
}

Nat aed2_Servidor::nivel(Jugador j, Casilla c) const{
    return _servidor.nivel(j, c);
}

bool aed2_Servidor::huboConstruccion(Jugador j) const{
    /*if(_servidor.casas(j).empty() && _servidor.comercios(j).empty()){
        return true;
    }
    return false;*/
    return _servidor.huboConstruccion(j);
}

Nat aed2_Servidor::popularidad(Jugador j) const{
    //return popularidad(j);
    return _servidor.popularidad(j);
}

Nat aed2_Servidor::antiguedad(Jugador j) const{
    //return antiguedad(j);
    return _servidor.antiguedad(j);
}
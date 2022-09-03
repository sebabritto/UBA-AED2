#include "Servidor.h"
//#include "Tipos.h"

Servidor::Servidor():
_partidas(diccTrie<Simcity>()), _modificables(diccTrie<bool>()), _hijos(diccTrie<list<string>>()){}

void Servidor::agregarSC(Jugador j, set<int> horizontales, set<int> verticales){
    Mapa mapa = Mapa(horizontales, verticales);
    _partidas.insert(make_pair(j, Simcity(mapa)));
    _hijos.insert(make_pair(j, list<string>()));
    _modificables.insert(make_pair(j, false));
}

void Servidor::agregarCasa(Jugador j, Casilla c) {
    _partidas.at(j).agregarCasa(c);
}

void Servidor::agregarComercio(Jugador j, Casilla c){
    _partidas.at(j).agregarComercio(c);
}

void Servidor::unir(Jugador j1, Jugador j2){
    (_partidas.at(j1)).unir(_partidas.at(j2)); //realizo la union de los SimCitys
    _modificables.at(j1) = false; //cambio su valor en modificables, ya que no se puede modificar mas
    _hijos.at(j1).emplace_back(j2); // agrego j2 a los hijos de j1
}

void Servidor::avanzarTurno(Jugador j){
    (_partidas.at(j)).avanzarTurno();
}

set<int> Servidor::riosHorizontales(Jugador j) const{
    return _partidas.at(j).mapa().horizontales();
}

set<int> Servidor::riosVerticales(Jugador j) const{
    return _partidas.at(j).mapa().verticales();
}

set<Casilla> Servidor::casas(Jugador j) const{
    set<Casilla> res;
    list<pair<Casilla, Nat>> casas = _partidas.at(j).casas();
    for(pair<Casilla, Nat> casa: casas){
        res.insert(casa.first);
    }
    return res;
}

set<Casilla> Servidor::comercios(Jugador j) const{
    set<Casilla> res;
    list<pair<Casilla, Nat>> comercios = _partidas.at(j).comercios();
    for(pair<Casilla, Nat> comercio: comercios){
        res.insert(comercio.first);
    }
    return res;
}

Nat Servidor::nivel(Jugador j, Casilla c) const{
    //Precondicion: La posicion debe tener una construccion.
    list<pair<Casilla, Nat>> casas = _partidas.at(j).casas();
    list<pair<Casilla, Nat>> comercios = _partidas.at(j).comercios();

    for(pair<Casilla, Nat> casa: casas){
        if(casa.first == c){
            return casa.second;
        }
    }
    for(pair<Casilla, Nat> comercio: comercios){
        if(comercio.first == c){
            return comercio.second;
        }
    }
    return 0;
}

bool Servidor::huboConstruccion(Jugador j) const{
    return _partidas.at(j).huboConstruccion();
}

Nat Servidor::popularidad(Jugador j) const{
    return _partidas.at(j).popularidad();
    //return _hijos.at(j).size();
}

Nat Servidor::antiguedad(Jugador j) const{
    return _partidas.at(j).turno();
}
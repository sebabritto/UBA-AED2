#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "SimCity.h"
#include "Mapa.h"
#include "Tipos.h"


class Servidor{
public:
    Servidor();

    void agregarSC(const Jugador, set<int>, set<int>);

    //void agregarCasas(Jugador, list<pair<Casilla,Nat>>&);

    void agregarCasa(const Jugador, Casilla);

    //void agregarComercios(Jugador, list<pair<Casilla,Nat>>&);

    void agregarComercio(const Jugador, Casilla);

    void avanzarTurno(const Jugador);

    void unir(const Jugador, const Jugador);

    set<int> riosHorizontales(const Jugador j) const;

    set<int> riosVerticales(const Jugador j) const;

    set<Casilla> casas(const Jugador j) const;

    set<Casilla> comercios(const Jugador j) const;

    Nat nivel(const Jugador j, Casilla c) const;

    bool huboConstruccion(const Jugador j) const;

    Nat popularidad(const Jugador j) const;

    Nat antiguedad(const Jugador j) const;

private:
    diccTrie<Simcity> _partidas;
    diccTrie<bool> _modificables;
    diccTrie<list<string>> _hijos;
};

#endif //SERVIDOR_H

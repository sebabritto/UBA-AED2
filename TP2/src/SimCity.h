#ifndef SIMCITY_H
#define SIMCITY_H

#include "Mapa.h"
#include "Tipos.h"

using namespace std;

class Simcity{
public:
    Simcity(Mapa m);

    void agregarCasa(Casilla);

    void agregarComercio(Casilla);

    void unir(Simcity s2);

    list<pair<Casilla, Nat>> casas() const;

    list<pair<Casilla, Nat>> comercios() const;

    Nat popularidad() const;

    Nat turno() const;

    bool huboConstruccion() const;

    Mapa mapa() const;

    Nat cantUnidos() const;

    void avanzarTurno();

private:
    Mapa _mapa;

    list<pair<Casilla, Nat>> _casas;    // Esto podría implementarse con algo mejor que listas capaz, pero sólo si lo usamos!

    list<pair<Casilla, Nat>> _comercios;    //ídem

    list<Simcity> _unidos;

    Nat _popularidad;

    Nat _turno;

    bool _huboConstruccion;

    list<pair<set<int>,set<int>>> _riosPendientes;

    ///FUNCIONES AUXILIARES///
    void definirEnLista(pair<Casilla, Nat> par, list<pair<Casilla, Nat>>& cs) const ;
    bool definidoEnLista(Casilla pos, const list<pair<Casilla, Nat>>& cs) const;
    void borrarEnLista(Casilla pos, list<pair<Casilla, Nat>>& cs) const;

    void definirEnCasas(pair<Casilla, Nat> par) const;

    void mergeUniones(list<pair<Casilla, Nat>>&, list<pair<Casilla, Nat>>&, list<Simcity>&) const;
    void mergeTotal(Simcity) const;
    void mergeCasas(list<pair<Casilla, Nat>>&, list<pair<Casilla, Nat>>&, list<pair<Casilla, Nat>>, Nat, Nat) const;
    void mergeComercios(list<pair<Casilla, Nat>>&, list<pair<Casilla, Nat>>&, list<pair<Casilla, Nat>> ,Nat, Nat) const;
    bool esConstruccionMayor(const list<pair<Casilla, Nat>>&, pair<Casilla, Nat>, Nat, Nat) const;

    void mergeMapa(Mapa &) const;

    Mapa mergeMapaBis(const Mapa&, const list<pair<set<int>,set<int>>>& ) const;

    void sumarNivel();


    list<pair<Casilla, Nat>> actualizarM(const list<pair<Casilla, Nat>>&, const list<pair<Casilla, Nat>>&) const;

    list<pair<Casilla, Nat>> mergeCasasTotales(const list<pair<Casilla, Nat>>&, const list<pair<Casilla, Nat>>&, const list<Simcity>&) const;
    list<pair<Casilla, Nat>> mergeComerciosTotales(const list<pair<Casilla, Nat>>&, const list<pair<Casilla, Nat>>&, const list<Simcity>&) const;



    Nat obtenerNivelEnLista(Casilla pos, list<pair<Casilla, Nat>> cs) const;

    void actualizarManhattan(list<pair<Casilla, Nat>>&, const list<pair<Casilla, Nat>>&) const;
    Nat maxNivelManhattan(Casilla pos, list<pair<Casilla, Nat>> cs) const;
    bool esManhattan(Casilla pos1, Casilla pos2) const;



    void definirSegunNivel(pair<Casilla, Nat> par, list<pair<Casilla, Nat>> &cs, Nat nivel);
};


#endif //SIMCITY_H

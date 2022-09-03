#include "Mapa.h"

Mapa::Mapa(set<int> &h, set<int> &v): _horizontales(h), _verticales(v){}

Mapa::~Mapa() {
    _horizontales.clear();
    _verticales.clear();
}

set<int> Mapa::horizontales() const{
    return _horizontales;
}

set<int> Mapa::verticales() const{
    return _verticales;
}

/*void Mapa::fusionar(Mapa &m) const{
    for (int n : m.horizontales()){
        _horizontales.insert(n);
    }
    for (int n : m.verticales()){
        _verticales.insert(n);
    }
}*/
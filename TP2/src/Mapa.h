#ifndef MAPA_H
#define MAPA_H

#include "Tipos.h"

class Mapa{
public:
    Mapa(set<int> &h, set<int> &v);

    ~Mapa();

    set<int> horizontales() const;

    set<int> verticales() const;

    void fusionar(Mapa);

private:
    set<int> _horizontales;

    set<int> _verticales;

};

#endif //MAPA_H

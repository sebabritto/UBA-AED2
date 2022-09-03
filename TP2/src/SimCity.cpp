#include "SimCity.h"

/////////////////////////////////FUNCIONES PUBLICAS/////////////////////////////////

Simcity::Simcity(Mapa m): _mapa(m), _casas(list<pair<Casilla,Nat>>()), _comercios(list<pair<Casilla,Nat>>()), _popularidad(0), _turno(0),
                          _unidos(list<Simcity>()), _huboConstruccion(false){}

void Simcity::agregarCasa(Casilla c) {
    _huboConstruccion = true;
    _casas.push_back(make_pair(c, 0));
}

void Simcity::agregarComercio(Casilla c) {  //ídem
    _huboConstruccion = true;
    _comercios.push_back(make_pair(c, 0));
}

Mapa Simcity::mapa() const{
    return mergeMapaBis(_mapa, _riosPendientes);
}

Mapa Simcity::mergeMapaBis(const Mapa& m, const list<pair<set<int>,set<int>>>& rios) const{
    set<int> *h = new set<int>(m.horizontales());
    set<int> *v = new set<int>(m.verticales());
    Mapa mapa = m;
    list<pair<set<int>,set<int>>>  riosT = rios;
    for(auto i: riosT){
        for(auto horiz: i.first){
            h->insert(horiz);
        }
        for(auto vert: i.second){
            v->insert(vert);
        }
    }
    mapa = Mapa(*h, *v);
    delete h;
    delete v;
    return mapa;
}

list<pair<Casilla, Nat>> Simcity::casas() const{
    if(!_unidos.empty()){
        return mergeCasasTotales(_casas, _comercios, _unidos);
    }else{
        return _casas;
    }
}

list<pair<Casilla, Nat>> Simcity::actualizarM(const list<pair<Casilla, Nat>> & comercios, const list<pair<Casilla, Nat>> & casas) const{
    auto comercios1 = comercios;

    for(auto & i : comercios1){
        Nat lvl= max(i.second, maxNivelManhattan(i.first, casas));
        //definirEnLista(make_pair(i.first, lvl), comercios);
        i.second = lvl;
    }
    return comercios1;
}

list<pair<Casilla, Nat>> Simcity::comercios() const{

    if(!_unidos.empty()){
        return mergeComerciosTotales(_casas, _comercios, _unidos);
    }else{
        return actualizarM(_comercios, _casas);
    }

}



list<pair<Casilla, Nat>> Simcity::mergeComerciosTotales(const list<pair<Casilla, Nat>>& casas, const list<pair<Casilla, Nat>>& comercios, const list<Simcity>& unidos) const{
    Nat *turno = new Nat(_turno);
    auto casas1 = casas;
    auto comercios1= comercios;
    auto unidos1 = unidos;

    while(!unidos1.empty()){
        Simcity sc = unidos1.front();
        mergeCasas(casas1, comercios1, sc.casas(), *turno, sc.turno());
        mergeComercios(comercios1, casas1, sc.comercios(), *turno, sc.turno());
        actualizarManhattan(comercios1, casas1);
        if(_turno < sc.turno()){
            *turno = sc.turno();
        }
        unidos1.pop_front();
    }
    delete turno;
    return comercios1;
}


list<pair<Casilla, Nat>> Simcity::mergeCasasTotales(const list<pair<Casilla, Nat>>& casas, const list<pair<Casilla, Nat>>& comercios,
                                               const list<Simcity>& unidos) const {
    Nat *turno = new Nat(_turno);
    auto casas1 = casas;
    auto comercios1= comercios;
    auto unidos1 = unidos;

    while(!unidos1.empty()){
        Simcity sc = unidos1.front();
        mergeCasas(casas1, comercios1, sc.casas(), *turno, sc.turno());
        mergeComercios(comercios1, casas1, sc.comercios(), *turno, sc.turno());
        actualizarManhattan(comercios1, casas1);
        if(_turno < sc.turno()){
            *turno = sc.turno();
        }
        unidos1.pop_front();
    }
    delete turno;
    return casas1;
}

void Simcity::mergeUniones(list<pair<Casilla, Nat>>& casas, list<pair<Casilla, Nat>>& comercios, list<Simcity> & unidos) const{
    Nat *turno = new Nat(_turno);

    while(!unidos.empty()){
        Simcity sc = unidos.front();
        mergeCasas(casas, comercios, sc.casas(), *turno, sc.turno());
        mergeComercios(comercios, casas, sc.comercios(), *turno, sc.turno());
        actualizarManhattan(comercios, casas);
        if(_turno < sc.turno()){
            *turno = sc.turno();
        }
        unidos.pop_front();
    }
    delete turno;

}

/**
 * Casa vs Comercio = Casa
 * Casa vs Casa = Casa de mayor nivel
 * Comercio vs Comercio = Comercio de mayor nivel
 * */
void Simcity::mergeCasas(list<pair<Casilla, Nat>>& casas1, list<pair<Casilla, Nat>>& comercios1, list<pair<Casilla, Nat>> casas2, Nat lvl1, Nat lvl2) const{
    while(!casas2.empty()) {
        pair<Casilla, Nat> casa = casas2.front();
        if (definidoEnLista(casa.first, casas1)) {//Si pisa una casa de s1.
            if (esConstruccionMayor(casas1, casa, lvl1, lvl2)) {
                definirEnLista(casa, casas1);
                casas2.pop_front();
            } else {
                casas2.pop_front();
            }
        } else if (definidoEnLista(casa.first, _comercios)) {//Si pisa un comercio de s1.
            casas1.push_back(casa); //push o emplace?
            borrarEnLista(casa.first, comercios1);
            casas2.pop_front();
        } else {//Si no esta en casas y comercios de s1.
            casas1.push_back(casa);
            casas2.pop_front();
        }
    }
}

void Simcity::mergeComercios(list <pair<Casilla, Nat>> & comercios1, list <pair<Casilla, Nat>> & casas1, list <pair<Casilla, Nat>> comercios2, Nat lvl1, Nat lvl2) const{
    while(!(comercios2.empty())){
        pair<Casilla, Nat> comercio = comercios2.front();
        if(definidoEnLista(comercio.first, comercios1)){
            if(esConstruccionMayor(comercios1, comercio, lvl1, lvl2)){
                definirEnLista(comercio, comercios1);
                comercios2.pop_front();
            }else{
                comercios2.pop_front();
            }
        }else if(definidoEnLista(comercio.first, casas1)){
            comercios2.pop_front();
        }else{
            comercios1.push_back(comercio);
            comercios2.pop_front();
        }
    }
}

bool Simcity::esConstruccionMayor(const list<pair<Casilla, Nat>>& ls, pair<Casilla, Nat> p, Nat lvl1, Nat lvl2) const {
    Nat nivel = obtenerNivelEnLista(p.first, ls);
    return (nivel != lvl1) && (p.second == lvl2 || nivel < p.second);
}

Nat Simcity::popularidad() const{
    return _popularidad;
}

Nat Simcity::turno() const{
    return _turno;
}

bool Simcity::huboConstruccion() const {
    return _huboConstruccion;
}

Nat Simcity::cantUnidos() const{
    return _unidos.size();
}

void Simcity::unir(Simcity sc){
    _huboConstruccion = _huboConstruccion || sc.huboConstruccion();
    _unidos.push_back(sc);
    _popularidad++;
    if(sc.popularidad() > 0){
        _popularidad += sc.popularidad();
    }

    _turno = max(_turno, sc.turno());
    _riosPendientes.push_back(make_pair(sc.mapa().horizontales(), sc.mapa().verticales()));
}

/////////////////////////////////FUNCIONES PRIVADAS/////////////////////////////////

void Simcity::avanzarTurno(){

    if(!_unidos.empty()){
        mergeUniones(_casas, _comercios, _unidos);
    }
    sumarNivel();
    _huboConstruccion = false;
    _turno++;
}

void Simcity::sumarNivel() {
    for(auto & _casa : _casas){
        _casa.second++;
    }
    for(auto & _comercio : _comercios){
        _comercio.second++;
    }

}


bool Simcity::definidoEnLista(Casilla pos, const list<pair<Casilla, Nat>>& cs) const{    //devuelve true si y sólo si el elemento está en la lista
    bool res = false;
    for(pair<Casilla, Nat> i: cs){
        if(pos == i.first){
            res = true;
        }
    }
    return res;
}

void definirSegunMaximo(list<pair<Casilla, Nat>>& res, pair<Casilla, Nat> casa){
    list<pair<Casilla, Nat>>::iterator it;
    for (pair<Casilla, Nat> casa: res){
        while (it != res.end() && it->first != casa.first)  //para en la casilla
            it++;
    }
    if (it == res.end())
        res.push_back(casa);	//define con el nivel indicado
    else
        it->second = max(it->second, casa.second);  //redefine según máx
}

void Simcity::definirEnLista(pair<Casilla, Nat> par, list<pair<Casilla, Nat>>& cs) const{     //si el ele
    bool insertado = false;
    for(auto & p: cs){
        if(par.first == p.first){
            p = par;
            insertado = true;
        }
    }
    if(!insertado) {
        cs.push_back(par);
    }
}

void Simcity::borrarEnLista(Casilla pos, list<pair<Casilla, Nat>>& cs) const{
    list<pair<Casilla,Nat>> res;
    for(auto& i: cs){
        if(pos != i.first){
            res.push_back(i);
        }
    }
    cs = res;
}

Nat Simcity::obtenerNivelEnLista(Casilla pos, list<pair<Casilla, Nat>> cs) const{
    Nat res = 0;
    for(auto i: cs){
        if(i.first == pos){
            res=i.second;
        }
    }
    return res;
}

void Simcity::actualizarManhattan(list<pair<Casilla, Nat>>& comercios, const list<pair<Casilla, Nat>>& casas)const{
    for(auto & i : comercios){
        Nat lvl= max(i.second, maxNivelManhattan(i.first, casas));
        //definirEnLista(make_pair(i.first, lvl), comercios);
        i.second = lvl;
    }
}

Nat Simcity::maxNivelManhattan(Casilla pos, list<pair<Casilla, Nat>> cs)const{
    Nat res = 0;
    for(auto i : cs){
        if(esManhattan(pos, i.first)){
            if(i.second>res){
                res = i.second;
            }
        }
    }
    return res;
}

bool Simcity::esManhattan(Casilla pos1, Casilla pos2)const{
    bool res = false;
    if((abs(pos1.first-pos2.first) +  abs(pos1.second-pos2.second))<=3){
        res = true;
    }
    return res;
}



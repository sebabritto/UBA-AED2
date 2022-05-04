#ifndef SOLUCION_DICCIONARIO_HPP
#define SOLUCION_DICCIONARIO_HPP
////////////////////////////////////Ejercicio_5////////////////////////////////////
template<class Clave, class Valor>
class Diccionario {
public:
    Diccionario();
    void definir(Clave k, Valor v);
    bool def(Clave k) const;
    Valor obtener(Clave k) const;
    std::vector<Clave> claves() const; //Ejercicio 8
private:

    struct Asociacion {
        Asociacion(Clave k, Valor v);
        Clave clave;
        Valor valor;
    };
    std::vector<Asociacion> _asociaciones;
};

template<class Clave, class Valor>
Diccionario<Clave,Valor>::Diccionario() {
}

template<class Clave, class Valor>
Diccionario<Clave,Valor>::Asociacion::Asociacion(Clave k, Valor v) : clave(k), valor(v) {
}

template<class Clave, class Valor>
void Diccionario<Clave,Valor>::definir(Clave k, Valor v) {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            _asociaciones[i].valor = v;
            return;
        }
    }
    _asociaciones.push_back(Asociacion(k, v));
}

template<class Clave, class Valor>
bool Diccionario<Clave,Valor>::def(Clave k) const {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            return true;
        }
    }
    return false;
}

template<class Clave, class Valor>
Valor Diccionario<Clave,Valor>::obtener(Clave k) const {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            return _asociaciones[i].valor;
        }
    }
    assert(false);
}

////////////////////////////////////Ejercicio_8////////////////////////////////////
template<class Clave>
Clave minimo(std::vector<Clave> cl){
    Clave min = cl[0];
    for(int i = 1; i < cl.size(); i++){
        if(cl[i] < min){
            min = cl[i];
        }
    }
    return min;
}
template<class Clave>
void eliminar(std::vector<Clave> &v, Clave c){
    std::vector<Clave> res;
    for(int i = 0; i < v.size(); i++){
        if(v[i] != c){
            res.push_back(v[i]);
        }
    }
    v = res;
}
template<class Clave, class Valor>
std::vector<Clave> Diccionario<Clave, Valor>::claves() const {
    std::vector<Clave> v1;
    std::vector<Clave> v2;
    for(int i = 0; i < _asociaciones.size(); i++){
        v1.push_back(_asociaciones[i].clave);
    }

    while(!v1.empty()){
        Clave min = v1[0];
        for(int i = 1; i < v1.size(); i++){
            if(v1[i] < min){
                min = v1[i];
            }
        }
        v2.push_back(min);
        eliminar(v1, min);
    }
    /*while(!v1.empty()){
        Clave min = minimo(v1);
        v2.push_back(min);
        eliminar(v1, min);
    }*/


    return v2;
}




#endif //SOLUCION_DICCIONARIO_HPP

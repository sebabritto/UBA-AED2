#ifndef SOLUCION_MULTICONJUNTO_HPP
#define SOLUCION_MULTICONJUNTO_HPP
#include "Diccionario.hpp"
////////////////////////////////////Ejercicio_7////////////////////////////////////
template<class T>
class Multiconjunto{
public:
    Multiconjunto();
    void agregar(T x);
    int ocurrencias(T x) const;
    bool operator<=(Multiconjunto<T> m); //Ejercicio 9
private:
    Diccionario<T, int> _dicc;
};

template<class T>
Multiconjunto<T>::Multiconjunto() {}

template<class T>
void Multiconjunto<T>::agregar(T x) {
    if(!_dicc.def(x)){
        _dicc.definir(x, 1);
    }else{
        _dicc.definir(x, _dicc.obtener(x) + 1);
    }
}

template<class T>
int Multiconjunto<T>::ocurrencias(T x) const{
    if(!_dicc.def(x)){
        return 0;
    }else{
        return _dicc.obtener(x);
    }
}
////////////////////////////////////Ejercicio_9////////////////////////////////////
template<class T>
bool Multiconjunto<T>::operator<=(Multiconjunto<T> m) {
    std::vector<T> v1 = this->_dicc.claves();
    for(int i = 0; i < v1.size(); i++){
        if(this->ocurrencias(v1[i]) > m.ocurrencias(v1[i])){
            return false;
        }
    }
    return true;
}
#endif //SOLUCION_MULTICONJUNTO_HPP

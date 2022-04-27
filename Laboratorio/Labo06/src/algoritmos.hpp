#ifndef ALGO2_LABO_CLASE5_ALGORITMOS_H
#define ALGO2_LABO_CLASE5_ALGORITMOS_H

#include <utility>
#include <iterator>
#include <vector>

// Completar con las funciones del enunciado

/////////////////////////////////EJERCICIO_1/////////////////////////////////
#if EJ < 8
template<class Contenedor>
typename Contenedor::value_type minimo(const Contenedor& c){
    //Contendedor::const_iterator it = c.begin();
    typename Contenedor::value_type min = *(c.begin());
    //typename Contenedor::const_iterator it1 = c.begin();
    auto it1 = c.begin();
    while(it1 != c.end()){
        typename Contenedor::const_iterator it2 = c.begin();
        while(it2 != c.end()){
            if(min > *it2){
                min = *it2;
            }
            ++it2;
        }
        ++it1;
    }
    return min;
}
#endif
/////////////////////////////////EJERCICIO_2/////////////////////////////////
template<class Contenedor>
typename Contenedor::value_type promedio(const Contenedor& c){
    typename Contenedor::const_iterator it = c.begin();
    int cont = 0;
    typename Contenedor::value_type suma = 0;
    while(it != c.end()){
        suma += *(it);
        cont++;
        ++it;
    }
    return suma / cont;
}

/////////////////////////////////EJERCICIO_3/////////////////////////////////
template<class Iterator>
typename Iterator::value_type minimoIter(const Iterator& desde, const Iterator& hasta){
    auto it1 = desde;
    auto min = it1;
    //auto ir = it1;
    //ir++;
    /*while(it1 != hasta){
        auto it2 = desde;
        while(it2 != hasta){
            if(*min > *it2){
                min = it2;
            }
            ++it2;
        }
        ++it1;
    }*/
    while(it1 != hasta){
        auto ir = it1;
        ir++;
        while(ir != hasta){
            if(*min > *ir){
                min = ir;
            }
            ++ir;
        }
        ++it1;
    }
    return *min;
}

template<class Iterator>
typename Iterator::value_type promedioIter(const Iterator& desde, const Iterator& hasta){
    Iterator it = desde;
    int cont = 0;
    typename Iterator::value_type suma = 0;
    while(it != hasta){
        suma += *it;
        cont++;
        ++it;
    }
    return suma / cont;
}

/////////////////////////////////EJERCICIO_4/////////////////////////////////
template<class Contenedor>
void filtrar(Contenedor &c, const typename Contenedor::value_type& elem){
    typename Contenedor::const_iterator it = c.begin();
    //auto it = c.begin();
    while(it != c.end()){
        if(*it == elem){
            it = c.erase(it);
        }else{
            ++it;
        }
    }
}
/////////////////////////////////EJERCICIO_5/////////////////////////////////
template<class Contenedor>
bool ordenado(Contenedor &c){
    typename Contenedor::const_iterator it = c.begin();
    //auto it = c.begin();
    typename Contenedor::value_type ant = *it;
    while(it != c.end()){
        if(ant > *it){
            return false;
        }
        ++it;
    }
    return true;
}
/////////////////////////////////EJERCICIO_6/////////////////////////////////
template<class Contenedor>
std::pair<Contenedor, Contenedor> split(const Contenedor &c,
                                        const typename Contenedor::value_type &elem){
    Contenedor menor;
    Contenedor mayor;
    typename Contenedor::const_iterator itMenor = menor.end();
    typename Contenedor::const_iterator itMayor = mayor.end();
    typename Contenedor::const_iterator it = c.begin();
    while(it != c.end()){
        if(*it < elem){
            menor.insert(itMenor, *it);
            itMenor = menor.end();
        }else{
            mayor.insert(itMayor, *it);
            itMayor = mayor.end();
        }
        ++it;
    }
    return std::make_pair(menor, mayor);
}

/////////////////////////////////EJERCICIO_7/////////////////////////////////
template<class Contenedor>
void merge(const Contenedor& c1, const Contenedor& c2, Contenedor &res){
    Contenedor cl = c1;
    Contenedor ck = c2;
    typename Contenedor::iterator itL = cl.begin();
    typename Contenedor::iterator itK = ck.begin();
    while(itL != cl.end() || itK != ck.end()){
        if (itL == cl.end()){
            res.insert(res.end(), *itK);
            itK = ck.erase(itK);
        }else if(itK == ck.end()){
            res.insert(res.end(), *itL);
            itL = cl.erase(itL);
        }else {
            if (*itL < *itK) {
                res.insert(res.end(), *itL);
                itL = cl.erase(itL);
            }else{
                res.insert(res.end(), *itK);
                itK = ck.erase(itK);
            }
        }
    }
}

/////////////////////////////////EJERCICIO_8/////////////////////////////////
#if EJ == 8
template<class Contenedor>
typename Contenedor::value_type minimo(const Contenedor& c){

    auto it1 = c.begin();
    auto min = it1;
    while(it1 != c.end()){
        auto it2 = c.begin();
        while(it2 != c.end()){
            if(*min > *it2){
                min = it2;
            }
            ++it2;
        }
        ++it1;
    }
    return *min;
}
#endif
#endif //ALGO2_LABO_CLASE5_ALGORITMOS_H

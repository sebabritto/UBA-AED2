#ifndef SOLUCION_TEMPLATES_HPP
#define SOLUCION_TEMPLATES_HPP

////////////////////////////////////Ejercicio_1////////////////////////////////////
template<class T>
T cuadrado(T t1){
    return t1*t1;
}
////////////////////////////////////Ejercicio_2////////////////////////////////////
template<class Contenedor, class Elem>
bool contiene(Contenedor c, Elem e){
    typename Contenedor::iterator i = c.begin();
    while(i != c.end()){
        if(*i == e){
            return true;
        }else{
            i++;
        }
    }
    /*for(typename Contenedor::value_type n: c){
        if(n == e){
            return true;
        }
    }
    for(int j = 0; j < c.size(); j++){
        if(c[j] == e){
            return true;
        }
    }*/
    return false;
}
////////////////////////////////////Ejercicio_3////////////////////////////////////
template<class Contenedor>
bool esPrefijo(Contenedor a, Contenedor b){
    for(int i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}

////////////////////////////////////Ejercicio_4////////////////////////////////////
template<class Contenedor, class Elem>
Elem maximo(const Contenedor &c){
    Elem max = c[0];
    //typename Contenedor::value_type max = c[0];
    /*typename Contenedor::iterator it = c.begin();
    while(it != c.end()){
        if(max < *it){
            max = *it;
        }
        it++;
    }*/
    for(int i = 1; i < c.size(); i++){
        if(max < c[i]){
            max = c[i];
        }
    }
    return max;
}
#endif //SOLUCION_TEMPLATES_HPP

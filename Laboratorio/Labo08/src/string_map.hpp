
#include "string_map.h"

template <typename T>
string_map<T>::string_map(){
    raiz = new Nodo();
    _size = 0;
}

template <typename T>
string_map<T>::~string_map(){
    eliminar(raiz);
}

template<class T>
void string_map<T>::eliminar(Nodo * n) {
    if(n != nullptr){
        eliminarHijos(n->siguientes);
        delete n->definicion;
        delete n;
    }
}

template<class T>
void string_map<T>::eliminarHijos(vector<Nodo *> v) {
    for(int i = 0; i < v.size(); i++){
        if(v[i] != nullptr){
            eliminar(v[i]);
        }
    }
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;
} // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {

    eliminar(raiz);
    this->raiz = new Nodo();
    if(d.size() != 0){
        copiar(this->raiz->siguientes, d.raiz->siguientes);
    }
    this->_size = d.size();
    return *this;
}

template<typename T>
void string_map<T>::copiar(vector<Nodo *>& v1, vector<Nodo*> v2) {
    for(int i = 0 ; i < v2.size(); i++){
        if(v2[i] != nullptr){
            v1[i] = new Nodo();
            if(v2[i]->definicion != nullptr){
                T *def = new T(*v2[i]->definicion);
                v1[i]->definicion = def;
            }
            copiar(v1[i]->siguientes, v2[i]->siguientes);
        }
    }
}

template<typename T>
void string_map<T>::insert(const pair<string, T>& p) {

    //T *def = new T(p.second);
    Nodo* nuevo = raiz;
    for(char c: p.first){
        int i = int(c);
        if(nuevo->siguientes[i] == nullptr){
            nuevo->siguientes[i] = new Nodo();
        }
        nuevo = nuevo->siguientes[i];
    }
    if(count(p.first)){
        delete nuevo->definicion;
    }
    T *def = new T(p.second);
    nuevo->definicion = def;
    _size++;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    Nodo* recorrer = raiz;
    for(char c: clave){
        int i = int(c);
        if(recorrer->siguientes[i] == nullptr){
            recorrer->siguientes[i] = new Nodo();
        }
        recorrer = recorrer->siguientes[i];
    }
    if(recorrer->definicion == nullptr){
        recorrer->definicion = new T();
    }
    return *recorrer->definicion;
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    Nodo* nuevo = raiz;
    for(char c: clave){
        int i = int(c);
        if(nuevo->siguientes[i] == nullptr){
            return 0;
        }else{
            nuevo = nuevo->siguientes[i];
        }
    }
    if(nuevo->definicion != nullptr){
        return 1;
    }else{
        return 0;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    //Precondicion: La clave esta definida.
    Nodo* nuevo = raiz;
    for(char c: clave){
        int i = int(c);
        nuevo = nuevo->siguientes[i];
    }
    return (nuevo->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    //Precondicion: La clave esta definida.
    Nodo* nuevo = raiz;
    for(char c: clave){
        int i = int(c);
        nuevo = nuevo->siguientes[i];
    }
    return *(nuevo->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    //Precondicion: la clave esta definida
    borrar(raiz, clave, 0);
}

//c a s a s
//- - - o
//- - - - n a
/*template<typename T>
void string_map<T>::borrarBis(string clave) {
    for(){

    }
}*/

template<typename T>
void string_map<T>::borrar(Nodo *n, string clave, int d) {
    bool tieneHijos = false;
    if(clave.length() == d){ //0
        int cant2 = 0;
        for(int i = 0 ; i < n->siguientes.size(); i++){ //Recorro los hijos.
            if(n->siguientes[i] != nullptr){
                cant2++;
            }
        }
        delete n->definicion;
        n->definicion = nullptr;
        if(cant2 == 0){ //No tiene hijos
            n = nullptr;
            delete n;
        }else{          //Tiene hijos
            tieneHijos = true;
        }
    }else{
        char c = clave[d];
        int i = int(c);
        borrar(n->siguientes[i], clave, d+1);
        int cant = 0;
        for(int i = 0 ; i < n->siguientes.size(); i++){
            if(n->siguientes[i] != nullptr){
                cant++;
            }
        }
        if(cant == 0 && n->definicion == nullptr){
            delete n->definicion;
            n = nullptr;
            delete n;

        }
    }
}



template <typename T>
int string_map<T>::size() const{
    return this->_size;
}

template <typename T>
bool string_map<T>::empty() const{
    return (_size == 0);
}



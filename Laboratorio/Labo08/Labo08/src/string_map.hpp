template <typename T>
string_map<T>::string_map(){
    raiz = nullptr;
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
}

template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if(raiz->siguientes.empty()){
        return 0;
    }else{
        return contAux(clave, raiz->siguientes);
    }
}
template<typename T>
int string_map<T>::contAux(const string &clave, vector<Nodo*> n) {
    if(n.empty()){
        return 0;
    }else{
        for(int it = n.begin(); it != n.end(); it++){
            if(n[it] == clave[0]){
                if(clave.size() == 1){
                    return 1;
                }else{
                    contAux(clave.substr(1, clave.size()-1), n[it]->siguientes);
                }
            }
        }
        return 0;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // COMPLETAR
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    // COMPLETAR
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    // COMPLETAR
}

template <typename T>
int string_map<T>::size() const{
    // COMPLETAR
}

template <typename T>
bool string_map<T>::empty() const{
    // COMPLETAR

    return raiz->siguientes.empty();
    /*bool res = false;
    for(int it = raiz->siguientes.begin(); it != raiz->siguientes.end(); ){

    }*/
}
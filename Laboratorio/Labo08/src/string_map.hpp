template <typename T>
string_map<T>::string_map(){
    raiz = nullptr;
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;
} // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
}

template <typename T>
string_map<T>::~string_map(){
    eliminarHijos(raiz->siguientes);
}

template<class T>
void string_map<T>::eliminarHijos(vector<Nodo *> v) {
    for(int it = 0; it < v.size(); it++){
        if(v[it]->siguientes.empty()){
            delete v[it];
        }else{
            eliminarHijos(v[it]->siguientes);
            delete v[it];
        }
    }
}

template<class T>
void string_map<T>::eliminarNodo(Nodo * n) {
    /*if(n->siguientes.empty()){
        delete n;
    }else{

    }*/
}
template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    string key = clave;
    return countAux(raiz->siguientes, key);
}

template<typename T>
int string_map<T>::countAux(vector<Nodo*> v, string& clave) const {
    for(int i = 0; i < v.size(); i++){
        if(*v[i] == clave[0]){
            if(clave.size() == 1){
                return 1;
            }else{
                return countAux(v[i]->siguientes, clave.substr(1, clave.size()-1));
            }
        }
    }
    return 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // COMPLETAR
}

template <typename T>
T& string_map<T>::at(const string& clave) {

}

/*template<typename T>
T& string_map<T>::atAux(vector<Nodo *> v, const string &clave) {
    int i = 0;
    while(v[i] )
}*/

template <typename T>
void string_map<T>::erase(const string& clave) {
    // COMPLETAR
}

template <typename T>
int string_map<T>::size() const{
    return this->_size;
}

template <typename T>
bool string_map<T>::empty() const{
    return raiz->siguientes.empty();
}
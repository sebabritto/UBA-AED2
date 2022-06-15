template <typename T>
string_map<T>::string_map(){
    raiz = new Nodo();
    _size = 0;
}

template <typename T>
string_map<T>::~string_map(){
    eliminarHijos(raiz->siguientes);
    delete raiz;
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

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;
} // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    if(this != &d){
        this->~string_map();
        if(d._size != 0){
            this->raiz = d.raiz;
        }
    }
    return *this;
}

template<typename T>
void string_map<T>::insert(const pair<string, T>& p) {
    T *def = new T(p.second);
    Nodo* nuevo = raiz;
    for(char c: p.first){
        int i = int(c);
        if(nuevo->siguientes[i] == nullptr){
            nuevo->siguientes[i] = new Nodo();
        }
        nuevo = nuevo->siguientes[i];
    }
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
    return *(recorrer->definicion);
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
    return 1;
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
    // COMPLETAR
}

template <typename T>
int string_map<T>::size() const{
    return this->_size;
}

template <typename T>
bool string_map<T>::empty() const{
    return (_size == 0);
}
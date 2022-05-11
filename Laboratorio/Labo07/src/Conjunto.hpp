
#include "Conjunto.h"
#include <stack>

template <class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
}

template <class T>
Conjunto<T>::~Conjunto() {
    eliminar(_raiz);
}

template<class T>
void Conjunto<T>::eliminar(Conjunto::Nodo *n) {
    if(n != nullptr){
        eliminar(n->izq);
        eliminar(n->der);
        delete n;
    }
}


template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* recorrer = _raiz;
    if(recorrer == nullptr){
        return false;
    }else{
        if(clave == recorrer->valor){
            return true;
        }else{
            while(recorrer != nullptr){
                if(clave == recorrer->valor){
                    return true;
                }else if(clave < recorrer->valor){
                    recorrer = recorrer->izq;
                }else{
                    recorrer = recorrer->der;
                }
            }
        }
    }

    //assert(false);
    return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {

    if(_raiz == nullptr){
        _raiz = new Nodo(clave);
    }else{
        Nodo* recorrer = _raiz;
        while(!this->pertenece(clave) /*recorrer->der->valor != clave || recorrer->izq->valor != clave */){
            if(clave < recorrer->valor){
                if(recorrer->izq == nullptr){
                    recorrer->izq = new Nodo(clave);
                }else{
                    recorrer = recorrer->izq;
                }
            }else{
                if(recorrer->der == nullptr){
                    recorrer->der = new Nodo(clave);
                }else{
                    recorrer = recorrer->der;
                }
            }
        }
    }
    //assert(false);
}
template<class T>
void Conjunto<T>::removerNodo(Nodo *padre, Nodo *nodo, std::string dir,const T& clave) {
    if(nodo->valor == clave){
        if(nodo->der == nullptr && nodo->izq == nullptr){
            delete nodo;
            if(dir == "IZQ"){
                padre->izq = nullptr;
            }else{
                padre->der = nullptr;
            }
        }else{
            if(nodo->der != nullptr){
                nodo->valor = minimo(nodo->der);
                removerNodo(nodo, nodo->der,"DER", nodo->valor);
            }else{
                nodo->valor = maximo(nodo->izq);
                removerNodo(nodo, nodo->izq,"IZQ", nodo->valor);
            }
        }
    }else{
        if(nodo->valor > clave){
            removerNodo(nodo,  nodo->izq, "IZQ",clave);
        }else{
            removerNodo(nodo, nodo->der, "DER", clave);
        }
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(cardinal() == 1 && clave == _raiz->valor){
        delete _raiz;
        _raiz = nullptr;
    }else{
        removerNodo(nullptr, _raiz, "", clave);
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* recorrer = _raiz;
    if(clave == recorrer->valor){
        if(recorrer->der != nullptr){
            return minimo(recorrer->der);
        }
    }else{
        while(recorrer->valor != clave){
            if(clave < recorrer->valor){
                if(recorrer->izq->valor == clave && recorrer->izq->izq == nullptr && recorrer->izq->der == nullptr){
                    return recorrer->valor;
                }else{
                    recorrer = recorrer->izq;
                }
            }else{
                recorrer = recorrer->der;
            }
        }
        return minimo(recorrer->der);
    }
    //assert(false);
}

template<class T>
const T &Conjunto<T>::minimo(Nodo *n) const {
    Nodo* recorrer = n;
    while(recorrer != nullptr){
        if(recorrer->izq == nullptr){
            return recorrer->valor;
        }else{
            recorrer = recorrer->izq;
        }
    }
    return recorrer->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    return minimo(_raiz);
    //assert(false);
}

template<class T>
const T &Conjunto<T>::maximo(Nodo *n) const {
    Nodo* recorrer = n;
    while(recorrer != nullptr){
        if(recorrer->der == nullptr){
            return recorrer->valor;
        }else{
            recorrer = recorrer->der;
        }
    }
    return recorrer->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return maximo(_raiz);
    //assert(false);
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return cardinalNodo(_raiz);
}

template<class T>
unsigned int Conjunto<T>::cardinalNodo(Nodo *n) const{
    if (n == nullptr) return 0;
    if(n->izq == nullptr && n->der == nullptr){
        return 1;
    }else{
        if(n->der == nullptr){
            return 1 + cardinalNodo(n->izq);
        }else if(n->izq == nullptr){
            return 1 + cardinalNodo(n->der);
        }else{
            return 1 + cardinalNodo(n->izq) + cardinalNodo(n->der);
        }
    }
    return 0;
}


template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {
    /*Conjunto<T> copia = *this;
    Nodo *recorrer = copia._raiz;
    os << "[";
    while(recorrer != nullptr){
        if(recorrer->izq != nullptr){
            os << minimo(recorrer->izq) << ", ";
            remover(minimo(recorrer->izq));
        }else{
            if(recorrer->der != nullptr){
                os << recorrer->valor << ", ";
                remover(recorrer->valor);
            }else{
                os << recorrer->valor;
                recorrer = nullptr;
            }
        }
    }
    os << "]";*/
    stack<Nodo*> s;
    Nodo* actual = _raiz;
    os << "[";
    while(actual != nullptr || s.empty() == false){
        while(actual != nullptr){
            s.push(actual);
            actual = actual->izq;
        }
        actual = s.top();
        s.pop();
        if(actual->izq == nullptr && actual->der == nullptr && s.empty()){
            os << actual->valor;
        }else{
            os << actual->valor << ", ";
        }
        actual = actual->der;
    }
    os << "]";
    //assert(false);
}









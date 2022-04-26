#include "Lista.h"

Lista::Lista() {
    // Completar
    this->tam = 0;
    this->primero = nullptr;
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    // Completar
    Nodo* temp = primero;
    while(temp != nullptr){
        temp = temp->siguiente;
        delete primero;
        primero = temp;
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Completar
    if(this != &aCopiar){
        tam = 0;
        if(aCopiar.tam == 0){
            primero = nullptr;
        }else{
            this->~Lista();
            Nodo* recorrer = aCopiar.primero;
            while(recorrer != nullptr){
                this->agregarAtras(recorrer->dato);
                recorrer = recorrer->siguiente;
            }
        }
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    // Completar
    Nodo* nuevo = new Nodo();
    nuevo->dato = elem;
    nuevo->siguiente = primero;
    primero = nuevo;
    if(tam != 0){
        primero->anterior = nuevo;
    }
    tam++;
}

void Lista::agregarAtras(const int& elem) {
    // Completar
    Nodo* nuevo = new Nodo();
    nuevo->dato = elem;
    if(tam == 0) {
        primero = nuevo;
    }else{
        Nodo* ultimo = primero;
        //Nodo* ant = ultimo->anterior;
        while(ultimo->siguiente != nullptr){
            ultimo = ultimo->siguiente;
        }
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
    }
    tam++;
}

void Lista::eliminar(Nat i) {
    // Completar

    if(i == 0 && tam == 1){
        delete primero;
        primero = nullptr;
    }else{
        Nodo* recorrer = primero;
        Nodo* ant = recorrer->anterior;
        Nodo* sig = recorrer->siguiente;
        int size = 0;
        while(recorrer != nullptr){
            if(i == 0){
                delete recorrer;
                recorrer = nullptr;
                primero = sig;
                primero->anterior = nullptr;
            }else if(size == i){
                if(size == tam-1){
                    delete recorrer;
                    recorrer = nullptr;
                    ant->siguiente = nullptr;
                }else{
                    ant->siguiente = sig;
                    sig->anterior = ant;
                    delete recorrer;
                    recorrer = nullptr;
                }
            }else{
                ant = recorrer;
                recorrer = recorrer->siguiente;
                sig = recorrer->siguiente;
            }
            size++;
        }
    }
     tam--;
}

int Lista::longitud() const {
    // Completar
    return tam;
}

const int& Lista::iesimo(Nat i) const {
    // Completar
    int size = 0;
    Nodo* recorrer = primero;
    while(recorrer != nullptr){
        if(size == i){
            return recorrer->dato;
        }else{
            size++;
            recorrer = recorrer->siguiente;
        }
    }
    //assert(false);
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    int size = 0;
    Nodo* recorrer = primero;
    while(recorrer != nullptr){
        if(size == i){
            return recorrer->dato;
        }else{
            size++;
            recorrer = recorrer->siguiente;
        }
    }
}

void Lista::mostrar(ostream& o) {
    // Completar
    Nodo* recorrer = primero;
    o << "[";
    while(recorrer != nullptr){
        o << recorrer->dato << ", ";
        recorrer = recorrer->siguiente;
    }
    o << "]";
}

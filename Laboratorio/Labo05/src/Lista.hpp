#include "Lista.h"

Lista::Lista() {
    this->tam = 0;
    this->primero = nullptr;
    this->ultimo = nullptr;
}


Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    Nodo* temp = primero;
    while(temp != nullptr){
        temp = temp->siguiente;
        delete primero;
        primero = temp;
        tam--;
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    if(this != &aCopiar){
        this->~Lista();
        if(aCopiar.tam != 0){
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
    Nodo* nuevo = new Nodo();
    nuevo->dato = elem;
    if(tam == 0){
        primero = nuevo;
        ultimo = nuevo;
    }else{
        primero->anterior = nuevo;
        nuevo->siguiente = primero;
        primero = nuevo;
    }
    tam++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = elem;
    if(tam == 0){
        primero = nuevo;
        ultimo = nuevo;
    }else{
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        ultimo = nuevo;
    }
    tam++;
}

void Lista::eliminar(Nat i) {
    if(i == 0 && tam == 1){
        delete primero;
        primero = nullptr;
        ultimo = nullptr;
    }else{
        Nodo* recorrer = primero;
        Nat size = 0;
        while(recorrer != nullptr){
            if(i == 0){
                primero = primero->siguiente;
                delete recorrer;
                recorrer = nullptr;
            }else if(i == size){
                if(i == tam - 1){
                   ultimo = ultimo->anterior;
                   delete recorrer;
                   recorrer = nullptr;
                }else{
                    recorrer->siguiente->anterior = recorrer->anterior;
                    recorrer->anterior->siguiente = recorrer->siguiente;
                    delete recorrer;
                    recorrer = nullptr;
                }
            }else{
                recorrer = recorrer->siguiente;
            }
            size++;
        }
    }
    tam--;
}


int Lista::longitud() const {
    return tam;
}

const int& Lista::iesimo(Nat i) const {
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
    assert(false);
    //return recorrer->dato;
}

int& Lista::iesimo(Nat i) {
    // (hint: es igual a la anterior...)
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
    assert(false);
    //return recorrer->dato;
}

void Lista::mostrar(ostream& o) {

    Nodo* recorrer = primero;
    o << "[";
    while(recorrer != nullptr){
        o << recorrer->dato << ", ";
        recorrer = recorrer->siguiente;
    }
    o << "]";
}

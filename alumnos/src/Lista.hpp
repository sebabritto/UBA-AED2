#include "Lista.h"

Lista::Lista() {
    // Completar
    this->tam = 0;
    this->primero = nullptr;
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
    Lista* res = new Lista();
    Nodo* prim = aCopiar.primero;
    Nodo* sig = prim->siguiente;
    while(prim != nullptr){
        res->primero = prim;
        prim = sig;
        sig = sig->siguiente;
    }
    return *res;

}
//{1}->{2}->{3}->
//{1}->{N}
//{N}
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




     /*Lista* res = new Lista();
     Nodo* recorrer = primero;
     int size = 0;
     while(recorrer != nullptr){
        if(size == i){
            recorrer = recorrer->siguiente;
        }else{
            res->agregarAtras(recorrer->dato);
            recorrer = recorrer->siguiente;
            size++;
        }
     }*/

     tam--;
}
//{1}->{2}->{3}->
//{1}->{3}
//{N}
int Lista::longitud() const {
    // Completar
    int aver = tam;
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
            recorrer->siguiente;
        }
    }

    //assert(false);
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    int size = 0;
    Nodo* recorrer = primero;
    int valor = 0;
    while(recorrer != nullptr){
        int valor = recorrer->dato;
        if(size == i){
            valor = recorrer->dato;
            return recorrer->dato;
        }else{
            size++;
            recorrer = recorrer->siguiente;
        }
    }
    int otrovalor = recorrer->dato;
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

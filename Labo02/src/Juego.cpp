#include <utility>
#include <list>

using namespace std;
using uint = unsigned int;
using Pos = pair<int, int>;

char ARRIBA = '^';
char ABAJO = 'v';
char DERECHA = '<';
char IZQUIERDA = '>';

// Ejercicio 15

//Hago la clase pocion, me va a facilitar las cosas

class Pocion{
public:
    Pocion(uint movimientos, uint turnos);
    uint movimientos();
    uint turnos();
    void proximo_turno();
private:
    uint movimientos_;
    uint turnos_;
};

Pocion::Pocion(uint movimientos, uint turnos) : movimientos_(movimientos), turnos_(turnos){}

uint Pocion::movimientos() {
    return this->movimientos_;
}

uint Pocion::turnos() {
    return this->turnos_;
}

void Pocion::proximo_turno() {
    this->turnos_--;
}

// Juego

class Juego {
  // Completar
public:
  Juego(uint casilleros, Pos pos_inicial);
  Pos posicion_jugador();
  uint turno_actual();
  void mover_jugador(char dir);
  void ingerir_pocion(uint movimientos, uint turnos);

private:
    uint turno_actual_;
    uint casilleros_;
    Pos pos_actual_;
    list<Pocion> pociones_;
    uint movimientos_realizados;
    uint movimientos_disponibles();
    void proximo_turno();
};

Juego::Juego(uint casilleros, Pos pos_inicial) :
casilleros_(casilleros), pos_actual_(pos_inicial), turno_actual_(0), movimientos_realizados(0) {}

Pos Juego::posicion_jugador() {
    return pos_actual_;
}

uint Juego::turno_actual() {
    return turno_actual_;
}

void Juego::mover_jugador(char dir) {
    bool jugada_valida = false;
    if(dir == ARRIBA && pos_actual_.first != 0){
        pos_actual_.first--;
        jugada_valida = true;
    }else if(dir == ABAJO && pos_actual_.first != this->casilleros_-1){
        pos_actual_.first++;
        jugada_valida = true;
    }else if(dir == DERECHA && pos_actual_.second != this->casilleros_-1){
        pos_actual_.second++;
        jugada_valida = true;
    }else if(dir == IZQUIERDA && pos_actual_.second != 0){
        pos_actual_.second--;
        jugada_valida = true;
    }
    if(jugada_valida){
        movimientos_realizados++;
        if(movimientos_realizados == movimientos_disponibles()){
            this->proximo_turno();
        }
    }
}

void Juego::ingerir_pocion(uint movimientos, uint turnos) {
    this->pociones_.push_back(Pocion(movimientos, turnos));
}

uint Juego::movimientos_disponibles() {
    if (this->pociones_.empty()) {
        return 1;
    }
    uint res = 0;
    for (auto p: pociones_) {
        res += p.movimientos();
    }
    return res;
}

void Juego::proximo_turno() {
    this->turno_actual_++;
    this->movimientos_realizados = 0;
    list<Pocion> res;
    for(auto p: pociones_){
        p.proximo_turno();
        if(p.turnos() != 0){
            res.push_back(p);
        }
    }
    this->pociones_ = res;
}

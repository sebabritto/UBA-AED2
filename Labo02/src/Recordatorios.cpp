#include <iostream>
#include <list>
using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
            // ene, feb, mar, abr, may, jun
            31, 28, 31, 30, 31, 30,
            // jul, ago, sep, oct, nov, dic
            31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
public:
    // Completar declaraciones funciones
    Fecha(uint mes, uint dia);
    uint mes();
    uint dia();
    void incrementar_dia();
#if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
#endif

private:
    //Completar miembros internos
    uint mes_;
    uint dia_;
};

Fecha::Fecha(uint mes, uint dia) : mes_(mes), dia_(dia) {}

uint Fecha::mes() {
    return this->mes_;
}

uint Fecha::dia(){
    return this->dia_;
}

void Fecha::incrementar_dia() {
    if(this->dia() == dias_en_mes(this->mes())){
        this->dia_ = 1;
        this->mes_++;
    }else{
        this->dia_++;
    }
}

ostream& operator<<(ostream& os, Fecha f){
    os << f.dia() << "/" << f.mes();
    return os;
}


#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia();
    // Completar iguadad (ej 9)
    bool igual_mes = this->mes() == o.mes();
    return igual_dia && igual_mes;
}
#endif

// Ejercicio 11, 12

// Clase Horario
class Horario{
public:
    Horario(uint hora, uint min);
    uint hora();
    uint min();
    bool operator==(Horario h);
    bool operator<(Horario h);
private:
    uint hora_;
    uint min_;
};

Horario::Horario(uint hora, uint min) : hora_(hora), min_(min){}

uint Horario::hora() {
    return hora_;
}

uint Horario::min() {
    return min_;
}

ostream& operator<<(ostream& os, Horario h){
    os << h.hora() << ":" << h.min();
    return os;
}

bool Horario::operator==(Horario h){
    bool igual_hora = this->hora() == h.hora();
    bool igual_min = this->min() == h.min();
    return igual_hora && igual_min;
}

bool Horario::operator<(Horario h) {
    return (this->hora() < h.hora()) ||
           (this->hora() == h.hora() && this->min() < h.min());
}


// Ejercicio 13

// Clase Recordatorio
class Recordatorio{
public:
    Recordatorio(Fecha f, Horario h, string mensaje);
    string mensaje();
    Fecha fecha();
    Horario horario();
    //bool operator<(Recordatorio r);
private:
    Fecha f_;
    Horario h_;
    string mensaje_;
};

string Recordatorio::mensaje() {
    return this->mensaje_;
}

Fecha Recordatorio::fecha() {
    return this->f_;
}

Horario Recordatorio::horario() {
    return this->h_;
}

Recordatorio::Recordatorio(Fecha f, Horario h, string mensaje) :
        f_(f) , h_(h), mensaje_(mensaje) {}

ostream& operator<<(ostream& os, Recordatorio r){
    os << r.mensaje() << " @ " << r.fecha() << " " << r.horario();
    return os;
}

/*bool Recordatorio::operator<(Recordatorio r) {
    return this->horario() < r.horario();
}*/
// Ejercicio 14

// Clase Agenda

class Agenda{
public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();

private:
    Fecha fecha_;
    list<Recordatorio> rec_de_hoy_;
};

Agenda::Agenda(Fecha fecha_inicial) : fecha_(fecha_inicial){}


void Agenda::agregar_recordatorio(Recordatorio rec) {
   /* bool yaPuesto = false; //Para ver si ya agregue el recordatorio a la lista voy a usar un bool
    if(this->rec_de_hoy_.empty()){ //si esta vacio no tengo q comparar con otro rec
        this->rec_de_hoy_.push_back(rec); //luego, simplemente agrego rec
    }else{
        list<Recordatorio> res;
        for(Recordatorio r: this->recordatorios_de_hoy()){ //uso un for range, mas facil
            //si el horario del rec q me pasaron a la funcion es mayor menor q el rec actual de mi lista
            //lo añado
            if(rec.horario() < r.horario()){
                if(yaPuesto){ //si ya lo agregue solo sigo agregando a mi lista res los demas
                    res.push_back(r);
                }else{ //en caso de no haberlo agregado añado el rec q me pasaron antes y luego sigo con los demas
                    yaPuesto = true; //lo hago true asi no sigo añadiendolo a la lista antes q todos los rec
                    res.push_back(rec);
                    res.push_back(r);
                }
            }else{
                //en caso de q solo haya uno y el horario del q me pasaron es mayor q el q tengo en la lista,
                //simplemente agrego al ultimo el rec
                if(this->recordatorios_de_hoy().size() == 1){
                    res.push_back(r);
                    res.push_back(rec);
                }else{ //Si no es asi y el horario de rec es mayor que el de r, entonces sigo añadiendo r,
                       // hasta encontrar uno q sea mayor a rec
                    res.push_back(r);
                }

            }
        }
        this->rec_de_hoy_ = res;
    }*/

   //Pruebo sort
    this->rec_de_hoy_.push_back(rec);
    this->rec_de_hoy_.sort([](Recordatorio & rec1, Recordatorio & rec2){
        return rec1.horario() < rec2.horario();
    }
    );

}



void Agenda::incrementar_dia() {
    this->fecha_.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    return this->rec_de_hoy_;
}

Fecha Agenda::hoy() {
    return this->fecha_;
}

ostream& operator<<(ostream& os, Agenda a){
    os << a.hoy() << endl;
    os << "=====" << endl;
    for(Recordatorio r : a.recordatorios_de_hoy()){
        if(r.fecha() == a.hoy()){ //Cuidado aca, si rompe las pelotas comparar dia con dia y mes con mes
            os << r << endl;
        }
    }
    return os;
}


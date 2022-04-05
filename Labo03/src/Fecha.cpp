// Typedef
typedef int Anio;
typedef int Mes;
typedef int Dia;

// MESES
const Mes ENERO = 1;
const Mes FEBRERO = 2;
const Mes MARZO = 3;
const Mes ABRIL = 4;
const Mes MAYO = 5;
const Mes JUNIO = 6;
const Mes JULIO = 7;
const Mes AGOSTO = 8;
const Mes SEPTIEMBRE = 9;
const Mes OCTUBRE = 10;
const Mes NOVIEMBRE = 11;
const Mes DICIEMBRE = 12;

bool esBisiesto(Anio anio) {
  bool p = anio % 4 == 0;
  bool q = anio % 100 == 0;
  bool r = anio % 400 == 0;
  return p and ((not q) or r);
}

int diasEnMes(int anio, int mes) {
  if (mes == FEBRERO) {
    if (esBisiesto(anio)) {
      return 29;
    } else {
      return 28;
    }
  }
  // No es febrero
  if (mes < AGOSTO) {
    if (mes % 2 == ENERO % 2) {
      return 31;
    } else {
      return 30;
    }
  } else {
    if (mes % 2 == AGOSTO % 2) {
      return 31;
    } else {
      return 30;
    }
  }
}

class Periodo;

class Fecha {
 public:
  // pre: anio > 0, mes \in [1, 12], dia \in [1, diasEnMes(anio, mes)]
  Fecha(Anio anio, Mes mes, Dia dia);

  Anio anio() const;
  Mes mes() const;
  Dia dia() const;

  bool operator==(Fecha o) const;
  bool operator<(Fecha o) const;

  void sumar_periodo(Periodo p);

 private:
  Anio anio_;
  Mes mes_; 
  Dia dia_;

  void ajustar_fecha();
  void sumar_anios(Anio anios);
  void sumar_meses(Mes meses);
  void sumar_dias(Dia dias);
};

Fecha::Fecha(Anio anio, Mes mes, Dia dia) {
  anio_ = anio;
  mes_ = mes;
  dia_ = dia;
}

Anio Fecha::anio() const {
  return anio_;
}

Mes Fecha::mes() const {
  return mes_;
}

Dia Fecha::dia() const {
  return dia_;
}

bool Fecha::operator==(Fecha o) const {
  return (anio_ == o.anio() and mes_ == o.mes() and dia_ == o.dia());
}

bool Fecha::operator<(Fecha o) const {
  return (anio_ < o.anio() or
          (anio_ == o.anio() and mes_ < o.mes()) or
          (anio_ == o.anio() and mes_ == o.mes() and dia_ < o.dia()));
}

bool operator!=(Fecha f1, Fecha f2) {
  return not (f1 == f2);
}

class Periodo {
 public:
  Periodo(int anios, int meses, int dias);

  int anios() const;
  int meses() const;
  int dias() const;

 private:
  int anios_;
  int meses_;
  int dias_;
};

Periodo::Periodo(int anios, int meses, int dias) : anios_(anios), 
    meses_(meses), dias_(dias) {};

int Periodo::anios() const {
  return anios_;
}

int Periodo::meses() const {
  return meses_;
}

int Periodo::dias() const {
  return dias_;
}

void Fecha::ajustar_fecha() {
  while (mes_ > 12 || dia_ > diasEnMes(anio_, mes_)) {
    if (mes_ > 12) {
      mes_ -= 12;
      anio_ += 1;
    } else {
      dia_ -= diasEnMes(anio_, mes_);
      mes_ += 1;
    }
  }
}

void Fecha::sumar_anios(int anios) {
  anio_ += anios;
  ajustar_fecha();
}

void Fecha::sumar_meses(int meses) {
  mes_ += meses;
  ajustar_fecha();
}

void Fecha::sumar_dias(int dias) {
  dia_ += dias;
  ajustar_fecha();
}

void Fecha::sumar_periodo(Periodo p) {
  sumar_anios(p.anios());
  sumar_meses(p.meses());
  sumar_dias(p.dias());
}

class Intervalo {
 public:
  // pre: desde < hasta
  Intervalo(Fecha desde, Fecha hasta);

  Fecha desde() const;
  Fecha hasta() const;

  int enDias() const;

 private:
  Fecha desde_;
  Fecha hasta_;
};

Intervalo::Intervalo(Fecha desde, Fecha hasta) : desde_(desde), hasta_(hasta) {};

Fecha Intervalo::desde() const {
  return desde_;
}

Fecha Intervalo::hasta() const {
  return hasta_;
}

int Intervalo::enDias() const {
  Fecha actual = desde_;
  int dias = 0;
  while (actual != hasta_) {
    dias++;
    actual.sumar_periodo(Periodo(0, 0, 1));
  }
  return dias;
}

#include "gtest-1.8.1/gtest.h"
#include "../src/Libreta.h"
#include "../src/Truco.h"
#include <map>
#include <cmath>

using namespace std;

// Ejercicio 4
TEST(Aritmetica, suma) {
    int calculado = 2+3;
    int esperado = 5;
    EXPECT_EQ(calculado, esperado);
}

// Ejercicio 5
TEST(Aritmetica, potencia) {
    int calculado = pow(10,2);
    int esperado = 100;
    EXPECT_EQ(calculado, esperado);
}

// Ejercicios 6..9

//Ejercicio 6
TEST(Aritmetica, potencia_general){
    for(int i = -5; i <= 5;i++){
        //if(i != 0){
        EXPECT_EQ(pow(i, 2), i*i);
        //}
    }
}

//Ejercicio 7
TEST(Diccionario, obtener){
    map<int,int> m;
    m[1] = 10;
    EXPECT_EQ(10, m.at(1));
}

//Ejercicio 8
TEST(Diccionario, definir){
    map<int,int> m;
    EXPECT_EQ(m.count(5), 0);
    m.insert(make_pair(5, 50));
    EXPECT_EQ(m.count(5), 1);
}

TEST(Truco, inicio){
    Truco t;
    EXPECT_TRUE(t.puntaje_j1() == 0 && t.puntaje_j2() == 0);
}

TEST(Truco, buenas){

    Truco t;
    EXPECT_FALSE(t.buenas(1));

    for(int i = 0; i < 15; i ++){
        t.sumar_punto(1);
    }
    EXPECT_FALSE(t.buenas(1));

    t.sumar_punto(1);
    EXPECT_TRUE(t.buenas(1));

    t.sumar_punto(1);
    t.sumar_punto(1);
    EXPECT_TRUE(t.buenas(1));
}
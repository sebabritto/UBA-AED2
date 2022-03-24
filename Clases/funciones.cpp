#include <vector>
#include "algobot.h"
#include <set>

using namespace std;

// Ejercicio 1
bool pertenece(vector<int> vec, int elem){
    for(int i = 0; i < vec.size(); i++){
        if(elem == vec[i]){
            return true;
        }
    }
    return false;
}

vector<int> quitar_repetidos(vector<int> s) {
    vector<int> res;
    for(int i = 0; i < s.size(); i++){
        if(!pertenece(res, s[i])){
            res.push_back(s[i]);
        }
    }
    return res;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    set<int> set_a;
    vector<int> res;
    for(int i = 0; i < s.size(); i++){
        set_a.insert(s[i]);
    }
    for(int n: set_a){
        res.push_back(n);
    }
    return res;
}

// Ejercicio 3

bool mismos_elementos(vector<int> a, vector<int> b) {
    for(int i = 0; i < a.size(); i++){
        if(!pertenece(b, a[i])){
            return false;
        }
    }
    return true;
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    set<int> set_a;
    set<int> set_b;
    for(int i = 0; i < a.size(); i++){
        set_a.insert(a[i]);
    }
    for(int j = 0; j < b.size(); j++){
        set_b.insert(b[j]);
    }
    return set_a == set_b;
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map<int, int> cont;
    vector<int> res;

    for(int i = 0; i < s.size(); i++){
        if(cont[s[i]] == 0){
            int valor = 0;
            for(int j = 0; j < s.size(); j++){
                if(s[i] == s[j]){
                    valor++;
                }
            }
            cont[s[i]] = valor;
        }
    }

    return cont;
}

// Ejercicio 6
int cantApariciones(vector<int> vec, int elem){
    int cant = 0;
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == elem){
            cant++;
        }
    }
    return cant;

}
vector<int> filtrar_repetidos(vector<int> s) {
    vector<int> res;
    /*for(int i = 0; i < s.size(); i++){
        if(cantApariciones(s, s[i]) == 1){
            res.push_back(s[i]);
        }
    }*/
    map<int,int> cont = contar_apariciones(s);
    for(int i = 0; i < s.size(); i++){
        if(cont[s[i]] == 1){
            res.push_back(s[i]);
        }
    }
    return res;
}

// Ejercicio 7
set<int> interseccion(set<int> a, set<int> b) {
    set<int> res;
    for(int n: a){
        if(a.count(n) == b.count(n)){
            res.insert(n);
        }
    }
    return res;
}

// Ejercicio 8
bool yaPertenece(map<int, set<int>> m, int elem){
    if(m.count(elem) > 0){
        return true;
    }
    return false;
}
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    set<int> a;
    map<int, set<int>> res;
    if(quitar_repetidos(s) == s){
        for(int i = 0; i < s.size(); i++){
            if(!yaPertenece(res, s[i] % 10)){
                int valor1 = s[i] % 10;
                for(int j = i; j < s.size(); j++){
                    int valor2 = s[j] % 10;
                    if(valor2 == valor1){
                        a.insert(s[j]);
                    }
                }
                res[valor1] = a;
                a.clear();
            }
        }
    }
    return res;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    vector<char> res = str;
    for(int i = 0; i < str.size(); i++){
        for(int j = 0; j < tr.size(); j++){
            if(tr[j].first == str[i]){
                res[i] = tr[j].second;
            }
        }
    }
    return res;
}

// Ejercicio 10
bool integrantes_repetidos(vector<Mail> s) {
    int fecha = s[0].fecha();
    for(int i = 0; i < s.size(); i++){
        for(LU n: s[i].libretas()){
            for(int j = i+1; j < s.size(); j++){
                for(LU k: s[j].libretas()){
                    if(n == k && s[i].libretas() != s[j].libretas() && s[i].fecha() == s[j].fecha()){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Ejercicio 11
map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
    map<set<LU>, Mail> res;
    int fechaMayor;
    for(int i = 0; i < s.size(); i++){

        if(s[i].adjunto()){
            res[s[i].libretas()] = s[i];
            for(int j = i+1; j < s.size(); j++){
                if((s[i].libretas() == s[j].libretas()) && (s[i].fecha() < s[j].fecha()) && s[j].adjunto()){
                    int fecha = s[j].fecha();
                    //res[s[i].libretas()] = s[j];
                    res.at(s[i].libretas()) = s[j];
                }
            }
        }
    }
    return res;
}


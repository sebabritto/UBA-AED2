#ifndef TIPOS_H
#define TIPOS_H

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <set>
#include <tuple>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "string_map.hpp"

using namespace std;

template<typename T> //No se si esta bien.
using diccTrie = string_map<T>;

using Nat = unsigned int;

using Casilla = pair<int, int>;

using Jugador = string;

enum Direccion {
    Horizontal, Vertical
};

#endif // TIPOS_H


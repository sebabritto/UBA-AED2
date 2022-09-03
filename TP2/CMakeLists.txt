cmake_minimum_required(VERSION 3.5)
project(TP_SimCity)

option(WITH_GUI "Preparar compilacion con interfaz grafica (necesita SDL instalado)" OFF)

# IMPORTANTE: Descomentar la siguiente linea para preparar compilacion con interfaz grafica (leer el readme para las instrucciones completas)
# set(WITH_GUI ON)

set(CMAKE_CXX_STANDARD 11)

# Algunos flags para pasar al compilador (gnu++11 en vez de c++11 para que sea cross-plat)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++11 -ggdb3 -g")

# Dependencia de Google Test
SET(BUILD_GMOCK OFF)
SET(BUILD_GTEST ON)
add_library(gtest STATIC tests/gtest-1.8.1/gtest-all.cc)
add_library(gtest_main STATIC tests/gtest-1.8.1/gtest_main.cc)

# Leemos todos los archivos fuentes en ./src
file(GLOB SOURCE_FILES src/*.cpp src/*.h src/*.hpp)

if (WITH_GUI)
    # Leemos todos los archivos fuentes en ./gui
    file(GLOB GUI_FILES gui/*.cpp gui/*.h gui/*.hpp)

    # En caso de no encontrar la biblioteca SDL, probar descomentando la siguiente línea
    # set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modulos/)

    find_package(SDL2 REQUIRED CONFIG)
    include_directories(${SDL2_INCLUDE_DIRS})

    add_executable(simCityGUI gui/main.cpp ${GUI_FILES} ${SOURCE_FILES})

    target_link_libraries(simCityGUI ${SDL2_LIBRARIES})
endif (WITH_GUI)

add_executable(correrTests ${SOURCE_FILES} tests/servidor-tests.cpp src/Servidor.h src/SimCity.h src/Servidor.cpp src/SimCity.cpp src/Mapa.h src/Mapa.cpp src/string_map.hpp)

# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)

# Test suites a ejecutar
add_test(correrTests servidor_test)

# Target para correr Valgrind
add_custom_target(correrValgrind
        valgrind --leak-check=full -v ./correrTests 2>&1
        DEPENDS correrTests)

#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

using namespace std;

const int ANCHO = 120;
const int ALTO  = 40;

// Declaración de funciones
void limpiarPantalla();
void vaciarBuffer();
void pausa();
void pausaSimple();
void lineaHorizontal(char c = '-');
void centrarTexto(string texto, int ancho = ANCHO);
void bordeSuperior();
void bordeInferior();
void lineaVacia(int cantidad = 1);

#endif
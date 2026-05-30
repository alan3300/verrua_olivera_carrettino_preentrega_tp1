#ifndef JUEGO_H
#define JUEGO_H

#include "utilidades.h"
#include <unistd.h>

// Variables globales del juego
extern string nombreJugador;
extern int puntaje;
extern bool juegoActivo;

// Funciones del juego
void mostrarTitulo();
void mostrarCreditos();
void mostrarInstrucciones();
void pantallaIntroduccion();
void pedirNombre();
bool pantallaPreparacion();
void cuentaRegresiva();

// Preguntas
bool pregunta1();
bool pregunta2();
bool pregunta3();
bool pregunta4();

// Finales
void pantallaVictoria();
void pantallaDerrota();
void jugar();
void menuPrincipal();

#endif
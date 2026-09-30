#pragma once
#include <iostream>
#include <string>
using namespace std;

// Constantes enumeradas: Estados de ánimo de la criatura.
enum EstadoAnimo { TRANQUILO = 0, INQUIETO, FURIOSO, SOMBRIO, NUM_ESTADOS };

class Criatura
{
public:
  Criatura(string nombre = "Sin Nombre");

  // Setters y getters
  void setNombre(string nombre);
  string getNombre();
  void setHambre(int hambre);
  int getHambre();
  void setEnergia(int energia);
  int getEnergia();
  void setCordura(int cordura);
  int getCordura();

  EstadoAnimo getAnimo();
  string getAnimoTexto();

  // Acciones del jugador
  void alimentar();
  void descansar();
  void ritualCalmante();
  void pasarTiempo(); // el ciclo "envejece" a la criatura

  bool estaViva();
  int getEdad();

  // Propiedad (dato miembro) static.
  static int totalCriaturas;

private:
  string m_nombre;
  int m_edad;
  int m_hambre;   // 0..100 (0 = saciada, 100 = muere de hambre)
  int m_energia;  // 0..100 (0 = se apaga)
  int m_cordura;  // 0..100 (0 = enloquece)
  EstadoAnimo m_animo;
  int aleatorio(int min, int max);
};

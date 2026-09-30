#include "Criatura.h"
#include <cstdlib>
#include <ctime>

// Inicialización de la propiedad estática.
int Criatura::totalCriaturas = 0;

/* /////////////////////////////////////////////////////////////////////// */
// Definición del método constructor.
Criatura::Criatura(string nombre)
{
  m_nombre = nombre;
  m_edad   = 0;
  m_hambre = 20 + aleatorio(0, 10);
  m_energia = 60 + aleatorio(0, 20);
  m_cordura = 70 + aleatorio(0, 20);
  m_animo = TRANQUILO;

  // Incrementamos la variable estatica cada vez que se llame al
  // método constructor.
  totalCriaturas++;
}

/* /////////////////////////////////////////////////////////////////////// */
// Aleatoriedad
int Criatura::aleatorio(int min, int max)
{
  return min + rand() % (max - min + 1);
}

/* /////////////////////////////////////////////////////////////////////// */
void Criatura::setNombre(string nombre) { m_nombre = nombre; }
string Criatura::getNombre()            { return m_nombre; }
void Criatura::setHambre(int hambre)    { m_hambre = hambre; }
int Criatura::getHambre()               { return m_hambre; }
void Criatura::setEnergia(int energia)  { m_energia = energia; }
int Criatura::getEnergia()              { return m_energia; }
void Criatura::setCordura(int cordura)  { m_cordura = cordura; }
int Criatura::getCordura()              { return m_cordura; }
int Criatura::getEdad()                 { return m_edad; }

/* /////////////////////////////////////////////////////////////////////// */
EstadoAnimo Criatura::getAnimo()
{
  // El ánimo se deriva del atributo mas bajo. OJO: la HAMBRE está
  // "al revés" (0 = saciada, 100 = hambrienta), así que se la
  // invierte para compararla con energía y cordura.
  int saciedad = 100 - m_hambre;
  int peor = saciedad;
  if (m_energia < peor) peor = m_energia;
  if (m_cordura < peor) peor = m_cordura;

  if (peor >= 60)       return TRANQUILO;
  else if (peor >= 40)  return INQUIETO;
  else if (peor >= 20)  return SOMBRIO;
  else                  return FURIOSO;
}

string Criatura::getAnimoTexto()
{
  // Arreglo de cadenas indexado por la enumeración.
  string textos[NUM_ESTADOS] = { "TRANQUILO", "INQUIETO", "FURIOSO", "SOMBRIO" };
  return textos[getAnimo()];
}

/* /////////////////////////////////////////////////////////////////////// */
void Criatura::alimentar()
{
  m_hambre -= 25 + aleatorio(0, 10);
  if (m_hambre < 0) m_hambre = 0;
  m_energia -= 5;
  if (m_energia < 0) m_energia = 0;
}

void Criatura::descansar()
{
  m_energia += 25 + aleatorio(0, 10);
  if (m_energia > 100) m_energia = 100;
  m_hambre += 8;
  if (m_hambre > 100) m_hambre = 100;
}

void Criatura::ritualCalmante()
{
  m_cordura += 20 + aleatorio(0, 10);
  if (m_cordura > 100) m_cordura = 100;
  m_energia -= 8;
  if (m_energia < 0) m_energia = 0;
}

/* /////////////////////////////////////////////////////////////////////// */
// El ciclo de tiempo: la criatura consume recursos y puede sufrir
// eventos aleatorios del cementerio.
void Criatura::pasarTiempo()
{
  m_edad++;
  m_hambre  += 6 + aleatorio(0, 5);
  m_energia -= 6 + aleatorio(0, 5);
  m_cordura -= 4 + aleatorio(0, 5);

  // Evento aleatorio del cementerio.
  int evento = aleatorio(0, 9);
  if (evento == 0)      m_cordura -= 12; // vientos funebres
  else if (evento == 1) m_hambre  += 10; // cuervos roban la ofrenda
  else if (evento == 2) m_energia -= 10; // alarma brutalista

  // Limitar valores entre 0 y 100.
  if (m_hambre  > 100) m_hambre  = 100;
  if (m_hambre  < 0)   m_hambre  = 0;
  if (m_energia > 100) m_energia = 100;
  if (m_energia < 0)   m_energia = 0;
  if (m_cordura > 100) m_cordura = 100;
  if (m_cordura < 0)   m_cordura = 0;
}

/* /////////////////////////////////////////////////////////////////////// */
bool Criatura::estaViva()
{
  // La criatura muere: de hambre cuando la HAMBRE llega a 100,
  // se apaga cuando la ENERGÍA llega a 0,
  // enloquece cuando la CORDURA llega a 0.
  return (m_hambre < 100 && m_energia > 0 && m_cordura > 0);
}

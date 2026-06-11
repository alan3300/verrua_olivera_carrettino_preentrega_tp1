
/*************************************************************************
 AVENTURA CONVERSACIONAL: "ESCAPE DE LA FACULTAD"
 Autores: Verrua, Alan; Olivera, Florencia; Carrettino, Fiorella.
 Materia: Informática General (Cat. Tirigall)
 Lic. en Artes Multimediales.
 Universidad Nacional de las Artes - Junio 2026

 Criterios de evaluación:
 - Uso de ciclo WHILE
 - Uso de ciclo FOR
 - Menu con SWITCH
 - Condicionales IF / ELSE
 - Variables INT, FLOAT y BOOL
 - Operadores logicos AND (&&) y OR (||)
 - Uso de cin para entrada de datos
 - Titulo del juego
 - Vuelta al menu al ganar/perder
 - Instructivo de como jugar
 - Resolucion terminal: 120x40
*************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main()
{
  // ==========================================================================
  //  VARIABLES GLOBALES DEL JUEGO (dentro de main, como en los ejemplos)
  // ==========================================================================
  string nombreJugador;
  int puntaje = 0;
  bool juegoActivo = false;
  float tiempoRestante = 60.0f;
  
  bool salirDelJuego = false;
  int opcionMenu;
  int eleccion;
  bool gameover;
  char respuesta;
  int pantallaActual;
  bool sigueVivo;
  int i;
  float porcentaje;
  bool preparado;

  // ==========================================================================
  //  MENU PRINCIPAL - BUCLE WHILE
  // ==========================================================================
  while (!salirDelJuego)
  {
    do
    {
      system("clear");
      
      // Titulo ASCII art
      cout << endl << endl;
      cout << "   ______  _____  _____       _____   ______   _____  ______   _               " << endl;
      cout << "  |  ____|/ ____|/ ____|  /\  |  __ \ |  ____| |  __ \|  ____| | |        /\   " << endl;
      cout << "  | |__  | (___ | |      /  \ | |__) || |__    | |  | | |__    | |       /  \  " << endl;
      cout << "  |  __|  \___ \| |     / /\ \|  ___/ |  __|   | |  | |  __|   | |      / /\ \ " << endl;
      cout << "  | |____ ____) | |____/ ____ \ |     | |____  | |__| | |____  | |____ / ____ \\" << endl;
      cout << "  |______|_____/ \_____/_/    \_\     |______| |_____/|______| |______/_/    \_\\" << endl;
      cout << endl;
      cout << "   ______       _____  _    _  _    _______       _____  " << endl;
      cout << "  |  ____|/\   |  __ \| |  | || |  |__   __|/\   |  __ \ " << endl;
      cout << "  | |__  /  \  | |  | | |  | || |     | |  /  \  | |  | |" << endl;
      cout << "  |  __|/ /\ \ | |  | | |  | || |     | | / /\ \ | |  | |" << endl;
      cout << "  | |  / ____ \| |__| | |__| || |____ | |/ ____ \| |__| |" << endl;
      cout << "  |_| /_/    \_\_____/ \____/ |______||_/_/    \_\_____/ " << endl;
      cout << endl << endl;
      
      cout << "                                    +----------------------------------------+" << endl;
      cout << "                                    |         MENU PRINCIPAL                 |" << endl;
      cout << "                                    +----------------------------------------+" << endl;
      cout << "                                    |                                        |" << endl;
      cout << "                                    |     1- Iniciar juego                   |" << endl;
      cout << "                                    |     2- Instrucciones                   |" << endl;
      cout << "                                    |     3- Creditos                        |" << endl;
      cout << "                                    |     4- Salir                           |" << endl;
      cout << "                                    |                                        |" << endl;
      cout << "                                    +----------------------------------------+" << endl;
      cout << endl;
      cout << "                                    Ingrese Opcion: ";
      cin >> opcionMenu;

      // SWITCH para manejar las opciones del menu
      switch (opcionMenu)
      {
        case 1:
          system("clear");
          cout << "El juego esta por comenzar..." << endl;
          cin.ignore().get();
          break;
        case 2:
          system("clear");
          cout << "Mostrando instrucciones..." << endl;
          cin.ignore().get();
          break;
        case 3:
          system("clear");
          cout << "Mostrando creditos..." << endl;
          cin.ignore().get();
          break;
        case 4:
          system("clear");
          cout << "Ha decidido salir del juego..." << endl;
          cin.ignore().get();
          break;
        default:
          system("clear");
          cout << "Introduzca una opcion valida." << endl;
          cin.ignore().get();
          break;
      }
    } while (opcionMenu != 1 && opcionMenu != 2 && opcionMenu != 3 && opcionMenu != 4);

    // ==========================================================================
    //  INSTRUCCIONES
    // ==========================================================================
    if (opcionMenu == 2)
    {
      system("clear");
      cout << "+====================================================================================================+" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|                              INSTRUCCIONES DE JUEGO                                                |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|   Sos une estudiantx atrapadx en la UNA despues de hora.                                           |" << endl;
      cout << "|   Debes escapar resolviendo acertijos en cada aula.                                                |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|   COMO JUGAR:                                                                                      |" << endl;
      cout << "|   - Ingresa el numero de la opcion elegida                                                         |" << endl;
      cout << "|   - Responde correctamente para avanzar y desbloquear las puertas                                  |" << endl;
      cout << "|   - Si fallas una pregunta, perdes el juego                                                        |" << endl;
      cout << "|   - Debes responder TODAS correctamente para poder escapar                                         |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "+====================================================================================================+" << endl;
      cout << endl;
      cout << "Presione ENTER para volver al menu...";
      cin.ignore().get();
    }

    // ==========================================================================
    //  CREDITOS
    // ==========================================================================
    else if (opcionMenu == 3)
    {
      system("clear");
      cout << "+====================================================================================================+" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|                                   CREDITOS                                                         |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|   Desarrollado por: Alan Verrua, Florencia Olivera y Fiorella Carrettino                           |" << endl;
      cout << "|   Materia: Informatica General (Cat. Tirigall)                                                     |" << endl;
      cout << "|   Universidad Nacional de las Artes                                                                |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|   Junio de 2026                                                                                    |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "+====================================================================================================+" << endl;
      cout << endl;
      cout << "Presione ENTER para volver al menu...";
      cin.ignore().get();
    }

    // ==========================================================================
    //  JUGAR
    // ==========================================================================
    else if (opcionMenu == 1)
    {
      puntaje = 0;
      juegoActivo = true;
      tiempoRestante = 60.0f;
      gameover = false;

      // ---------------------- PANTALLA INTRODUCCION -------------------------
      system("clear");
      cout << "+====================================================================================================+" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|                    FACULTAD. CALLE VIAMONTE... 23:45 Hs...                                          |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|         Las luces se apagan... las puertas se cierran...                                           |" << endl;
      cout << "|         Solo queda una salida, pero esta bloqueada por acertijos.                                  |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "+====================================================================================================+" << endl;
      cout << endl;
      cout << "Presione ENTER para continuar...";
      cin.ignore().get();

      // ---------------------- PEDIR NOMBRE ----------------------------------
      system("clear");
      cout << "+====================================================================================================+" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|                         Como es tu nombre, estudiantx?                                             |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "+====================================================================================================+" << endl;
      cout << endl;
      cout << "  Indique su nombre: ";
      cin.ignore();
      getline(cin, nombreJugador);
      if (nombreJugador.empty())
      {
        nombreJugador = "Estudiantx";
      }
      cout << endl;
      cout << "  Hola " << nombreJugador << ", INTENTA ESCAPAR!" << endl;
      cout << endl;
      cout << "Presione ENTER para continuar...";
      cin.get();

      // ---------------------- PANTALLA PREPARACION --------------------------
      system("clear");
      cout << "+====================================================================================================+" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|         " << nombreJugador << ", Por que te quedaste hasta tan tarde en la facultad?" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "|                              1. Me quede estudiando                                                |" << endl;
      cout << "|                              2. Me quede dormidx                                                   |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "+====================================================================================================+" << endl;
      cout << endl;
      cout << "  Ingrese Opcion: ";
      cin >> eleccion;

      system("clear");
      cout << "+====================================================================================================+" << endl;
      cout << "|                                                                                                    |" << endl;
      if (eleccion == 1)
      {
        cout << "|                    PROFE: JAJA mira que dedicadx...                                                 |" << endl;
      }
      else
      {
        cout << "|                    PROFE: Asi estamos, pais...                                                      |" << endl;
      }
      cout << "|                                                                                                    |" << endl;
      cout << "|                    Estas preparadx para el desafio? (S/N):                                          |" << endl;
      cout << "|                                                                                                    |" << endl;
      cout << "+====================================================================================================+" << endl;
      cout << endl;
      cout << "  Respuesta: ";
      cin >> respuesta;

      // Uso de operador OR (||)
      if (respuesta == 'S' || respuesta == 's')
      {
        preparado = true;
      }
      else
      {
        preparado = false;
      }

      if (!preparado)
      {
        system("clear");
        cout << "+====================================================================================================+" << endl;
        cout << "|                                                                                                    |" << endl;
        cout << "|         Bueno, cuando estes listx volve!!! Te estaremos esperando muejjejej                        |" << endl;
        cout << "|                                                                                                    |" << endl;
        cout << "+====================================================================================================+" << endl;
        cout << endl;
        cout << "Presione ENTER para continuar...";
        cin.ignore().get();
        gameover = true;
      }
      else
      {
        // ---------------------- CUENTA REGRESIVA CON FOR ------------------
        system("clear");
        cout << endl << endl;
        cout << "                              Preparate..." << endl;
        cout << endl;

        for (i = 3; i >= 1; i--)
        {
          cout << endl << endl;
          if (i == 3)
          {
            cout << "                                   _____  " << endl;
            cout << "                                  |___ /  " << endl;
            cout << "                                    |_ \\  " << endl;
            cout << "                                   ___) | " << endl;
            cout << "                                  |____/  " << endl;
          }
          else if (i == 2)
          {
            cout << "                                    ___   " << endl;
            cout << "                                   |__ \\  " << endl;
            cout << "                                     / /  " << endl;
            cout << "                                    / /_  " << endl;
            cout << "                                   |____| " << endl;
          }
          else
          {
            cout << "                                     __   " << endl;
            cout << "                                    /_ |  " << endl;
            cout << "                                     | |  " << endl;
            cout << "                                     | |  " << endl;
            cout << "                                     |_|  " << endl;
          }
          usleep(800000);
          system("clear");
        }

        // ==================================================================
        //  BUCLE WHILE PARA LAS 4 PANTALLAS
        // ==================================================================
        pantallaActual = 1;
        sigueVivo = true;

        while (pantallaActual <= 4 && sigueVivo && juegoActivo)
        {
          // ---------------------- PANTALLA 1 ------------------------------
          if (pantallaActual == 1)
          {
            do
            {
              system("clear");
              cout << "+====================================================================================================+" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|                    PANTALLA 1: AULA DE INFORMATICA GENERAL                                         |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|   PROFESOR: Tengo un inicio pero nunca un final.                                                   |" << endl;
              cout << "|             Si me ejecutas, el programa no avanza. Que soy?                                        |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|                              1) Bucle                                                              |" << endl;
              cout << "|                              2) Bucle infinito                                                     |" << endl;
              cout << "|                              3) Variable                                                           |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "+====================================================================================================+" << endl;
              cout << endl;
              cout << "  Ingrese Opcion: ";
              cin >> eleccion;
            } while (eleccion != 1 && eleccion != 2 && eleccion != 3);

            system("clear");
            cout << "+====================================================================================================+" << endl;
            cout << "|                                                                                                    |" << endl;

            if (eleccion == 2)
            {
              cout << "|                              CORRECTO!!                                                             |" << endl;
              cout << "|                    La puerta del aula se abre...                                                    |" << endl;
              puntaje += 25;
            }
            else
            {
              cout << "|                              INCORRECTO!!!                                                          |" << endl;
              cout << "|                    La alarma de seguridad se activa...                                              |" << endl;
              sigueVivo = false;
            }
            cout << "|                                                                                                    |" << endl;
            cout << "+====================================================================================================+" << endl;
            cout << endl;
            cout << "Presione ENTER para continuar...";
            cin.ignore().get();
          }

          // ---------------------- PANTALLA 2 ------------------------------
          else if (pantallaActual == 2)
          {
            do
            {
              system("clear");
              cout << "+====================================================================================================+" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|                    PANTALLA 2: [COMPLETAR CON NARRATIVA]                                           |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|   [Agregar acertijo o pregunta aqui]                                                               |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|                              1) Opcion 1                                                           |" << endl;
              cout << "|                              2) Opcion 2                                                           |" << endl;
              cout << "|                              3) Opcion 3                                                           |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|   [Usar variable float tiempoRestante y operador && o ||]                                          |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "+====================================================================================================+" << endl;
              cout << endl;
              cout << "  Ingrese Opcion: ";
              cin >> eleccion;
            } while (eleccion != 1 && eleccion != 2 && eleccion != 3);

            // Ejemplo de uso de float y operador &&:
            // tiempoRestante -= 15.0f;
            // if (eleccion == 2 && tiempoRestante > 0.0f) { ... }

            system("clear");
            cout << "+====================================================================================================+" << endl;
            cout << "|                                                                                                    |" << endl;
            cout << "|                    [COMPLETAR: mensaje de correcto o incorrecto]                                    |" << endl;
            cout << "|                                                                                                    |" << endl;
            cout << "+====================================================================================================+" << endl;
            cout << endl;
            cout << "Presione ENTER para continuar...";
            cin.ignore().get();
            
            // Por ahora siempre correcto para no bloquear
            puntaje += 25;
          }

          // ---------------------- PANTALLA 3 ------------------------------
          else if (pantallaActual == 3)
          {
            do
            {
              system("clear");
              cout << "+====================================================================================================+" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|                    PANTALLA 3: [COMPLETAR CON NARRATIVA]                                           |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|   [Agregar acertijo o pregunta aqui]                                                               |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|                              1) Opcion 1                                                           |" << endl;
              cout << "|                              2) Opcion 2                                                           |" << endl;
              cout << "|                              3) Opcion 3                                                           |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|   [Usar variable float tiempoRestante y operador && o ||]                                          |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "+====================================================================================================+" << endl;
              cout << endl;
              cout << "  Ingrese Opcion: ";
              cin >> eleccion;
            } while (eleccion != 1 && eleccion != 2 && eleccion != 3);

            // Ejemplo de uso de float y operador ||:
            // tiempoRestante -= 15.0f;
            // if (eleccion == 1 || tiempoRestante <= 30.0f) { ... }

            system("clear");
            cout << "+====================================================================================================+" << endl;
            cout << "|                                                                                                    |" << endl;
            cout << "|                    [COMPLETAR: mensaje de correcto o incorrecto]                                    |" << endl;
            cout << "|                                                                                                    |" << endl;
            cout << "+====================================================================================================+" << endl;
            cout << endl;
            cout << "Presione ENTER para continuar...";
            cin.ignore().get();
            
            // Por ahora siempre correcto para no bloquear
            puntaje += 25;
          }

          // ---------------------- PANTALLA 4 ------------------------------
          else if (pantallaActual == 4)
          {
            do
            {
              system("clear");
              cout << "+====================================================================================================+" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|                    PANTALLA 4: [COMPLETAR CON NARRATIVA]                                           |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|   [Agregar acertijo o pregunta final aqui]                                                         |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|                              1) Opcion 1                                                           |" << endl;
              cout << "|                              2) Opcion 2                                                           |" << endl;
              cout << "|                              3) Opcion 3                                                           |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "|   [Usar variable float tiempoRestante y operador && o ||]                                          |" << endl;
              cout << "|                                                                                                    |" << endl;
              cout << "+====================================================================================================+" << endl;
              cout << endl;
              cout << "  Ingrese Opcion: ";
              cin >> eleccion;
            } while (eleccion != 1 && eleccion != 2 && eleccion != 3);

            // Ejemplo de uso de float y operador &&:
            // if (eleccion == 3 && tiempoRestante > 0.0f) { victoria }
            // else if (eleccion != 3 || tiempoRestante <= 0.0f) { derrota }

            system("clear");
            cout << "+====================================================================================================+" << endl;
            cout << "|                                                                                                    |" << endl;
            cout << "|                    [COMPLETAR: mensaje de correcto o incorrecto]                                    |" << endl;
            cout << "|                                                                                                    |" << endl;
            cout << "+====================================================================================================+" << endl;
            cout << endl;
            cout << "Presione ENTER para continuar...";
            cin.ignore().get();
            
            // Por ahora siempre correcto para no bloquear
            puntaje += 25;
          }

          pantallaActual++;
        } // Fin while pantallas

        // ==================================================================
        //  PANTALLA FINAL: VICTORIA O DERROTA
        // ==================================================================
        if (sigueVivo)
        {
          // VICTORIA
          system("clear");
          cout << endl << endl;
          cout << "   _______  _______  ___      ___  _______  _______  _______  __  " << endl;
          cout << "  |       ||       ||   |    |   ||       ||       ||       ||  | " << endl;
          cout << "  |  _____||   _   ||   |    |   ||  _____||_     _||    ___||  | " << endl;
          cout << "  | |_____ |  |_|  ||   |    |   || |_____   |   |  |   |___ |  | " << endl;
          cout << "  |_____  ||       ||   |___ |   ||_____  |  |   |  |    ___||__| " << endl;
          cout << "   _____| ||   _   ||       ||   | _____| |  |   |  |   |___  __  " << endl;
          cout << "  |_______||__| |__||_______||___||_______|  |___|  |_______||__| " << endl;
          cout << endl;
          
          cout << "+====================================================================================================+" << endl;
          cout << "|                                                                                                    |" << endl;
          cout << "|                    FELICITACIONES " << nombreJugador << "!" << endl;
          cout << "|                                                                                                    |" << endl;
          cout << "|                    Escapaste del Laberinto de la Facultad!                                         |" << endl;
          cout << "|                                                                                                    |" << endl;
          
          // Uso de variable float para calcular porcentaje
          porcentaje = (puntaje / 100.0f) * 100.0f;
          cout << "|                    Puntaje final: " << puntaje << "/100 (" << (int)porcentaje << "%)" << endl;
          cout << "|                                                                                                    |" << endl;
          cout << "|                    Ahora, si... ponete a estudiar!                                                 |" << endl;
          cout << "|                                                                                                    |" << endl;
          cout << "+====================================================================================================+" << endl;
          cout << endl;
          cout << "Presione ENTER para continuar...";
          cin.ignore().get();
        }
        else
        {
          // DERROTA
          system("clear");
          cout << endl << endl;
          cout << "   _______  __    _  _______  _______  ______   ______   _______  ______   __   __   __   __  " << endl;
          cout << "  |       ||  |  | ||       ||       ||    _ | |    _ | |       ||      | |  | |  | |  | |  | " << endl;
          cout << "  |    ___||   |_| ||       ||    ___||   | || |   | || |   _   ||  _    ||  |_|  | |  | |  | " << endl;
          cout << "  |   |___ |       ||       ||   |___ |   |_||_|   |_||_|  |_|  || | |   ||       | |  | |  | " << endl;
          cout << "  |    ___||  _    ||      _||    ___||    __  |    __  |       || |_|   ||       | |__| |__| " << endl;
          cout << "  |   |___ | | |   ||     |_ |   |___ |   |  | |   |  | |   _   ||       ||   _   |  __   __  " << endl;
          cout << "  |_______||_|  |__||_______||_______||___|  |_|___|  |_|__| |__||______| |__| |__| |__| |__| " << endl;
          cout << endl;
          
          cout << "+====================================================================================================+" << endl;
          cout << "|                                                                                                    |" << endl;
          cout << "|                    LO SIENTO " << nombreJugador << "..." << endl;
          cout << "|                                                                                                    |" << endl;
          cout << "|                    No lograste escapar del Laberinto de la Facultad.                               |" << endl;
          cout << "|                                                                                                    |" << endl;
          cout << "|                    Puntaje obtenido: " << puntaje << "/100" << endl;
          cout << "|                                                                                                    |" << endl;
          cout << "+====================================================================================================+" << endl;
          cout << endl;
          cout << "Presione ENTER para continuar...";
          cin.ignore().get();
        }

        juegoActivo = false;
      } // Fin if preparado

      system("clear");
      cout << "Game Over" << endl;
      cout << "Presione ENTER para volver al menu...";
      cin.ignore().get();
    }
    else if (opcionMenu == 4)
    {
      salirDelJuego = true;
    }
  } // Fin while menu principal

  // ==========================================================================
  //  SALIR
  // ==========================================================================
  system("clear");
  cout << "Hasta la proxima!" << endl;
  cout << endl;

  return 0;
}

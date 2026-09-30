/***************************************************************\
 * EL GUARDIÁN DEL CEMENTERIO BRUTALISTA - TP2
 * Alumnxs: Alan Verruá - Florencia Olivera - Fiorella Carrettino
\***************************************************************/

#include <ncurses.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Criatura.h"

using namespace std;

// Enumeración del menú principal.
enum OpcionMenu { JUGAR = 0, INSTRUCTIVO, CREDITOS, SALIR, NUM_OPCIONES };

// Resolución del diseño.
const int ANCHO_DISENO = 120;
const int ALTO_DISENO  = 40;
// Tamano minimo para que sea jugable (chequeo de terminal).
const int ANCHO_MIN = 120;
const int ALTO_MIN  = 40;

// Arreglo de frames ASCII de la criatura, indexado por EstadoAnimo.
const string FRAMES_CRIATURA[NUM_ESTADOS][7] = {
  { // TRANQUILO
    "        _,=~~~==,,_       ",
    "    ,-~~~      ~~-~,      ",
    "   /  @         @  \\     ",
    "  |                |      ",
    "   \\   \\______/   /      ",
    "    ~-__________-~        ",
    "      ||      ||          "
  },
  { // INQUIETO
    "        _,=~~~==,,_       ",
    "    ,-~~~      ~~-~,      ",
    "   /  @         o  \\     ",
    "  |        __        |    ",
    "   \\   \\______/   /      ",
    "    ~-__________-~        ",
    "     /|      |\\         "
  },
  { // FURIOSO
    "        _,=~~~==,,_       ",
    "    ,-~~~      ~~-~,      ",
    "   /  \\X/   \\X/  \\    ",
    "  |    ________     |     ",
    "   \\  /______/\\  /      ",
    "    ~-__________-~        ",
    "     /|      |\\         "
  },
  { // SOMBRÍO
    "        _,=~~~==,,_       ",
    "    ,-~~~      ~~-~,      ",
    "   /  -         -  \\     ",
    "  |     ~~~~~~      |     ",
    "   \\   \\______/   /      ",
    "    ~-__________-~        ",
    "      ||      ||          "
  }
};

// Variables globales de adaptación a la terminal.
int W = ANCHO_DISENO;   // ancho util real
int H = ALTO_DISENO;    // alto util real
int ox = 0;             // desplazamiento horizontal (centrado)
int oy = 0;             // desplazamiento vertical (centrado)

// Funciones auxiliares.
void iniciarNcurses();
void calcularAdaptacion();
bool terminalSuficiente();
void pedirTerminalGrande();
void dibujarMarco(int colorPar);
void barra(int y, int x, int valor, string etiqueta, int colorPar);
void mostrarTitulo();
void mostrarInstructivo();
void mostrarCreditos();
int  menuPrincipal();
void jugar();
void pausar(string mensaje);

/* /////////////////////////////////////////////////////////////////////// */
int main()
{
  // Semilla para la aleatoriedad con RANDOM.
  srand((unsigned)time(NULL));

  iniciarNcurses();

  bool salir = false;
  while (!salir)
  {
    // Chequeo obligatorio de la consigna: la terminal debe medir
    // al menos 120x40; si no, se muestra un mensaje y se espera.
    pedirTerminalGrande();

    int op = menuPrincipal();
    if (op == JUGAR)             jugar();
    else if (op == INSTRUCTIVO)  mostrarInstructivo();
    else if (op == CREDITOS)     mostrarCreditos();
    else                         salir = true;
  }

  endwin();
  cout << "Gracias por jugar. Criaturas creadas en total: "
       << Criatura::totalCriaturas << endl;
  return 0;
}

/* /////////////////////////////////////////////////////////////////////// */
void iniciarNcurses()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  start_color();
  init_pair(1, COLOR_WHITE,  COLOR_BLACK); // texto normal
  init_pair(2, COLOR_GREEN,  COLOR_BLACK); // barras altas / estado bueno
  init_pair(3, COLOR_YELLOW, COLOR_BLACK); // barras medias
  init_pair(4, COLOR_RED,    COLOR_BLACK); // barras bajas / peligro
  init_pair(5, COLOR_CYAN,   COLOR_BLACK); // criatura / acentos
  init_pair(6, COLOR_MAGENTA,COLOR_BLACK); // título
  calcularAdaptacion();
}

/* /////////////////////////////////////////////////////////////////////// */
// Se adapta al tamaño real de la terminal: si es menor que el diseño,
// se usa el tamaño de la terminal; si es mayor, se centra el diseño.
void calcularAdaptacion()
{
  int alto, ancho;
  getmaxyx(stdscr, alto, ancho);
  W = min(ANCHO_DISENO, ancho);
  H = min(ALTO_DISENO, alto);
  if (W < ANCHO_MIN) W = min(ANCHO_MIN, ancho);
  if (H < ALTO_MIN)  H = min(ALTO_MIN, alto);
  ox = (ancho - W) / 2;
  oy = (alto - H) / 2;
}

/* /////////////////////////////////////////////////////////////////////// */
// Chequeo de consigna: ¿la terminal mide al menos 120x40?
bool terminalSuficiente()
{
  int alto, ancho;
  getmaxyx(stdscr, alto, ancho);
  return (ancho >= ANCHO_DISENO && alto >= ALTO_DISENO);
}

/* /////////////////////////////////////////////////////////////////////// */
// Si la terminal es mas chica que 120x40, se avisa con un mensaje
// centrado y se espera a que el usuario redimensione (o salga con Q).
void pedirTerminalGrande()
{
  while (!terminalSuficiente())
  {
    int alto, ancho;
    getmaxyx(stdscr, alto, ancho);
    clear();

    // Marco de advertencia centrado (aunque la terminal sea chica).
    int mw = min(ancho - 2, 70);
    int mh = 9;
    int mx = (ancho - mw) / 2;
    int my = (alto - mh) / 2;
    if (mx < 0) mx = 0;
    if (my < 0) my = 0;

    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(my, mx, "  TERMINAL DEMASIADO PEQUENA  ");
    attroff(COLOR_PAIR(4) | A_BOLD);

    attron(COLOR_PAIR(1));
    mvprintw(my + 2, mx, "Este juego necesita una terminal de al menos:");
    mvprintw(my + 3, mx, "    %d columnas x %d filas (resolucion del diseno)", ANCHO_DISENO, ALTO_DISENO);
    mvprintw(my + 5, mx, "Tamano actual detectado: %d columnas x %d filas", ancho, alto);
    mvprintw(my + 7, mx, ">> Redimensiona la ventana de la terminal <<");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3));
    mvprintw(my + 8, mx, "[Q] Salir del juego   |   Cualquier otra tecla: reintentar");
    attroff(COLOR_PAIR(3));

    refresh();
    int tecla = getch();
    if (tecla == KEY_RESIZE) continue;
    if (tecla == 'q' || tecla == 'Q')
    {
      endwin();
      cout << "Terminal insuficiente (" << ancho << "x" << alto
           << "). Se requiere al menos " << ANCHO_DISENO << "x"
           << ALTO_DISENO << ". Saliendo..." << endl;
      exit(0);
    }
  }
  calcularAdaptacion();
}

/* /////////////////////////////////////////////////////////////////////// */
void dibujarMarco(int colorPar)
{
  attron(COLOR_PAIR(colorPar));
  for (int x = 0; x < W; x++)
  {
    mvaddch(oy, ox + x, ACS_HLINE);
    mvaddch(oy + H - 1, ox + x, ACS_HLINE);
  }
  for (int y = 0; y < H; y++)
  {
    mvaddch(oy + y, ox, ACS_VLINE);
    mvaddch(oy + y, ox + W - 1, ACS_VLINE);
  }
  mvaddch(oy, ox, ACS_ULCORNER);
  mvaddch(oy, ox + W - 1, ACS_URCORNER);
  mvaddch(oy + H - 1, ox, ACS_LLCORNER);
  mvaddch(oy + H - 1, ox + W - 1, ACS_LRCORNER);
  attroff(COLOR_PAIR(colorPar));
}

/* /////////////////////////////////////////////////////////////////////// */
void barra(int y, int x, int valor, string etiqueta, int colorPar)
{
  attron(COLOR_PAIR(colorPar));
  mvprintw(oy + y, ox + x, "%-9s [", etiqueta.c_str());
  int lleno = valor / 5; // barra de 20 caracteres
  for (int i = 0; i < 20; i++)
    addch(i < lleno ? '#' : '-');
  printw("] %3d", valor);
  attroff(COLOR_PAIR(colorPar));
}

/* /////////////////////////////////////////////////////////////////////// */
// Devuelve el color de la barra segun el nivel de UN atributo "a mayor
// mejor" (energía, cordura). El hambre se maneja aparte porque es "a
// mayor peor" (0 = saciada, 100 = muere de hambre).
int colorNivel(int valor)
{
  if (valor > 60)      return 2; // verde: bien
  else if (valor > 30) return 3; // amarillo: regular
  else                 return 4; // rojo: peligro
}

/* /////////////////////////////////////////////////////////////////////// */
void mostrarTitulo()
{
    // Arte título
    std::vector<std::string> arteTitulo = {
        R"(   ____ _   _   _    ____  ____ ___    _    _   _   )",
        R"(  / ___| | | | / \  |  _ \|  _ \_ _|  / \  | \ | |  )",
        R"( | |  _| | |  / _ \ | |_) | | | | |  / _ \ |  \| |  )",
        R"( | |_| | |_| / ___ \|  _ <| |_| | | / ___ \| |\  |  )",
        R"(  \____|\___/_/   \_\_| \_\____/___/_/   \_\_| \_|  )"
    };

    // Centrar el arte del título (ancho: 55)
    int cx = (W - 55) / 2;
    if (cx < 1) cx = 1;

    attron(COLOR_PAIR(6) | A_BOLD);
    for (size_t i = 0; i < arteTitulo.size(); i++) {
        mvprintw(oy + 2 + i, ox + cx, "%s", arteTitulo[i].c_str());
    }
    attroff(COLOR_PAIR(6) | A_BOLD);

    attron(COLOR_PAIR(5));
    // Centrar el subtítulo de forma independiente (ancho: 43)
    int cxSub = (W - 43) / 2;
    if (cxSub < 1) cxSub = 1;
    mvprintw(oy + 8, ox + cxSub, "-- EL GUARDIAN DEL CEMENTERIO BRUTALISTA --");
    attroff(COLOR_PAIR(5));
}

/* /////////////////////////////////////////////////////////////////////// */
int menuPrincipal()
{
  int seleccion = JUGAR;
  int tecla;

  while (true)
  {
    // Si redimensionaron la terminal a menos de 120x40, avisar.
    pedirTerminalGrande();
    calcularAdaptacion(); // por si redimensionaron la terminal

    clear();
    dibujarMarco(5);
    mostrarTitulo();

    string opciones[NUM_OPCIONES] = { "1. JUGAR", "2. INSTRUCTIVO", "3. CREDITOS", "4. SALIR" };
    int cx = W / 2 - 9;
    if (cx < 1) cx = 1;

    for (int i = 0; i < NUM_OPCIONES; i++)
    {
      if (i == seleccion)
      {
        attron(COLOR_PAIR(6) | A_REVERSE);
        mvprintw(oy + 14 + i * 2, ox + cx, " %s ", opciones[i].c_str());
        attroff(COLOR_PAIR(6) | A_REVERSE);
      }
      else
      {
        attron(COLOR_PAIR(1));
        mvprintw(oy + 14 + i * 2, ox + cx, "  %s  ", opciones[i].c_str());
        attroff(COLOR_PAIR(1));
      }
    }

    attron(COLOR_PAIR(1));
    mvprintw(oy + H - 5, ox + 2, "Flechas + ENTER. Tamano: %dx%d", W, H);
    mvprintw(oy + H - 4, ox + 2, "Requisito mínimo de terminal: %dx%d", ANCHO_DISENO, ALTO_DISENO);
    attroff(COLOR_PAIR(1));
    refresh();

    tecla = getch();
    if (tecla == KEY_RESIZE) continue;
    if (tecla == KEY_UP)   seleccion = (seleccion + NUM_OPCIONES - 1) % NUM_OPCIONES;
    else if (tecla == KEY_DOWN) seleccion = (seleccion + 1) % NUM_OPCIONES;
    else if (tecla == '\n' || tecla == KEY_ENTER) return seleccion;
  }
}

/* /////////////////////////////////////////////////////////////////////// */
void mostrarInstructivo()
{
  clear();
  dibujarMarco(5);
  attron(COLOR_PAIR(6) | A_BOLD);
  mvprintw(oy + 2, ox + W / 2 - 8, " INSTRUCTIVO ");
  attroff(COLOR_PAIR(6) | A_BOLD);

  attron(COLOR_PAIR(1));
  mvprintw(oy + 5, ox + 4, "Eres el guardián de un cementerio brutalista. Una criatura antigua despierta");
  mvprintw(oy + 6, ox + 4, "bajo el mausoleo de hormigón... y depende de tí para sobrevivir 15 noches.");
  mvprintw(oy + 8, ox + 4, "ATRIBUTOS:");
  mvprintw(oy + 9,  ox + 6, "- HAMBRE:  0 = saciada, 100 = muere de hambre. [A] ALIMENTAR la reduce.");
  mvprintw(oy + 10, ox + 6, "- ENERGIA: si llega a 0, la criatura se apaga para siempre.");
  mvprintw(oy + 11, ox + 6, "- CORDURA: si llega a 0, la criatura enloquece y se pierde.");
  mvprintw(oy + 13, ox + 4, "ACCIONES (cada acción consume un ciclo de tiempo):");
  mvprintw(oy + 14, ox + 6, "- [A] ALIMENTAR:       reduce el hambre de la criatura.");
  mvprintw(oy + 15, ox + 6, "- [D] DESCANSAR:       recupera ENERGIA, sube un poco el hambre.");
  mvprintw(oy + 16, ox + 6, "- [R] RITUAL CALMANTE: restaura la cordura con runas antiguas.");
  mvprintw(oy + 17, ox + 6, "- [S] SIGUIENTE CICLO: deja pasar el tiempo sin hacer nada.");
  mvprintw(oy + 18, ox + 6, "- [Q] ABANDONAR:       volver al menú principal.");
  mvprintw(oy + 20, ox + 4, "CUIDADO: cada noche el cementerio sufre eventos aleatorios (vientos");
  mvprintw(oy + 21, ox + 4, "fúnebres, cuervos ladrones, alarmas) que debilitan a la criatura.");
  mvprintw(oy + 22, ox + 4, "El estado de ANIMO depende del atributo más bajo (el hambre se cuenta");
  mvprintw(oy + 23, ox + 4, "como saciedad): TRANQUILO -> INQUIETO -> SOMBRIO -> FURIOSO.");
  attroff(COLOR_PAIR(1));

  pausar("Presiona cualquier tecla para volver al menú...");
}

/* /////////////////////////////////////////////////////////////////////// */
void mostrarCreditos()
{
    clear();
    dibujarMarco(5);

    attron(COLOR_PAIR(6) | A_BOLD);
    mvprintw(oy + 2, ox + W / 2 - 5, " CREDITOS ");
    attroff(COLOR_PAIR(6) | A_BOLD);

    // Arte ASCII estilizado y alineado con raw string literals R"(...)"
    attron(COLOR_PAIR(5));
    mvprintw(oy + 7,  ox + W / 2 - 23, R"(  ____ ____  _____ ____ ___ _____ ___  ____  )");
    mvprintw(oy + 8,  ox + W / 2 - 23, R"( / ___|  _ \| ____|  _ \_ _|_   _/ _ \/ ___| )");
    mvprintw(oy + 9,  ox + W / 2 - 23, R"(| |   | |_) |  _| | | | | |  | || | | \___ \ )");
    mvprintw(oy + 10, ox + W / 2 - 23, R"(| |___|  _ <| |___| |_| | |  | || |_| |___) |)");
    mvprintw(oy + 11, ox + W / 2 - 23, R"( \____|_| \_\_____|____/___| |_| \___/|____/ )");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(1));
    mvprintw(oy + 15, ox + W / 2 - 8, "Juego creado por:");
    attroff(COLOR_PAIR(1));

    // Nombres centrados respecto al bloque de texto
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(oy + 17, ox + W / 2 - 9, "    Alan Verruá    ");
    mvprintw(oy + 18, ox + W / 2 - 9, " Florencia Olivera ");
    mvprintw(oy + 19, ox + W / 2 - 9, "Fiorella Carrettino");
    attroff(COLOR_PAIR(2) | A_BOLD);

   attron(COLOR_PAIR(3));
    mvprintw(oy + 22, ox + W / 2 - 30, "Trabajo Práctico N.2 - Informática General (Cátedra Tirigall)");
    mvprintw(oy + 23, ox + W / 2 - 19, "Universidad Nacional de las Artes (UNA)");
    mvprintw(oy + 24, ox + W / 2 - 12, "Lic. Artes Multimediales.");
    mvprintw(oy + 25, ox + W / 2 - 6, "Octubre 2026.");
    attroff(COLOR_PAIR(3));

    pausar("Presiona cualquier tecla para volver al menú...");
}

/* /////////////////////////////////////////////////////////////////////// */
void pausar(string mensaje)
{
  attron(COLOR_PAIR(3));
  mvprintw(oy + H - 3, ox + 2, "%s", mensaje.c_str());
  attroff(COLOR_PAIR(3));
  refresh();
  getch();
}

/* /////////////////////////////////////////////////////////////////////// */
void jugar()
{
  clear();
  dibujarMarco(5);

  // Pedir el nombre de la criatura (uso del objeto STRING).
  attron(COLOR_PAIR(5));
  mvprintw(oy + 8, ox + 4, "La criatura despierta bajo el mausoleo...");
  mvprintw(oy + 10, ox + 4, "Escribe su nombre (max. 20 letras) y pulsa ENTER: ");
  attroff(COLOR_PAIR(5));
  echo();
  curs_set(1);
  char buffer[21];
  getnstr(buffer, 20);
  noecho();
  curs_set(0);
  string nombre = (buffer[0] == '\0') ? "Hormigón" : string(buffer);

  Criatura criatura(nombre);

  const int CICLOS_PARA_GANAR = 15;
  bool salirAlMenu = false;
  string mensaje = "La criatura abre los ojos entre la niebla.";

  while (!salirAlMenu)
  {
    // Chequeo por si redimensionaron la terminal durante la partida.
    pedirTerminalGrande();
    calcularAdaptacion(); // por si redimensionaron la terminal
    clear();
    dibujarMarco(5);

    // Encabezado
    attron(COLOR_PAIR(6) | A_BOLD);
    mvprintw(oy + 2, ox + 2, " NOCHE %02d / %02d ", criatura.getEdad() + 1, CICLOS_PARA_GANAR);
    attroff(COLOR_PAIR(6) | A_BOLD);
    attron(COLOR_PAIR(5));
    mvprintw(oy + 2, ox + 30, " Criatura: %-20s ", criatura.getNombre().c_str());
    mvprintw(oy + 2, ox + 62, " ANIMO: %s ", criatura.getAnimoTexto().c_str());
    attroff(COLOR_PAIR(5));

    // Dibujar la criatura segun su estado de animo (arreglo + enum).
    EstadoAnimo animo = criatura.getAnimo();
    attron(COLOR_PAIR(5));
    for (int i = 0; i < 7; i++)
      mvprintw(oy + 5 + i, ox + 4, "%s", FRAMES_CRIATURA[animo][i].c_str());
    attroff(COLOR_PAIR(5));

    // Barras de atributos con colores segun nivel.
    // HAMBRE: "a mayor peor" (100 = muere de hambre).
    // ENERGIA y CORDURA: "a mayor mejor" (0 = muere).
    int bx = 40;
    int colorHambre  = criatura.getHambre()  > 60 ? 4 : (criatura.getHambre()  > 30 ? 3 : 2);
    int colorEnergia = colorNivel(criatura.getEnergia());
    int colorCordura = colorNivel(criatura.getCordura());
    barra(6, bx, criatura.getHambre(),  "HAMBRE",  colorHambre);
    barra(8, bx, criatura.getEnergia(), "ENERGÍA", colorEnergia);
    barra(10, bx, criatura.getCordura(),"CORDURA", colorCordura);

    // Mensaje del ultimo evento.
    attron(COLOR_PAIR(1));
    mvprintw(oy + 13, ox + bx, "Bitácora del guardia:");
    mvprintw(oy + 14, ox + bx, "%s", mensaje.c_str());
    attroff(COLOR_PAIR(1));

    // Acciones disponibles.
    attron(COLOR_PAIR(3));
    mvprintw(oy + 17, ox + bx, "[A] Alimentar   [D] Descansar   [R] Ritual");
    mvprintw(oy + 18, ox + bx, "[S] Siguiente ciclo             [Q] Salir al menú");
    attroff(COLOR_PAIR(3));

    refresh();
    int tecla = getch();

    if (tecla == KEY_RESIZE) continue;
    if (tecla == 'q' || tecla == 'Q') { salirAlMenu = true; continue; }

    if (tecla == 'a' || tecla == 'A')
    {
      criatura.alimentar();
      criatura.pasarTiempo();
      mensaje = "Ofrendas frescas para " + criatura.getNombre() + ".";
    }
    else if (tecla == 'd' || tecla == 'D')
    {
      criatura.descansar();
      criatura.pasarTiempo();
      mensaje = criatura.getNombre() + " duerme entre ecos fríos.";
    }
    else if (tecla == 'r' || tecla == 'R')
    {
      criatura.ritualCalmante();
      criatura.pasarTiempo();
      mensaje = "Runas antiguas calman la mente de " + criatura.getNombre() + ".";
    }
    else
    {
      criatura.pasarTiempo();
      mensaje = "El tiempo pesa sobre los muros de hormigón...";
    }

    // Verificar derrota: la criatura muere.
    if (!criatura.estaViva())
    {
      clear();
      dibujarMarco(4);

      // "DERROTA"
      std::vector<std::string> arteDerrota = {
          R"(  ____  ____  ____  ____  ___  _____    __    )",
          R"( |  _ \|  __||  _ \|  _ \/ _ \|_   _|  /  \   )",
          R"( | | | | |__ | |_) | |_) | | | |  | | / /\ \  )",
          R"( | |_| |  __||  _ <|  _ <| |_| |  | |/ /__\ \ )",
          R"( |____/|____||_| \_\_| \_\\___/   |_/_/    \_\)"
      };

      attron(COLOR_PAIR(4) | A_BOLD);
      for (size_t i = 0; i < arteDerrota.size(); i++) {
          // Restamos 22 (mitad de 44) para centrar exacto
          mvprintw(oy + 8 + i, ox + W / 2 - 22, "%s", arteDerrota[i].c_str());
      }
      attroff(COLOR_PAIR(4) | A_BOLD);

      attron(COLOR_PAIR(1));
      mvprintw(oy + 15, ox + 4, "%s ha vuelto al silencio del cementerio brutalista...", criatura.getNombre().c_str());
      attroff(COLOR_PAIR(1));

      pausar("Presiona cualquier tecla para volver al menú principal.");
      salirAlMenu = true;
    }
    // Verificar victoria: sobrevivio los 15 ciclos.
    else if (criatura.getEdad() >= CICLOS_PARA_GANAR)
    {
      clear();
      dibujarMarco(2);

      // "VICTORIA"
      std::vector<std::string> arteVictoria = {
          R"( __     __ ___   ____  _____  ___  ____   ___      _    )",
          R"( \ \   / /|_ _| / ___||_   _|/ _ \|  _ \ |_ _|    / \   )",
          R"(  \ \ / /  | | | |      | | | | | | |_) | | |    / _ \  )",
          R"(   \ V /   | | | |___   | | | |_| |  _ <  | |   / ___ \ )",
          R"(    \_/   |___| \____|  |_|  \___/|_| \_\|___| /_/   \_\)"
      };

      attron(COLOR_PAIR(2) | A_BOLD);
      for (size_t i = 0; i < arteVictoria.size(); i++) {
          // Restamos 27 (mitad de 54) para centrar exacto
          mvprintw(oy + 8 + i, ox + W / 2 - 27, "%s", arteVictoria[i].c_str());
      }
      attroff(COLOR_PAIR(2) | A_BOLD);

      attron(COLOR_PAIR(1));
      mvprintw(oy + 15, ox + 4, "%s sobrevivió las %d noches. El mausoleo sigue en pie.", criatura.getNombre().c_str(), CICLOS_PARA_GANAR);
      attroff(COLOR_PAIR(1));

      pausar("Presiona cualquier tecla para volver al menú principal.");
      salirAlMenu = true;
    }
  }
}

#include "juego.h"

// ============================================================================
//  IMPLEMENTACIÓN DE UTILIDADES
// ============================================================================
void limpiarPantalla() { system("clear"); }

void vaciarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausa() {
    cout << "\n  [Presiona ENTER para continuar...]";
    cin.get();
}

void pausaSimple() {
    cout << "\n  [Presiona ENTER...]";
    cin.get();
}

void lineaHorizontal(char c) {
    for (int i = 0; i < ANCHO; i++) cout << c;
    cout << endl;
}

void centrarTexto(string texto, int ancho) {
    int espacios = (ancho - texto.length()) / 2;
    if (espacios < 0) espacios = 0;
    for (int i = 0; i < espacios; i++) cout << " ";
    cout << texto << endl;
}

void bordeSuperior() {
    cout << "  +";
    for (int i = 0; i < ANCHO - 4; i++) cout << "=";
    cout << "+" << endl;
}

void bordeInferior() {
    cout << "  +";
    for (int i = 0; i < ANCHO - 4; i++) cout << "=";
    cout << "+" << endl;
}

void lineaVacia(int cantidad) {
    for (int v = 0; v < cantidad; v++) {
        cout << "  |";
        for (int i = 0; i < ANCHO - 4; i++) cout << " ";
        cout << "|" << endl;
    }
}

// ============================================================================
//  IMPLEMENTACIÓN DEL JUEGO
// ============================================================================
string nombreJugador;
int puntaje = 0;
bool juegoActivo = false;

void mostrarTitulo() {
    limpiarPantalla();
    cout << endl << endl;
    cout << "   ______  _____  _____       _____   ______   _____  ______   _               " << endl;
    cout << "  |  ____|/ ____|/ ____|  /\\  |  __ \\ |  ____| |  __ \\|  ____| | |        /\\   " << endl;
    cout << "  | |__  | (___ | |      /  \\ | |__) || |__    | |  | | |__    | |       /  \\  " << endl;
    cout << "  |  __|  \\___ \\| |     / /\\ \\|  ___/ |  __|   | |  | |  __|   | |      / /\\ \\ " << endl;
    cout << "  | |____ ____) | |____/ ____ \\ |     | |____  | |__| | |____  | |____ / ____ \\" << endl;
    cout << "  |______|_____/ \\_____/_/    \\_\\     |______| |_____/|______| |______/_/    \\_\\" << endl;
    cout << endl;
    cout << "   ______       _____  _    _  _    _______       _____  " << endl;
    cout << "  |  ____|/\\   |  __ \\| |  | || |  |__   __|/\\   |  __ \\ " << endl;
    cout << "  | |__  /  \\  | |  | | |  | || |     | |  /  \\  | |  | |" << endl;
    cout << "  |  __|/ /\\ \\ | |  | | |  | || |     | | / /\\ \\ | |  | |" << endl;
    cout << "  | |  / ____ \\| |__| | |__| || |____ | |/ ____ \\| |__| |" << endl;
    cout << "  |_| /_/    \\_\\_____/ \\____/ |______||_/_/    \\_\\_____/ " << endl;
    cout << endl << endl;
    
    lineaHorizontal('~');
    centrarTexto("UNA AVENTURA CONVERSACIONAL");
    centrarTexto("Creado por: Alan Verruá, Florencia Olivera y Fiorella Carrettino");
    lineaHorizontal('~');
    cout << endl;
}

void mostrarCreditos() {
    limpiarPantalla();
    bordeSuperior();
    lineaVacia(2);
    centrarTexto("CREDITOS");
    lineaVacia(2);
    centrarTexto("Desarrollado por: Alan Verruá, Florencia Olivera y Fiorella Carrettino");
    centrarTexto("Materia: Informática General (Cát. Tirigall)");
    centrarTexto("Universidad Nacional de las Artes");
    lineaVacia(2);
    centrarTexto("Junio de 2026");
    lineaVacia(2);
    bordeInferior();
    pausa();
}

void mostrarInstrucciones() {
    limpiarPantalla();
    bordeSuperior();
    lineaVacia(1);
    centrarTexto("INSTRUCCIONES DE JUEGO");
    lineaVacia(1);
    centrarTexto("Sos une estudiantx atrapadx en la UNA después de hora.");
    centrarTexto("Debes escapar resolviendo acertijos en cada aula.");
    lineaVacia(1);
    centrarTexto("COMO JUGAR:");
    centrarTexto("- Ingresa el número de la opción elegida");
    centrarTexto("- Responde correctamente para avanzar y desbloquear las puertas");
    centrarTexto("- Si fallás una pregunta, perdés el juego");
    centrarTexto("- Debés responder TODAS correctamente para poder escapar");
    lineaVacia(2);
    bordeInferior();
    pausa();
}

void pantallaIntroduccion() {
    limpiarPantalla();
    bordeSuperior();
    lineaVacia(2);
    centrarTexto("FACULTAD. CALLE VIAMONTE... 23:45 Hs...");
    lineaVacia(1);
    centrarTexto("Las luces se apagan... las puertas se cierran...");
    centrarTexto("Solo queda una salida, pero está bloqueada por acertijos.");
    lineaVacia(2);
    bordeInferior();
    pausa();
}

void pedirNombre() {
    limpiarPantalla();
    bordeSuperior();
    lineaVacia(3);
    centrarTexto("¿Como es tu nombre, estudiantx?");
    lineaVacia(3);
    cout << "  |                                              Indique su nombre: ";
    
    getline(cin, nombreJugador);
    if (nombreJugador.empty()) nombreJugador = "Estudiantx";
    
    lineaVacia(3);
    centrarTexto("Hola " + nombreJugador + ", ¡INTENTA ESCAPAR!");
    lineaVacia(3);
    bordeInferior();
    pausa();
}

bool pantallaPreparacion() {
    limpiarPantalla();
    bordeSuperior();
    lineaVacia(2);
    centrarTexto(nombreJugador + ", ¿Por qué te quedaste hasta tan tarde en la facultad?");
    lineaVacia(2);
    centrarTexto("1. Me quedé estudiando");
    centrarTexto("2. Me quedé dormidx");
    lineaVacia(2);
    bordeInferior();

    int opcion;
    cout << "\n  Ingrese Opción: ";
    cin >> opcion;
    vaciarBuffer();

    limpiarPantalla();
    bordeSuperior();
    lineaVacia(3);
    
    if (opcion == 1) centrarTexto("PROFE: JAJA mirá que dedicadx...");
    else centrarTexto("PROFE: Así estamos, país...");
    
    lineaVacia(2);
    centrarTexto("¿Estás preparadx para el desafío? (S/N): ");
    lineaVacia(2);
    bordeInferior();

    char respuesta;
    cout << "\n  Respuesta: ";
    cin >> respuesta;
    vaciarBuffer();

    return (respuesta == 'S' || respuesta == 's');
}

void cuentaRegresiva() {
    limpiarPantalla();
    cout << "\n\n"; centrarTexto("Preparate..."); cout << "\n";
    usleep(800000);
}

// ============================================================================
//  PREGUNTAS
// ============================================================================

bool pregunta1() {
    limpiarPantalla(); 
    bordeSuperior(); 
    lineaVacia(1);
    centrarTexto("PANTALLA 1: AULA DE INFORMATICA GENERAL"); 
    lineaVacia(1);
    
    cout << "  |          .---------------------------------------------------------------------------------------------.           |" << endl;
    cout << "  |          |  _________________________________________________________________________________________  |           |" << endl;
    cout << "  |          | | Tengo un inicio pero nunca un final. Si me ejecutas, el programa no avanza. ¿Que soy?   | |           |" << endl;
    cout << "  |          | |_________________________________________________________________________________________| |           |" << endl;
    cout << "  |          '---------------------------------------------------------------------------------------------'           |" << endl;
    
    lineaVacia(1);
    centrarTexto("PROFESOR: Tengo un inicio pero nunca un final.");
    centrarTexto("Si me ejecutas, el programa no avanza. ¿Que soy?");
    lineaVacia(1);
    centrarTexto("1) Bucle  |  2) Bucle infinito  |  3) Variable");
    lineaVacia(1); 
    bordeInferior();
    
    int respuesta; 
    cout << "\n  Ingrese Opcion: "; 
    cin >> respuesta; 
    vaciarBuffer();
    
    limpiarPantalla(); 
    bordeSuperior(); 
    lineaVacia(3);
    
    if (respuesta == 2) { 
        centrarTexto("CORRECTO!!"); 
        centrarTexto("La puerta del aula se abre..."); 
        puntaje += 25; 
        lineaVacia(3); 
        bordeInferior(); 
        pausa(); 
        return true; 
    } else { 
        centrarTexto("INCORRECTO!!!"); 
        centrarTexto("La alarma de seguridad se activa..."); 
        lineaVacia(3); 
        bordeInferior(); 
        pausa(); 
        return false; 
    }
}
   
bool pregunta2() {
    limpiarPantalla(); bordeSuperior(); lineaVacia(1);
    centrarTexto("PANTALLA 2: ..."); lineaVacia(1);
    
    
}

bool pregunta3() {
    limpiarPantalla(); bordeSuperior(); lineaVacia(1);
    centrarTexto("PANTALLA 3: ..."); lineaVacia(1);
    
    
}

bool pregunta4() {
    limpiarPantalla(); bordeSuperior(); lineaVacia(1);
    centrarTexto("PANTALLA 4: ..."); lineaVacia(1);
    
    
}

// ============================================================================
//  PANTALLAS FINALES Y BUCLE DE JUEGO
// ============================================================================

void pantallaVictoria() {
    limpiarPantalla();
    cout << endl << endl;
    cout << "   _______  _______  ___      ___  _______  _______  _______  __  " << endl;
    cout << "  |       ||       ||   |    |   ||       ||       ||       ||  | " << endl;
    cout << "  |  _____||   _   ||   |    |   ||  _____||_     _||    ___||  | " << endl;
    cout << "  | |_____ |  |_|  ||   |    |   || |_____   |   |  |   |___ |  | " << endl;
    cout << "  |_____  ||       ||   |___ |   ||_____  |  |   |  |    ___||__| " << endl;
    cout << "   _____| ||   _   ||       ||   | _____| |  |   |  |   |___  __  " << endl;
    cout << "  |_______||__| |__||_______||___||_______|  |___|  |_______||__| " << endl;
    cout << endl;

    bordeSuperior(); lineaVacia(2);
    centrarTexto("FELICITACIONES " + nombreJugador + "!");
    lineaVacia(1);
    centrarTexto("Escapaste del Laberinto de la Facultad!");
    lineaVacia(1);
    centrarTexto("Puntaje final: " + to_string(puntaje) + "/100");
    lineaVacia(1);
    centrarTexto("Ahora, sí... ponete a estudiar!");
    lineaVacia(2); bordeInferior(); pausa();
}

void pantallaDerrota() {
    limpiarPantalla();
    cout << endl << endl;
    cout << "   _______  __    _  _______  _______  ______   ______   _______  ______   __   __   __   __  " << endl;
    cout << "  |       ||  |  | ||       ||       ||    _ | |    _ | |       ||      | |  | |  | |  | |  | " << endl;
    cout << "  |    ___||   |_| ||       ||    ___||   | || |   | || |   _   ||  _    ||  |_|  | |  | |  | " << endl;
    cout << "  |   |___ |       ||       ||   |___ |   |_||_|   |_||_|  |_|  || | |   ||       | |  | |  | " << endl;
    cout << "  |    ___||  _    ||      _||    ___||    __  |    __  |       || |_|   ||       | |__| |__| " << endl;
    cout << "  |   |___ | | |   ||     |_ |   |___ |   |  | |   |  | |   _   ||       ||   _   |  __   __  " << endl;
    cout << "  |_______||_|  |__||_______||_______||___|  |_|___|  |_|__| |__||______| |__| |__| |__| |__| " << endl;
    cout << endl;

    bordeSuperior(); lineaVacia(2);
    centrarTexto("LO SIENTO " + nombreJugador + "...");
    lineaVacia(1);
    centrarTexto("No lograste escapar del Laberinto de la Facultad.");
    lineaVacia(1);
    centrarTexto("Puntaje obtenido: " + to_string(puntaje) + "/100");
    lineaVacia(2); bordeInferior(); pausa();
}

void jugar() {
    puntaje = 0; 
    juegoActivo = true;
    
    pantallaIntroduccion();
    pedirNombre();
    
    if (!pantallaPreparacion()) {
        limpiarPantalla(); bordeSuperior(); lineaVacia(3);
        centrarTexto("Bueno, cuando estes listx volvé!!! te estaremos esperando muejjejej");
        lineaVacia(3); bordeInferior(); pausa(); return;
    }
    
    cuentaRegresiva();
    
    int pantallaActual = 1;
    bool sigueVivo = true;

    // BUCLE DE PREGUNTAS
    while (pantallaActual <= 4 && sigueVivo && juegoActivo) {
        bool resultado = false;

        switch (pantallaActual) {
            case 1: resultado = pregunta1(); break;
            case 2: resultado = pregunta2(); break;
            case 3: resultado = pregunta3(); break;
            case 4: resultado = pregunta4(); break;
        }

        if (!resultado) sigueVivo = false; // Si responde mal, sigueVivo se vuelve false y corta el while
        
        pantallaActual++;
    }

    if (sigueVivo) pantallaVictoria();
    else pantallaDerrota();
}

void menuPrincipal() {
    int opcion = 0;
    bool salir = false;

    while (!salir) {
        mostrarTitulo();
        cout << "                                    |     1- Iniciar juego                   |" << endl;
        cout << "                                    |     2- Instrucciones                   |" << endl;
        cout << "                                    |     3- Creditos                        |" << endl;
        cout << "                                    |     4- Salir                           |" << endl;
        cout << "\n                                    Ingrese Opcion: ";
        
        cin >> opcion;
        vaciarBuffer();

        switch (opcion) {
            case 1: jugar(); break;
            case 2: mostrarInstrucciones(); break;
            case 3: mostrarCreditos(); break;
            case 4: salir = true; break;
        }
    }
}

int main() {
    system("resize -s 40 120 2>/dev/null || true");
    menuPrincipal();
    return 0;
}
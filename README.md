Escape de la Facultad - TP1
Preentrega del Trabajo Práctico 1 
Informática General (Cód. 67) (Cát. Tirigall) 
Lic. en Artes Multinediales. Universidad Nacional de las Artes.

##Integrantes del Grupo:

* Alan Verruá
* Florencia Olivera
* Fiorella Carrettino

##Descripción del Proyecto:
Es una aventura conversacional desarrollada íntegramente en C++. 
El jugador toma el rol de un estudiante que quedó atrapado en la facultad después de hora y debe resolver una serie de acertijos para poder desbloquear las puertas y escapar.

##Instrucciones de Compilación y Ejecución
El proyecto está preparado para correr en entornos Linux / WSL (Ubuntu). 
Para probar el juego, abrir la terminal en el directorio del proyecto y ejecutar los siguientes comandos:

1. Para compilar:
g++ main.cpp -o escape

2. Para ejecutar:
./escape

##Estructura del Código y Modularización.

Para mantener el proyecto organizado, legible y facilitar el trabajo colaborativo, el código se dividió en módulos específicos:

* **`utilidades.h`:** Funciona como nuestra biblioteca personalizada de herramientas de consola y formateo visual. Aquí se abstraen todas las funciones repetitivas para no ensuciar la lógica del juego.
* Incluye:
  * Control de consola: `limpiarPantalla()`, `pausa()`, `vaciarBuffer()` (vital para evitar bugs entre ingresos de números y texto).
  * Interfaz gráfica (ASCII): Funciones paramétricas como `lineaHorizontal()`, `centrarTexto()`, `bordeSuperior()` y `bordeInferior()`, que garantizan un diseño uniforme en todas las pantallas.

* **`juego.h`:** Archivo de cabecera (header) destinado a aislar las declaraciones, prototipos de las funciones principales y variables globales del estado del jugador, separando el "qué hace" del "cómo lo hace".

* **`main.cpp`:** Es el núcleo lógico del programa. Contiene el punto de entrada (`main()`), el gestor del menú principal y el bucle central de la partida (`jugar()`). Aquí se interconectan las utilidades gráficas con las pantallas de historia, la evaluación de los 4 acertijos (`pregunta1()`, etc.) y el sistema de condiciones de victoria o derrota.

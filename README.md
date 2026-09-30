Guardián Brutalista - T. P. 2
Entrega del Trabajo Práctico 2
Informática General (Cód. 67) (Cát. Tirigall) 
Lic. en Artes Multinediales. Universidad Nacional de las Artes.

# EL GUARDIÁN DEL CEMENTERIO BRUTALISTA — TP2

Juego de gestión de una criatura antigua que despierta bajo un mausoleo
de hormigón. El jugador debe mantenerla con vida durante 15 noches
cuidando sus tres atributos: **hambre**, **energía** y **cordura**.

## Autores

- Alan Verruá
- Florencia Olivera
- Fiorella Carrettino

## Requisitos

- Compilador de C++ (g++)
- Biblioteca **ncurses** instalada
- Terminal de al menos **120 columnas x 40 filas** (el juego lo verifica
  y muestra un mensaje si la ventana es más chica)

## Compilación

```bash
g++ main.cpp Criatura.cpp -o guardian -lncurses
```

## Ejecución

```bash
./guardian
```

## Cómo jugar

Cada acción consume un ciclo de tiempo (una noche). Sobreviví las 15
noches para ganar; si algún atributo llega a su límite fatal, la
criatura muere y pierdes la partida.

| Tecla | Acción |
|-------|--------|
| `A` | Alimentar: reduce el **hambre** (0 = saciada, 100 = muere de hambre) |
| `D` | Descansar: recupera **energía** (si llega a 0, se apaga) |
| `R` | Ritual calmante: restaura la **cordura** (si llega a 0, enloquece) |
| `S` | Dejar pasar el tiempo sin hacer nada |
| `Q` | Abandonar la partida y volver al menú |

En el menú principal se navega con las **flechas** y **ENTER**.

Cada noche el cementerio sufre eventos aleatorios (vientos fúnebres,
cuervos ladrones, alarmas) que debilitan a la criatura. El **estado de
ánimo** (TRANQUILO → INQUIETO → SOMBRÍO → FURIOSO) depende del atributo
más bajo —contando el hambre al revés, como saciedad— y cambia el arte
ASCII de la criatura.

## Estructura del proyecto

| Archivo | Contenido |
|---------|-----------|
| `Criatura.h` | Declaración de la clase `Criatura` y el enum `EstadoAnimo` |
| `Criatura.cpp` | Implementación de la clase `Criatura` (incluye la propiedad estática `totalCriaturas`) |
| `main.cpp` | Interfaz ncurses: menú, instructivo, créditos, pantalla de juego, arte ASCII |
| `README.md` | Este archivo |

## Técnicas utilizadas (consigna TP2)

- ncurses con colores (`init_pair`, `COLOR_PAIR`) y atributos (`A_BOLD`, `A_REVERSE`)
- Enumeraciones (`OpcionMenu`, `EstadoAnimo`)
- Números aleatorios (`rand`, `srand`)
- Objetos `string`
- Arreglos (frames ASCII de la criatura indexados por el enum) y `vector`
- Funciones y procedimientos
- Clase `Criatura` separada en `.h` / `.cpp`
- Título ASCII, instructivo, créditos y vuelta al menú
- Chequeo de terminal 120x40 con mensaje al usuario

# Manual de Usuario del Programa de Dibujo de Figuras

## Introducción
Este programa permite dibujar diversas figuras geométricas en la consola de Windows utilizando las teclas del teclado para desplazarse. Las figuras incluyen triángulos, cuadrados, rectángulos, círculos, líneas, rombos y hexágonos. Además, el programa permite seleccionar diferentes punteros y colores, además de poder guardar la disposición de las figuras en un archivo, o bien poder cargar las figuras de un archivo para mostrar en la pantalla.

## Requisitos del Sistema
- Sistema Operativo: Windows
- IDE: CodeBlocks

## Compilación y Ejecución
1. Abre el proyecto en CodeBlocks.
2. En la barra de herramientas, selecciona "Build" y luego "Build and Run" (F9).

# Uso del Programa

## Interfaz de Menú
Al ejecutar el programa, se presenta un menú con las siguientes opciones:

- F1 - Triángulo
- F2 - Cuadrado
- F3 - Rectángulo
- F4 - Círculo
- F5 - Línea
- F6 - Rombo
- F7 - Hexágono
- F8 - Elegir Puntero
- F9 - Limpiar Pantalla
- F10 - Color Puntero
- F12 - Grabar Pantalla
- CTRL + A - Cargar Archivo

## Navegación del Menú
Utiliza las teclas F1 a F12 para seleccionar la opción deseada.
Para navegar dentro del menú, usa las teclas de dirección (a, w, d, s).

## Dibujar Figuras
Para dibujar una figura:

1. Selecciona la figura deseada utilizando la tecla correspondiente (F1 a F7).
2. Ingresa los parámetros solicitados cuando se te indique.

*Nota: La figura se dibujará a partir del último punto desde donde se presionó la tecla para dibujar.*

## Orientación de las Figuras
Al seleccionar la orientación de una figura, utiliza las siguientes teclas:

- Flecha Arriba
- Flecha Abajo
- Flecha Derecha
- Flecha Izquierda

## Opciones Adicionales
- F8 - Elegir Puntero: Cambia el carácter utilizado para dibujar las figuras.
- F9 - Limpiar Pantalla: Limpia la pantalla y elimina todas las figuras.
- F10 - Color Puntero: Cambia el color del puntero utilizado para dibujar.
- F12 - Grabar Pantalla: Guarda la disposición actual de las figuras en un archivo.
- CTRL + A - Cargar Archivo: Carga el archivo con extensión .txt para mostrar en pantalla.

# Manual Tecnico del Programa de Dibujo de Figuras

## Introduccion

El sistema de gestión de formas es una aplicación de consola diseñada para permitir al usuario seleccionar y manipular diversas formas geométricas utilizando teclas de función y combinaciones de teclas. La aplicación está estructurada en un solo programa en C++ y utiliza la biblioteca de Windows para manejar la entrada del teclado y la visualización.

## Procedimientos de Instalación

### Compilación del Código

- Abra su entorno de desarrollo C++.

- Clone el repositorio del proyecto desde GitHub usando el siguiente comando:

```
git clone https://github.com/rvald3z/ProyectoFinalProgramacionI.git
```
- Entra en la carpeta del proyecto.

- Compile el código fuente utilizando el IDE CodeBlocks

### Ejecución del Programa

- Navegue a la carpeta del proyecto compilado.
- Ejecute el archivo ejecutable generado (por ejemplo, GestionDeFormas.exe).

## Componentes Principales

Interfaz de Usuario: Basada en la consola, donde el usuario selecciona opciones mediante el teclado.
Módulo de Entrada: Maneja la captura de eventos de teclado.

## Algoritmos

### Detección de Entrada del Teclado

```
if (GetKeyState(VK_F1) & 0x8000) {
    // Acción para F1
    opcionSeleccionada = 1;
    inMenu = true;
}
```

### Movimiento del Cursor

```
if (_kbhit()) {
    char key = _getch();
    key = tolower(key);
    switch (key) {
    case 'a':
        posicionX--;
        break;
    case 'd':
        posicionX++;
        break;
    case 'w':
        posicionY--;
        break;
    case 's':
        posicionY++;
        break;
    }
}
```

## Estructuras de Datos

## Modelo

```
struct Figura {
    int idFigura;
    COORD coord;
    int valor1;
    int valor2;
    char puntero;
    int color;
    char orientacion;
};
```

### Variables Globales

```
int ancho_pantalla = 110;
int alto_pantalla = 30;
char PUNTERO = '+';
int COLOR = 15;
int posicionX = ancho_pantalla / 2;
int posicionY = alto_pantalla / 2;
int opcionSeleccionada = 1;
```

## Funciones

``` 
void void gotoxy(int x, int y, char p, int color): Función para mover el cursor a una posición específica y cambiar el color y el carácter del puntero.
void mostrarMenu(): Función para mostrar las opciones del menú.
void dibujarCuadrado(Figura nuevoCuadrado): Función para dibujar un cuadrado.
void dibujarTriangulo(Figura nuevoTriangulo): Función para dibujar un triángulo.
void dibujarRectangulo(Figura nuevoRectangulo): Función para dibujar un rectángulo.
void dibujarCirculo(Figura nuevoCirculo): Función para dibujar un círculo.
void dibujarLinea(Figura nuevaLinea): Función para dibujar una línea.
void dibujarRombo(Figura nuevoRombo): Función para dibujar un rombo.
void dibujarHexagono(Figura nuevoHexagono): Función para dibujar un hexágono.
void cargar(): Función para dibujar todas las figuras que se encuntren en un archivo.
void limpiarFiguras(): Función para limpiar la pantalla y eliminar todas las figuras.
void getOrientacion(): Función para obtener la orientación de una figura.
```

## Librerias

- `#include <iostream>`: Esta es una librería estándar de C++ que proporciona las funciones básicas de entrada y salida. Contiene las funciones `std::cout` y `std::cin` para imprimir en la consola y leer datos del usuario, respectivamente.

- `#include <windows.h>`: Esta es una librería específica de Windows que proporciona acceso a muchas funciones de la API de Windows. Contiene funciones para manipular ventanas, procesos, hilos, manejo de memoria y otras operaciones relacionadas con el sistema operativo Windows. Algunas funciones que utilizaste, como `GetKeyState`, `GetAsyncKeyState` y `Sleep`, provienen de esta librería.

- `#include <conio.h>`: Esta librería proporciona funciones para manipular la entrada del teclado y la pantalla en modo consola en sistemas Windows. Contiene funciones como `_kbhit()` y `_getch()` que permiten detectar si se ha presionado una tecla y leer la entrada del teclado sin necesidad de presionar Enter, respectivamente.

- `#include <vector>`: Esta es una librería estándar de C++ que proporciona la clase `std::vector`, que es una implementación de un contenedor dinámico de elementos. Permite almacenar y manipular colecciones de objetos de manera dinámica.

- `#include <fstream>`: Esta librería estándar de C++ proporciona clases y funciones para realizar operaciones de entrada y salida de archivos. Contiene las clases `std::ifstream` y `std::ofstream` para leer y escribir archivos, respectivamente.

- `#include <sstream>`: Esta librería estándar de C++ proporciona clases y funciones para realizar operaciones de entrada y salida en cadenas de texto. Contiene la clase `std::stringstream`, que permite leer y escribir datos en un `std::string` como si fuera un flujo de entrada o salida.

- `#include <string>`: Esta es una librería estándar de C++ que proporciona la clase `std::string`, que representa una cadena de texto. Contiene funciones y operadores para manipular cadenas de caracteres de manera eficiente.

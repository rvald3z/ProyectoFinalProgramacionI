#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cmath>


using namespace std;

int ancho_pantalla = 30;
int alto_pantalla = 30;
const char PUNTERO = '+';
int posicionX = ancho_pantalla / 2;
int posicionY = alto_pantalla / 2;

struct Figura {
    int idFigura;
    COORD coord;
    int valor1;
    int valor2;
};

vector<Figura> figuras;

void gotoxy(int x, int y, char c) {
    COORD coord;

    if (x == -1) {
        coord.X = ancho_pantalla;
        posicionX = ancho_pantalla;
    }
    else if (x > ancho_pantalla) {
        coord.X = 0;
        posicionX = 0;
    }
    else {
        coord.X = x;
    }

    if (y == -1) {
        coord.Y = alto_pantalla;
        posicionY = alto_pantalla;
    }
    else if (y > alto_pantalla) {
        coord.Y = 0;
        posicionY = 0;
    }
    else {
        coord.Y = y;
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    cout << c;
}

void dibujarTriangulo(Figura trianguloNuevo) {
    COORD coord;

    int base = trianguloNuevo.valor1;
    int altura = base / 2 * sqrt(3);

    coord.X = trianguloNuevo.coord.X;
    coord.Y = trianguloNuevo.coord.Y;

    for (int i = 0; i < altura; ++i) {
        gotoxy(coord.X - i, coord.Y + i, PUNTERO);
        gotoxy(coord.X + i, coord.Y + i, PUNTERO);
    }

    for (int j = coord.X - altura; j <= coord.X + altura; ++j) {
        gotoxy(j, coord.Y + altura, PUNTERO);
    }
}



void dibujarCuadrado(Figura nuevoCuadrado) {
    COORD coord;
    for (int fila = 0; fila < nuevoCuadrado.valor1; ++fila) {
        for (int columna = 0; columna < nuevoCuadrado.valor1; ++columna) {
            coord.X = (nuevoCuadrado.coord.X + columna + ancho_pantalla) % ancho_pantalla;
            coord.Y = (nuevoCuadrado.coord.Y + fila + alto_pantalla) % alto_pantalla;
            gotoxy(coord.X, coord.Y, PUNTERO);
        }
    }
}



void dibujarRectangulo(Figura nuevoRectangulo) {
    COORD coord;
    for (int fila = 0; fila < nuevoRectangulo.valor2; ++fila) {
        for (int columna = 0; columna < nuevoRectangulo.valor1; ++columna) {
            coord.X = (nuevoRectangulo.coord.X + columna + ancho_pantalla) % ancho_pantalla;
            coord.Y = (nuevoRectangulo.coord.Y + fila + alto_pantalla) % alto_pantalla;
            gotoxy(coord.X, coord.Y, PUNTERO);
        }
    }
}


void dibujarCirculo(Figura nuevoCirculo) {
}





void cargar() {
    for (const Figura& figura : figuras) {
        if (figura.idFigura == 1) {
            dibujarTriangulo(figura);
        } else if (figura.idFigura == 2) {
            dibujarCuadrado(figura);
        } else if (figura.idFigura == 3) {
            dibujarRectangulo(figura);
        } else if (figura.idFigura == 4) {
            dibujarCirculo(figura);
        }
    }
}


void limpiarFiguras() {
    system("cls");
    cout<<"Limpiando la pantalla, por favor espere....";
    Sleep(2000);
    figuras.clear();
}

void menu() {
    system("cls");
    cout << "Seleccione la figura que desea dibujar:\n";
    cout << "1. Triangulo\n";
    cout << "2. Cuadrado\n";
    cout << "3. Rectangulo\n";
    cout << "4. Circulo\n";
    cout << "5. Limpiar Figuras\n";
    cout << "Presione Esc para volver a la pantalla de dibujo!\n";
}

int main() {
    bool inMenu = false;
    gotoxy(posicionX, posicionY, PUNTERO);

    while (true) {
        system("cls");
        cargar();
        gotoxy(posicionX, posicionY, PUNTERO);

        if (inMenu) {
            menu();
            char menuKey;
            do {
                menuKey = _getch();
            } while (menuKey != '1' && menuKey != '2' && menuKey != '3' && menuKey != '4' &&  menuKey!= '5' && menuKey != VK_ESCAPE);

            if (menuKey == '1') {
                cout << "Ingrese la base del triangulo: ";
                int baseTriangulo;
                cin >> baseTriangulo;
                Figura nuevoTriangulo;
                nuevoTriangulo.idFigura = 1;
                nuevoTriangulo.valor1 = baseTriangulo;
                nuevoTriangulo.coord.X = posicionX;
                nuevoTriangulo.coord.Y = posicionY;
                dibujarTriangulo(nuevoTriangulo);
                figuras.push_back(nuevoTriangulo);
                inMenu = false;
            }
            if (menuKey == '2') {
                cout << "Ingrese el lado del cuadrado: ";
                int ladoCuadrado;
                cin >> ladoCuadrado;
                Figura nuevoCuadrado;
                nuevoCuadrado.idFigura = 2;
                nuevoCuadrado.valor1 = ladoCuadrado;
                nuevoCuadrado.coord.X = posicionX;
                nuevoCuadrado.coord.Y = posicionY;
                dibujarCuadrado(nuevoCuadrado);
                figuras.push_back(nuevoCuadrado);
                inMenu = false;
            }
            if (menuKey == '3') {
                cout << "Ingrese la base del rectangulo: ";
                int baseRectangulo;
                cin >> baseRectangulo;
                cout << "Ingrese el alto del rectangulo: ";
                int altoRectangulo;
                cin >> altoRectangulo;
                Figura nuevoRectangulo;
                nuevoRectangulo.idFigura = 3;
                nuevoRectangulo.valor1 = baseRectangulo;
                nuevoRectangulo.valor2 = altoRectangulo;
                nuevoRectangulo.coord.X = posicionX;
                nuevoRectangulo.coord.Y = posicionY;
                dibujarRectangulo(nuevoRectangulo);
                figuras.push_back(nuevoRectangulo);
                inMenu = false;
            }
            if (menuKey == '4') {
                cout << "Ingrese el radio del circulo: ";
                int radioCirculo;
                cin >> radioCirculo;
                Figura nuevoCirculo;
                nuevoCirculo.idFigura = 4;
                nuevoCirculo.valor1 = radioCirculo;
                nuevoCirculo.coord.X = posicionX;
                nuevoCirculo.coord.Y = posicionY;
                dibujarCirculo(nuevoCirculo);
                figuras.push_back(nuevoCirculo);
                inMenu = false;
            }
            if (menuKey == '5') {
                limpiarFiguras();
                inMenu = false;
            }
            if (menuKey == VK_ESCAPE) {
                inMenu = false;
            }
        }
        else {
            if (GetKeyState(VK_F12) & 0x8000) {
                inMenu = true;
            }

            if (_kbhit()) {
                char key = _getch();
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
        }

        Sleep(100);
    }
    return 0;
}

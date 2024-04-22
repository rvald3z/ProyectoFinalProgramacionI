#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

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
    cout << c << "(" << x << "," << y << ")";
}

void dibujarTriangulo(){
}

void dibujarCuadrado(Figura nuevoCuadrado) {
}

void dibujarRectangulo(){
}

void dibujarCirculo(){
}


void cargar() {
    for (const Figura& figura : figuras) {
        if (figura.idFigura == 2) {
            dibujarCuadrado(figura);
        }
    }
}

void menu() {
    system("cls");
    cout << "Seleccione la figura que desea dibujar:\n";
    cout << "1. Triangulo\n";
    cout << "2. Cuadrado\n";
    cout << "3. Rectangulo\n";
    cout << "4. Circulo\n";
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
            } while (menuKey != '1' && menuKey != '2' && menuKey != '3' && menuKey != '4' && menuKey != VK_ESCAPE);

            if (menuKey == '1') {
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
                inMenu = false;
            }
            if (menuKey == '4') {
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

#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int ancho_pantalla = 30;
int alto_pantalla = 30;
const char PUNTERO = '+';
int posicionX = ancho_pantalla / 2;
int posicionY = alto_pantalla / 2;

struct figuras {
};

void gotoxy(int x, int y, char c) {
    COORD coord;

    if (x == -1) {
        coord.X = ancho_pantalla;
        posicionX = ancho_pantalla;
    }
    else if (x > ancho_pantalla) {
        coord.X = 1;
        posicionX = 1;
    }
    else {
        coord.X = x;
    }

    if (y == -1) {
        coord.Y = alto_pantalla;
        posicionY = alto_pantalla;
    }
    else if (y > alto_pantalla) {
        coord.Y = 1;
        posicionY = 1;
    }
    else {
        coord.Y = y;
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << c;
}

void cuadrado(int lado) {

    for (int i = 0; i < lado; i++) {
        for (int j = 0; j < lado; j++) {
            gotoxy(posicionX + j, posicionY + i, PUNTERO);
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
    cout << "Presione Esc para volver a la pantalla de dibujo!";
}

int main() {
    bool inMenu = false;

    while (true) {
        system("cls");
        gotoxy(posicionX, posicionY, PUNTERO);

        if (GetKeyState(VK_F12) & 0x8000) {
            menu();
            char menuKey;
            do {
                menuKey = _getch();
            } while (menuKey != '1' && menuKey != '2' && menuKey != 'q' && menuKey != 'Q');

            if (menuKey == '1') {
                cout << "Triangulo";
            } else if (menuKey == '2') {
                cout << "Ingrese el lado del cuadrado: ";
                int ladoCuadrado;
                cin >> ladoCuadrado;
                cuadrado(ladoCuadrado);
            } else if (menuKey == 'q' || menuKey == 'Q') {
                break;
            }
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
                case 'q':
                    return 0;
                }
        }
        Sleep(100);
    }
    return 0;
}

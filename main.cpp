#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <algorithm>

using namespace std;

int ancho_pantalla = 110;
int alto_pantalla = 30;
const char PUNTERO = '+';
int posicionX = ancho_pantalla / 2;
int posicionY = alto_pantalla / 2;
int opcionSeleccionada = 1;

struct Figura {
    int idFigura;
    COORD coord;
    int valor1;
    int valor2;
};

vector<Figura> figuras;

void menu() {
    cout << "F1-Triangulo\t";
    cout << "F2-Cuadrado\t";
    cout << "F3-Rectangulo\t";
    cout << "F4-Circulo\t" ;
    cout << "F5-Linea\t";
    cout << "F6-Rombo\t" ;
    cout << "F7-Hexagono\t"<<endl;
    cout << endl;
    cout << "F8-Elegir Puntero\t";
    cout << "F9-Limpiar Pantalla\t";
    cout << "F10-Color Puntero\t";
    cout << "F12-Grabar Pantalla\t";
}

void gotoxy(int x, int y, char p, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;

    if (x == -1) {
        coord.X = ancho_pantalla;
    } else if (x > ancho_pantalla) {
        coord.X = 0;
    } else {
        coord.X = x;
    }

    if (y == -1) {
        coord.Y = alto_pantalla;
    } else if (y > alto_pantalla) {
        coord.Y = 0;
    } else {
        coord.Y = y;
    }

    SetConsoleCursorPosition(hConsole, coord);
    SetConsoleTextAttribute(hConsole, color);
    cout << p;
}

void dibujarTriangulo(Figura trianguloNuevo) {
    int base = trianguloNuevo.valor1;
    int altura = trianguloNuevo.valor1;

    for (int i = 0; i < altura; ++i) {
        int x1 = (trianguloNuevo.coord.X - i + ancho_pantalla) % ancho_pantalla;
        int x2 = (trianguloNuevo.coord.X + i + ancho_pantalla) % ancho_pantalla;
        int y = (trianguloNuevo.coord.Y + i + alto_pantalla) % alto_pantalla;

        if(x1 == x2){
            gotoxy(x1, y, PUNTERO, 12);
        } else {
            gotoxy(x1, y, PUNTERO, 15);
            gotoxy(x2, y, PUNTERO, 15);
        }
    }

    for (int j = trianguloNuevo.coord.X - altura + 1; j <= trianguloNuevo.coord.X + altura - 1; ++j) {
        int x = (j + ancho_pantalla) % ancho_pantalla;
        int y = (trianguloNuevo.coord.Y + altura + alto_pantalla - 1) % alto_pantalla;
        gotoxy(x, y, PUNTERO, 15);
    }
}

void dibujarCuadrado(Figura nuevoCuadrado) {
    COORD coord;
    int lado = nuevoCuadrado.valor1;

    for (int fila = 0; fila < lado; ++fila) {
        for (int columna = 0; columna < lado; ++columna) {
            if (fila == 0 && columna == 0) {
                coord.X = (nuevoCuadrado.coord.X + columna + ancho_pantalla) % ancho_pantalla;
                coord.Y = (nuevoCuadrado.coord.Y + fila + alto_pantalla) % alto_pantalla;
                gotoxy(coord.X, coord.Y, PUNTERO, 12);
            } else if (fila == 0 || fila == lado - 1 || columna == 0 || columna == lado - 1) {
                coord.X = (nuevoCuadrado.coord.X + columna + ancho_pantalla) % ancho_pantalla;
                coord.Y = (nuevoCuadrado.coord.Y + fila + alto_pantalla) % alto_pantalla;
                gotoxy(coord.X, coord.Y, PUNTERO, 15);
            }
        }
    }
}

void dibujarRectangulo(Figura nuevoRectangulo) {
    COORD coord;
    int base = nuevoRectangulo.valor1;
    int altura = nuevoRectangulo.valor2;

    for (int fila = 0; fila < altura; ++fila) {
        for (int columna = 0; columna < base; ++columna) {
            if (fila == 0 && columna == 0) {
                coord.X = (nuevoRectangulo.coord.X + columna + ancho_pantalla) % ancho_pantalla;
                coord.Y = (nuevoRectangulo.coord.Y + fila + alto_pantalla) % alto_pantalla;
                gotoxy(coord.X, coord.Y, PUNTERO, 12);
            } else if (fila == 0 || fila == altura - 1 || columna == 0 || columna == base - 1) {
                coord.X = (nuevoRectangulo.coord.X + columna + ancho_pantalla) % ancho_pantalla;
                coord.Y = (nuevoRectangulo.coord.Y + fila + alto_pantalla) % alto_pantalla;
                gotoxy(coord.X, coord.Y,PUNTERO, 15);
            }
        }
    }
}

void dibujarCirculo(Figura nuevoCirculo) {
    COORD coord;
    COORD coordPunto;
    int radio = nuevoCirculo.valor1;
    bool flag = false;

    for (int i = -radio; i <= radio; ++i) {
        for (int j = -radio; j <= radio; ++j) {
            if (i * i + j * j <= radio * radio + radio/2 && i * i + j * j >= radio * radio - radio/2) {

                if(!flag){
                    coordPunto.X = nuevoCirculo.coord.X;
                    coordPunto.Y = nuevoCirculo.coord.Y;
                    gotoxy(coordPunto.X, coordPunto.Y, PUNTERO, 12);
                    flag = true;
                }

                coord.X = (nuevoCirculo.coord.X + j + ancho_pantalla) % ancho_pantalla;
                coord.Y = (nuevoCirculo.coord.Y + i + alto_pantalla) % alto_pantalla;
                gotoxy(coord.X, coord.Y, PUNTERO, 15);
            }
        }
    }
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

void borrarFigura(COORD coord) {
    auto it = find_if(figuras.begin(), figuras.end(), [coord](const Figura& figura) {
        return figura.coord.X == coord.X && figura.coord.Y == coord.Y;
    });

    if (it != figuras.end()) {
        cout << "Lo encontre!";
        figuras.erase(it);
        Sleep(1000);
    } else {
        cout << "No lo encontre!";
        Sleep(1000);
    }
}

int main() {
    bool inMenu = false;
    gotoxy(posicionX, posicionY, PUNTERO, 15);
    while (true) {
        system("cls");
        menu();
        cargar();
        gotoxy(posicionX, posicionY, PUNTERO, 15);

        if (inMenu) {
            if (opcionSeleccionada == 1) {
                system("cls");
                cout << "Ingrese la base del triangulo: ";
                int baseTriangulo;
                cin >> baseTriangulo;
                Figura nuevoTriangulo;
                nuevoTriangulo.idFigura = 1;
                nuevoTriangulo.valor1 = baseTriangulo;
                nuevoTriangulo.coord.X = posicionX;
                nuevoTriangulo.coord.Y = posicionY;
                figuras.push_back(nuevoTriangulo);
                inMenu = false;
            }
            if (opcionSeleccionada == 2) {
                system("cls");
                cout << "Ingrese el lado del cuadrado: ";
                int ladoCuadrado;
                cin >> ladoCuadrado;
                Figura nuevoCuadrado;
                nuevoCuadrado.idFigura = 2;
                nuevoCuadrado.valor1 = ladoCuadrado;
                nuevoCuadrado.coord.X = posicionX;
                nuevoCuadrado.coord.Y = posicionY;

                figuras.push_back(nuevoCuadrado);
                inMenu = false;
            }
            if (opcionSeleccionada == 3) {
                system("cls");
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
                figuras.push_back(nuevoRectangulo);
                inMenu = false;
            }
            if (opcionSeleccionada == 4) {
                system("cls");
                cout << "Ingrese el radio del circulo: ";
                int radioCirculo;
                cin >> radioCirculo;
                Figura nuevoCirculo;
                nuevoCirculo.idFigura = 4;
                nuevoCirculo.valor1 = radioCirculo;
                nuevoCirculo.coord.X = posicionX;
                nuevoCirculo.coord.Y = posicionY;
                figuras.push_back(nuevoCirculo);
                inMenu = false;
            }
            if (opcionSeleccionada == 5) {
                inMenu = false;
            }
            if (opcionSeleccionada == 6) {
                inMenu = false;
            }
            if (opcionSeleccionada == 7) {
                inMenu = false;
            }
            if (opcionSeleccionada == 8) {
                inMenu = false;
            }
            if (opcionSeleccionada == 9) {
                inMenu = false;
            }
            if (opcionSeleccionada == 10) {
                inMenu = false;
            }
            if (opcionSeleccionada == 12) {
                inMenu = false;
            }
            if (opcionSeleccionada == 13) {
                inMenu = false;
            }
        }
        else {
            if (GetKeyState(VK_F1) & 0x8000) {
                //Triángulo
                opcionSeleccionada = 1;
                inMenu = true;
            }
            if (GetKeyState(VK_F2) & 0x8000) {
                //Cuadrado
                opcionSeleccionada = 2;
                inMenu = true;
            }
            if (GetKeyState(VK_F3) & 0x8000) {
                //Rectángulo
                opcionSeleccionada = 3;
                inMenu = true;
            }
            if (GetKeyState(VK_F4) & 0x8000) {
                //Circulo
                opcionSeleccionada = 4;
                inMenu = true;
            }
            if (GetKeyState(VK_F5) & 0x8000) {
                //Linea
                opcionSeleccionada = 5;
                inMenu = true;
            }
            if (GetKeyState(VK_F6) & 0x8000) {
                //Rombo
                opcionSeleccionada = 6;
                inMenu = true;
            }
            if (GetKeyState(VK_F7) & 0x8000) {
                //Hexagono
                opcionSeleccionada = 7;
                inMenu = true;
            }
            if (GetKeyState(VK_F8) & 0x8000) {
                // Elegir Puntero
                opcionSeleccionada = 8;
                inMenu = true;
            }
            if (GetKeyState(VK_F9) & 0x8000) {
                // Limpiar Pantalla
                opcionSeleccionada = 9;
                inMenu = true;
            }
            if (GetKeyState(VK_F10) & 0x8000) {
                // Color Puntero
                opcionSeleccionada = 10;
                inMenu = true;
            }
            if (GetKeyState(VK_F12) & 0x8000) {
                // Grabar Pantalla
                opcionSeleccionada = 12;
                inMenu = true;
            }
            if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x41) & 0x8000)) {
                // Cargar Archivo
                opcionSeleccionada = 13;
                inMenu = true;
            }
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
        }

        Sleep(100);
    }
    return 0;
}

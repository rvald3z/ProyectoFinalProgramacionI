#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int ancho_pantalla = 110;
int alto_pantalla = 30;
char PUNTERO = '+';
int COLOR = 15;
int posicionX = ancho_pantalla / 2;
int posicionY = alto_pantalla / 2;
int opcionSeleccionada = 1;

struct Figura {
    int idFigura;
    COORD coord;
    int valor1;
    int valor2;
    char puntero;
    int color;
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
    char puntero = trianguloNuevo.puntero;
    int color = trianguloNuevo.color;

    for (int i = 0; i < altura; ++i) {
        int x1 = (trianguloNuevo.coord.X - i + ancho_pantalla) % ancho_pantalla;
        int x2 = (trianguloNuevo.coord.X + i + ancho_pantalla) % ancho_pantalla;
        int y = (trianguloNuevo.coord.Y + i + alto_pantalla) % alto_pantalla;

        if(x1 == x2){
            gotoxy(x1, y, puntero, 12);
        } else {
            gotoxy(x1, y, puntero, color);
            gotoxy(x2, y, puntero, color);
        }
    }

    for (int j = trianguloNuevo.coord.X - altura + 1; j <= trianguloNuevo.coord.X + altura - 1; ++j) {
        int x = (j + ancho_pantalla) % ancho_pantalla;
        int y = (trianguloNuevo.coord.Y + altura + alto_pantalla - 1) % alto_pantalla;
        gotoxy(x, y, puntero, color);
    }
}
void dibujarCuadrado(Figura nuevoCuadrado) {
    COORD coord;
    int lado = nuevoCuadrado.valor1;
    char puntero = nuevoCuadrado.puntero;
    int color = nuevoCuadrado.color;

    for (int fila = 0; fila < lado; ++fila) {
        for (int columna = 0; columna < lado; ++columna) {
            if (fila == 0 && columna == 0) {
                coord.X = (nuevoCuadrado.coord.X + columna + ancho_pantalla) % ancho_pantalla;
                coord.Y = (nuevoCuadrado.coord.Y + fila + alto_pantalla) % alto_pantalla;
                gotoxy(coord.X, coord.Y, puntero, 12);
            } else if (fila == 0 || fila == lado - 1 || columna == 0 || columna == lado - 1) {
                coord.X = (nuevoCuadrado.coord.X + columna + ancho_pantalla) % ancho_pantalla;
                coord.Y = (nuevoCuadrado.coord.Y + fila + alto_pantalla) % alto_pantalla;
                gotoxy(coord.X, coord.Y, puntero, color);
            }
        }
    }
}
void dibujarRectangulo(Figura nuevoRectangulo) {
    COORD coord;
    int base = nuevoRectangulo.valor1;
    int altura = nuevoRectangulo.valor2;
    char puntero = nuevoRectangulo.puntero;
    int color = nuevoRectangulo.color;

    for (int fila = 0; fila < altura; ++fila) {
        for (int columna = 0; columna < base; ++columna) {
            if (fila == 0 && columna == 0) {
                coord.X = (nuevoRectangulo.coord.X + columna + ancho_pantalla) % ancho_pantalla;
                coord.Y = (nuevoRectangulo.coord.Y + fila + alto_pantalla) % alto_pantalla;
                gotoxy(coord.X, coord.Y, puntero, 12);
            } else if (fila == 0 || fila == altura - 1 || columna == 0 || columna == base - 1) {
                coord.X = (nuevoRectangulo.coord.X + columna + ancho_pantalla) % ancho_pantalla;
                coord.Y = (nuevoRectangulo.coord.Y + fila + alto_pantalla) % alto_pantalla;
                gotoxy(coord.X, coord.Y,puntero, color);
            }
        }
    }
}
void dibujarCirculo(Figura nuevoCirculo) {
    COORD coord;
    COORD coordPunto;
    int radio = nuevoCirculo.valor1;
    char puntero = nuevoCirculo.puntero;
    bool flag = false;
    int color = nuevoCirculo.color;

    for (int i = -radio; i <= radio; ++i) {
        for (int j = -radio; j <= radio; ++j) {
            if (i * i + j * j <= radio * radio + radio/2 && i * i + j * j >= radio * radio - radio/2) {

                if(!flag){
                    coordPunto.X = nuevoCirculo.coord.X;
                    coordPunto.Y = nuevoCirculo.coord.Y;
                    gotoxy(coordPunto.X, coordPunto.Y, puntero, 12);
                    flag = true;
                }

                coord.X = (nuevoCirculo.coord.X + j + ancho_pantalla) % ancho_pantalla;
                coord.Y = (nuevoCirculo.coord.Y + i + alto_pantalla) % alto_pantalla;
                gotoxy(coord.X, coord.Y, puntero, color);
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
                nuevoTriangulo.puntero = PUNTERO;
                nuevoTriangulo.color = COLOR;
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
                nuevoCuadrado.puntero = PUNTERO;
                nuevoCuadrado.color = COLOR;
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
                nuevoRectangulo.puntero = PUNTERO;
                nuevoRectangulo.color = COLOR;
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
                nuevoCirculo.puntero = PUNTERO;
                nuevoCirculo.color = COLOR;
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
                system("cls");
                cout << "Quieres cambiar el puntero para dibujar? *(si o no)" << endl;
                string respuesta;
                cin >> respuesta;
                if (respuesta == "si" ) {
                    char nuevoPuntero;
                    cout << "Digita el caracter que quieres que sea tu puntero?" << endl;
                    cin >> nuevoPuntero;
                    PUNTERO = nuevoPuntero;
                    cout << "Tu puntero ha sido actualizado!" << endl;
                    cin.get();
                    inMenu = false;
                } else {
                    inMenu = false;
                }
            }
            if (opcionSeleccionada == 9) {
                inMenu = false;
            }
            if (opcionSeleccionada == 10) {
                system("cls");
                int color;
                cout << "Elige el color para el puntero:" << endl;
                cout << "1. Rojo" << endl;
                cout << "2. Azul" << endl;
                cout << "3. Verde" << endl;
                cout << "4. Amarillo" << endl;
                cout << "5. Cian" << endl;
                cout << "6. Magenta" << endl;
                cout << "7. Blanco" << endl;
                cout << "8. Negro" << endl;
                cin >> color;
                switch(color){
                    case 1:
                        COLOR = 12;
                        break;
                    case 2:
                        COLOR = 9;
                        break;
                    case 3:
                        COLOR = 10;
                        break;
                    case 4:
                        COLOR = 14;
                        break;
                    case 5:
                        COLOR = 11;
                        break;
                    case 6:
                        COLOR = 13;
                        break;
                    case 7:
                        COLOR = 15;
                        break;
                    case 8:
                        COLOR = 0;
                        break;
                    default:
                        cout << "Opción no válida. Se mantendrá el color predeterminado." << endl;
                        break;
                }

    cout << "Color del puntero actualizado." << endl;
    _getch();
    inMenu = false;
}
            if (opcionSeleccionada == 12) {
                system("cls");
                string nombreArchivo;
                string rutaArchivo;
                string fullPath;
                cout << "Escribir el nombre del archivo como quieres guardarlo (incluyendo la extensión .txt)" << endl;
                cin >> nombreArchivo;
                cout << "Escribir la ruta donde quieres guardar el archivo '" << nombreArchivo << "'" << "(no hace falta escribir '/' al final de la ruta)" << endl;
                cin >> rutaArchivo;
                fullPath = rutaArchivo + "/" + nombreArchivo;

                ofstream archivo(fullPath);
                if (archivo.is_open()) {
                    for (const Figura& figura : figuras) {
                        archivo << figura.idFigura << ";" << figura.valor1 << ";" << figura.valor2 << ";" << figura.coord.X << ";" << figura.coord.Y << ";" << figura.puntero << ";" << figura.color << "\n"; // Utiliza "\n" para terminar cada línea
                    }
                    archivo.close();
                    cout << "Figuras guardadas correctamente en el archivo '" << fullPath << "'." << endl;
                    Sleep(3000);
                    inMenu = false;
                } else {
                    cout << "Error al abrir el archivo para escritura." << endl;
                    Sleep(3000);
                    inMenu = false;
                }
            }
            if (opcionSeleccionada == 13) {
                system("cls");
                string ruta;
                cout<<"Escribe la ruta del archivo que quieres cargar: "<<endl;
                cin >> ruta;
                ifstream archivoLectura(ruta);
                if (archivoLectura.fail()) {
                    system("cls");
                    cout << "El archivo " << "'"<< ruta << "'" << " no fue encontrado o no existe, favor revisar!" << endl;
                    Sleep(3000);
                    inMenu = false;
                } else {
                    figuras.clear();
                    string registro;
                    while (getline(archivoLectura, registro)) {
                        stringstream token(registro);
                        string campo;
                        getline(token, campo, ';');
                        int idFigura = stoi(campo);

                        getline(token, campo, ';');
                        int valor1 = stoi(campo);

                        getline(token, campo, ';');
                        int valor2 = stoi(campo);

                        getline(token, campo, ';');
                        int coordX = stoi(campo);

                        getline(token, campo, ';');
                        int coordY = stoi(campo);

                        getline(token, campo, ';');
                        char puntero = campo[0];

                        getline(token, campo);
                        int color = stoi(campo);

                        Figura nuevaFigura;
                        nuevaFigura.idFigura = idFigura;
                        nuevaFigura.valor1 = valor1;
                        nuevaFigura.valor2 = valor2;
                        nuevaFigura.coord.X = coordX;
                        nuevaFigura.coord.Y = coordY;
                        nuevaFigura.puntero = puntero;
                        nuevaFigura.color = color;
                        figuras.push_back(nuevaFigura);
                    }
                    archivoLectura.close();
                    system("cls");
                    cout << "Figuras cargadas correctamente desde el archivo: " << ruta << endl;
                    Sleep(3000);
                    inMenu = false;

                }
            }
        } else {
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
            if (GetKeyState(VK_SHIFT) & 0x8000){
                //Borrar figura
                COORD coord;
                coord.X = posicionX;
                coord.Y = posicionY;
                borrarFigura(coord);
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

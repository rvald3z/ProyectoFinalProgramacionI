#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int ancho_pantalla = 100;
int alto_pantalla = 100;
const char PUNTERO = '+';

void gotoxy(int x, int y, char c) {
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    cout << c << "(" << x << ", " << y << ")";
}

void menu() {
    system("cls");
    cout << "Seleccione la figura que desea dibujar:\n";
    cout << "1. Triangulo\n";
    cout << "2. Cuadrado\n";
    cout << "3. Rectangulo\n";
    cout << "4. Circulo\n";
    cout << "Presione Esc para volver a la pantall de dibujo!";
}

int main() {
    int playerX = ancho_pantalla / 2;
    int playerY = alto_pantalla / 2;

    bool inMenu = false;

    while (true) {
        system("cls");
        gotoxy(playerX, playerY, PUNTERO);

        if (inMenu) {
            menu();
            char menuKey;
            do {
                menuKey = _getch();
            } while (menuKey != '1' && menuKey != '2' && menuKey != '3' && menuKey != '4' && menuKey != VK_ESCAPE);

            if(menuKey == '1'){
                cout<<"Triangulo";
                inMenu = false;
            }
            if(menuKey == '2'){
                cout<<"Cuadrado";
                inMenu = false;
            }
            if(menuKey == '3'){
                cout<<"Rectangulo";
                inMenu = false;
            }
            if(menuKey == '4'){
                cout<<"Circulo";
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
                        //Caso Extremo
                        // (0,35)
                        // (0 - 1 + 70 ) % 70
                        // 69 % 70
                        // entonces el resto de 69 % 70 es 69

                        //Caso Normal
                        // (2,35)
                        // (2 - 1 + 70) % 70
                        // 71 % 70
                        // Entonces el resto de 71 % 70 es 1

                        playerX = (playerX - 1 + ancho_pantalla) % ancho_pantalla;
                        break;
                    case 'd':
                        //Caso Extremo
                        // (69,35)
                        // (69 + 1) % 70
                        // 70 % 70
                        // entonces el resto de 70 % 70 es 0

                        //Caso Normal
                        // (2,70)
                        // (2 - 1) % 70
                        // 71 % 70
                        // Entonces el resto de 71 % 70 es 1

                        playerX = (playerX + 1) % ancho_pantalla;
                        break;

                    case 'w':
                        //Caso Extremo
                        // (35,0)
                        // (0 - 1 + 70 ) % 70
                        // 69 % 70
                        // entonces el resto de 69 % 70 es 69

                        //Caso Normal
                        // (2,35)
                        // (2 - 1 + 70) % 70
                        // 71 % 70
                        // Entonces el resto de 71 % 70 es 1

                        playerY = (playerY - 1 + alto_pantalla) % alto_pantalla;
                        break;
                    case 's':

                        //Caso Extremo
                        // (35,69)
                        // (69 + 1) % 70
                        // 70 % 70
                        // entonces el resto de 70 % 70 es 0

                        //Caso Normal
                        // (2,70)
                        // (2 - 1) % 70
                        // 71 % 70
                        // Entonces el resto de 71 % 70 es 1

                        playerY = (playerY + 1) % alto_pantalla;
                        break;
                    case 'q':
                        return 0;
                }
            }
        }

        Sleep(100);
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <map>
#include "jugador.h"
#include "dealer.h"
#include "funciones.h"
#include "juego.h"

using namespace std;

// g++ main.cpp dealer.cpp funciones.cpp jugador.cpp juego.cpp -o main.exe 


int main(){
    configurar_terminal();  
    
    set_color(CIAN);
    cout << R"(
 _______   __                      __                                     __       
|       \ |  \                    |  \                                   |  \      
| $$$$$$$\| $$  ______    _______ | $$   __       __   ______    _______ | $$   __ 
| $$__/ $$| $$ |      \  /       \| $$  /  \     |  \ |      \  /       \| $$  /  \
| $$    $$| $$  \$$$$$$\|  $$$$$$$| $$_/  $$      \$$  \$$$$$$\|  $$$$$$$| $$_/  $$
| $$$$$$$\| $$ /      $$| $$      | $$   $$      |  \ /      $$| $$      | $$   $$ 
| $$__/ $$| $$|  $$$$$$$| $$_____ | $$$$$$\      | $$|  $$$$$$$| $$_____ | $$$$$$\ 
| $$    $$| $$ \$$    $$ \$$     \| $$  \$$\     | $$ \$$    $$ \$$     \| $$  \$$\
 \$$$$$$$  \$$  \$$$$$$$  \$$$$$$$ \$$   \$$__   | $$  \$$$$$$$  \$$$$$$$ \$$   \$$
                                           |  \__/ $$                              
                                            \$$    $$                              
                                             \$$$$$$                              
    )" << RESET << endl;

    string opcion;

    do {
        set_color(NEGRITA);
        cout << "\n=== MENU PRINCIPAL ===" << RESET << endl;

        cout << "1. " << VERDE << "Jugar" << RESET << endl;
        cout << "2. " << ROJO << "Salir" << RESET << endl;
        cout << "Elige: ";
        cin >> opcion;

        if (opcion == "1") {
            juego nuevo_juego;
            animacion_cargando("Empezando nuevo juego");
            nuevo_juego.empezar_juego();
            nuevo_juego.guardar_juego();

            cout << "\nPresiona Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        else if (opcion == "2") {
            cout << "Saliendo del programa." << endl;
        }
        else {
            cout << ROJO << "Opción inválida." << RESET << endl;
        }

    } while (opcion != "2");

    return 0;
}
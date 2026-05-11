#include <iostream>
#include <vector>
#include <map>

#include "jugador.h"
#include "dealer.h"
#include "funciones.h"
#include "juego.h"

// g++ main.cpp dealer.cpp funciones.cpp jugador.cpp juego.cpp -o main.exe 

using namespace std; 

int main(){


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
    )" << endl;


    int opcion;

    do {
        cout << "\n=== MENU PRINCIPAL ===" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Salir" << endl;
        cout << "Elige: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:{
                juego nuevo_juego;
                animacion_cargando("Empezando nuevo juego");
                nuevo_juego.empezar_juego();
                nuevo_juego.guardar_juego();
                //cout << "El juego ha terminado.." <<endl;
                break;
            }
            case 2:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción inválida." << endl;
        }
    } while (opcion != 2);
    
    return 0;
}
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

    
    cout << "Turno del dealer..." << endl;
    animacion_cargando("El dealer está pensando");
    

    return 0;
}
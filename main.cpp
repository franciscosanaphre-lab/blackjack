#include <iostream>
#include <vector>
#include <map>

#include "jugador.h"
#include "dealer.h"
#include "funciones.h"

// g++ main.cpp dealer.cpp funciones.cpp jugador.cpp -o main.exe 

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

    jugador jugador_principal;
    jugador_principal.agregar_carta("A");

    vector<string> test = {
        "A","J","2"
    }; 

    jugador_principal.ver_cartas();

    dealer jugador_dealer;
    jugador_dealer.ver_cartas();

    return 0;
}
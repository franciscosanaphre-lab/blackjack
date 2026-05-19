#include "dealer.h"
#include "funciones.h"
#include <iostream>

using namespace std;

void dealer::ver_cartas(bool mostrar_oculta){
    if (baraja.empty()) return;
    
    mostrar_carta(baraja[0]);  // primera carta siempre visible
    
    for (size_t i = 1; i < baraja.size(); i++) {
        if (!mostrar_oculta && i == 1) {
            // segunda carta oculta
            set_color(AMARILLO);
            cout << "[???] ";
            set_color(RESET);
        } else {
            mostrar_carta(baraja[i]);
        }
    }
    cout << endl;
}
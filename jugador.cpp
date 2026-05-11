#include "jugador.h"
#include <iostream>

using namespace std;

void jugador::agregar_carta(string carta){
    baraja.push_back(carta);
};

void jugador::limpiar_cartas(){
    baraja.clear();
};

vector<string> jugador::obtener_baraja(){
    return baraja;
}

void jugador::ver_cartas(){
    for (int i=0; i<baraja.size(); i++){
        std::cout << baraja[i]<< " ";
    }
    std::cout<<std::endl;
}
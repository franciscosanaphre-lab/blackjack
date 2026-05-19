#include "jugador.h"
#include "funciones.h"
#include <iostream>
#include <sstream>

using namespace std;

void jugador::agregar_carta(string carta){
    baraja.push_back(carta);
}

void jugador::limpiar_cartas(){
    baraja.clear();
}

vector<string> jugador::obtener_baraja(){
    return baraja;
}

vector<string> jugador::obtener_baraja_sin_formato(){
    vector<string> baraja_sin_formato;
    for (size_t i = 0; i < baraja.size(); i++){
        string pica, valor;
        stringstream ss(baraja[i]);
        ss >> pica >> valor;
        baraja_sin_formato.push_back(valor);
    }
    return baraja_sin_formato;
}

void jugador::ver_cartas(){
    for (const auto& carta : baraja) {
        mostrar_carta(carta);
    }
    cout << endl;
}
#include "funciones.h"
#include <algorithm>
#include <map>
using namespace std;

#include <thread>
#include <chrono>
#include <sstream>
#include <string>

const map<string, int> valoresCartas = {
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
    {"10", 10},
    {"J", 10},
    {"Q", 10},
    {"K", 10}
};


void limpiar_pantalla() {
     cout << "\033[2J\033[3J\033[H" << flush;
}

void animacion_cargando(string mensaje, int vueltas, int velocidad_ms) {
    char frames[] = {'|', '/', '-', '\\'};

    for (int i = 0; i < vueltas; i++) {
        cout << "\r" << mensaje << " " << frames[i % 4] << flush;
        this_thread::sleep_for(chrono::milliseconds(velocidad_ms));
    }

    cout << "\r\033[2K" << flush; // limpia la línea
}

int calcular_valor_baraja(vector<string> baraja){

    int valor_actual = 0;
    int aces = 0;

    for (int i=0; i<baraja.size();i++){

        if (baraja[i] == "A") {
            aces += 1;
            //cout << "got an ace" << endl;
            continue;
        }

        valor_actual += valoresCartas.at(baraja[i]);
        //cout << "VALOR: " << valoresCartas.at(baraja[i]) << endl;

    }
     // procesamos aces:

    vector<int> manos_perdidas;
    vector<int> manos_no_perdidas;

    for (int i=0; i<=aces; i++){
        int valor_prueba = valor_actual + i*11 + aces-i;
        //cout << "VALOR PRUEBA: "<< i << " " << valor_prueba << endl;
        
        if (valor_prueba <= 21){
            manos_no_perdidas.push_back(valor_prueba);
            //cout << "Mano no perdida: " << valor_prueba << endl;
        } else {
            manos_perdidas.push_back(valor_prueba);
            //cout << "Mano perdida: " << valor_prueba << endl;
        }
    }

    if (aces>0){
         if (!manos_no_perdidas.empty()){
            valor_actual = *max_element(manos_no_perdidas.begin(), manos_no_perdidas.end());
        } else {
            valor_actual = *min_element(manos_perdidas.begin(), manos_perdidas.end());
        }
    }
   

    return valor_actual;
}

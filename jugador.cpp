#include "jugador.h"
#include <iostream>
#include <sstream>
#include <string>

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

vector<string> jugador::obtener_baraja_sin_formato(){
    vector<string> baraja_sin_formato;

    //cout << "Size: "<<baraja.size()<<endl;
    for (int i=0; i<baraja.size(); i++){

        //cout <<"Index:"<< i<<endl;
        string pica, valor;

        stringstream ss(baraja[i]);

        ss >> pica >> valor;

        //cout << "[=]Pica:" << "'"<<pica<<"'" << endl;
        //cout << "[+]Valor: " <<"'"<<valor<<"'"<<endl;

        baraja_sin_formato.push_back(valor);
        
    }

    //cout << "finished!" << endl;
    return baraja_sin_formato;
}



void jugador::ver_cartas(){
    for (int i=0; i<baraja.size(); i++){
        std::cout << baraja[i]<< " ";
    }
    std::cout<<std::endl;
}
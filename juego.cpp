#include <iostream>
#include "juego.h"

#include <fstream>
#include <string>

#include <random>
#include <algorithm>

using namespace std;
string leer_archivo(string nombre_archivo) {
    ifstream archivoIn(nombre_archivo);

    string linea;
    getline(archivoIn, linea);

    return linea;
} 


void escribir_archivo(string nombre_archivo, string texto){
    ofstream archivoOut(nombre_archivo);

    if(!archivoOut){
        cerr << "Error: No fue posible abrir el archivo!!!" << std::endl;
        return;
    }

    archivoOut << texto << endl;
   
    archivoOut.close();
}

void juego::guardar_juego(){
    string nombre_archivo = "juegos/juego_"+to_string(id)+".txt";
    escribir_archivo(nombre_archivo,logs);
}


void juego::guardar_estado(){
    vector<string> mano_jugador = juego_jugador.obtener_baraja();
    vector<string> mano_dealer = dealer_juego.obtener_baraja();

    string mano_jugador_string = "";

    for (int i=0; i<mano_jugador.size(); i++){
        mano_jugador_string += mano_jugador[i]+" ";
    }

    string mano_dealer_string = "";

    for (int i=0; i<mano_dealer.size(); i++){
        mano_dealer_string += mano_dealer[i]+" ";
    }

    int valor_jugador = calcular_valor_baraja(juego_jugador.obtener_baraja());
    int valor_dealer = calcular_valor_baraja(dealer_juego.obtener_baraja());

    logs+="\n-----------------------";
    logs+="\nMano del jugador: "+mano_jugador_string;
    logs+="\nValor de su mano: " +to_string(valor_jugador);
    logs+="\nMano del dealer: "+mano_dealer_string;
    logs+="\nValor de su mano: "+to_string(valor_dealer);

}

void juego::mostrar_estado() {
    limpiar_pantalla();

    cout << "======================" << endl;
    cout << "      BLACKJACK       " << endl;
    cout << "======================" << endl;
    cout << endl;
    cout << "[+] Tu mano:" << endl;
    juego_jugador.ver_cartas();
    cout << "Valor: " << calcular_valor_baraja(juego_jugador.obtener_baraja()) << endl;

    cout << endl;
    cout << "Mano del dealer:" << endl;
    dealer_juego.ver_cartas();

    vector<string> dealer_baraja = dealer_juego.obtener_baraja();

    dealer_baraja.erase(dealer_baraja.begin());
    
    cout << "Valor del dealer es al menos: " << calcular_valor_baraja(dealer_baraja) << endl;

    cout << endl;
}

juego::juego(){
    int numero_juego = stoi(leer_archivo("no_juego.txt")) + 1;
    cout << "Numero de juego: "<< numero_juego << endl;
    escribir_archivo("no_juego.txt", to_string(numero_juego));
    id = numero_juego;
}

string juego::sacar_carta(){
    random_device rd;
    mt19937 gen(rd());

    shuffle(baraja.begin(), baraja.end(), gen);

    string carta1 = baraja.back();
    baraja.pop_back();

    return carta1;
}

void juego::empezar_juego(){

    baraja = baraja_default;
    animacion_cargando("Repartiendo 2 cartas a cada jugador");
    
    juego_jugador.agregar_carta(sacar_carta());
    juego_jugador.agregar_carta(sacar_carta());

    dealer_juego.agregar_carta(sacar_carta());
    dealer_juego.agregar_carta(sacar_carta());

    /*

    cout << "Cartas repartidas." << endl;
    cout << "Tu mano:" << endl;
    juego_jugador.ver_cartas();

    

    cout << "Valor de mano: " << valor_mano << endl;

    cout << "Mano del dealer:" << endl;
    dealer_juego.ver_cartas();

    */ 

    mostrar_estado();
    guardar_estado();

    int valor_mano = calcular_valor_baraja(juego_jugador.obtener_baraja());

    if (valor_mano == 21){
        cout << "Ganaste con 21 puntos" << endl;
        return;
    } else if (valor_mano>21){
        cout << "Perdiste, te sobraron: " << valor_mano-21 << " puntos." << endl;
        return;
    }

    while (true) {

        int opcion;
        bool plantado = false;

        cout << "Tu turno." << endl;
        cout << "Presione (1) para pedir carta." << endl;
        cout << "Presione (2) para plantarse" << endl;

        cin >> opcion;

        string nueva_carta;

        switch (opcion)
        {
        case 1:
            
            animacion_cargando("Pidiendo carta nueva");
            nueva_carta = sacar_carta();

            logs = logs+"\nEl jugador pidio carta nueva: "+ nueva_carta;
            
            juego_jugador.agregar_carta(nueva_carta);
            mostrar_estado();
            guardar_estado();
            cout << "Te dieron la carta: '"<< nueva_carta << "'" << endl;
            //cout << "Tu nueva mano: " << endl;
            //juego_jugador.ver_cartas();

            valor_mano = calcular_valor_baraja(juego_jugador.obtener_baraja());
            //cout << "Valor:" << valor_mano << endl;

            if (valor_mano == 21){
                cout << "Ganaste con 21 puntos" << endl;
                logs = logs+"\nEl jugador gano con 21 puntos";
                return;
            } else if (valor_mano>21){
                cout << "Perdiste, te sobraron: " << valor_mano-21 << " puntos." << endl;
                logs = logs+"\nEl jugador perdio, le sobraron: "+to_string(valor_mano-21)+" puntos.";
                return;
            }

            break;
        case 2:
            cout << "Te plantaste." << endl;
            logs = logs+"\nEl jugador se planto";
            plantado = true;
            break;
        default:
            cout << "Opcion invalida, unicas opciones (1) o (2).";
            break;
        }

        int valor_mano_dealer = calcular_valor_baraja(dealer_juego.obtener_baraja());
        int valor_mano_jugador = calcular_valor_baraja(juego_jugador.obtener_baraja());

        cout << "Turno del dealer:" << endl;
        logs = logs+"\nTurno del dealer.";

        // el dealer se planta
        if (valor_mano_dealer>=17){
            cout << "El dealer se a plantado." << endl;
            logs = logs+"\nEl dealer se planta.";
            if (plantado){
                if (valor_mano_jugador == valor_mano_dealer){
                    cout << "Hubo un empate!" << endl;
                    logs = logs+"\nHubo empate";
                } else if (valor_mano_jugador>valor_mano_dealer){
                    cout << "Ganaste por " << valor_mano_jugador-valor_mano_dealer << " puntos. " << endl;
                    logs = logs+"\nEl jugador gana por: "+to_string(valor_mano_jugador-valor_mano_dealer)+" puntos.";
                } else {
                    cout << "Perdiste, el dealer tenia: " << valor_mano_dealer << " puntos."<< endl;
                    logs = logs+"\nEl jugador perdio, el dealer tenia:"+to_string(valor_mano_dealer)+" puntos."; 
                }
                return;
            }
        } 
        // el dealer pide carta
        else {

            animacion_cargando("El dealer esta tomando una nueva carta",12,300);
            logs = logs+"\nEl dealer esta tomando una nueva carta";
            nueva_carta = sacar_carta();
            dealer_juego.agregar_carta(nueva_carta);

            /*

            cout << "Su mano: " << endl;
            dealer_juego.ver_cartas();

            */ 

            mostrar_estado();
            guardar_estado();
            cout << "El dealer obtuvo esta nueva carta: " << nueva_carta << endl;
            logs = logs+"\nEl dealer obtuvo: "+nueva_carta;

            valor_mano_dealer = calcular_valor_baraja(dealer_juego.obtener_baraja());
            logs = logs+"\nValor de la mano del dealer: "+to_string(valor_mano_dealer);

            if (valor_mano_dealer>21) {
                cout << "Has ganado!, el dealer se paso por " << valor_mano_dealer-21 << " puntos." << endl;
                logs = logs+"\nEl jugador ha ganado!, el dealer se paso por:"+to_string(valor_mano_dealer-21)+" puntos";
                return;
            }
            
        }
    }
}
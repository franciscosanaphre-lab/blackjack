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

void juego::mostrar_estado() {
    limpiar_pantalla();

    cout << "======================" << endl;
    cout << "      BLACKJACK       " << endl;
    cout << "======================" << endl;

    cout << endl;
    cout << "Tu mano:" << endl;
    juego_jugador.ver_cartas();
    cout << "Valor: " << calcular_valor_baraja(juego_jugador.obtener_baraja()) << endl;

    cout << endl;
    cout << "Mano del dealer:" << endl;
    dealer_juego.ver_cartas();
    string carta_oculta = dealer_juego.obtener_baraja()[0];
    
    cout << "Valor dealer es al menos:" << calcular_valor_baraja(dealer_juego.obtener_baraja()) - valoresCartas.at(carta_oculta) << endl;

    cout << endl;
}

juego::juego(){
    int numero_juego = stoi(leer_archivo("no_juego.txt")) + 1;
    cout << "Numero de juego: "<< numero_juego << endl;
    escribir_archivo("no_juego.txt", to_string(numero_juego));
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
    cout << "Repartiendo 2 cartas a cada jugador." << endl;
    
    juego_jugador.agregar_carta(sacar_carta());
    juego_jugador.agregar_carta(sacar_carta());

    dealer_juego.agregar_carta(sacar_carta());
    dealer_juego.agregar_carta(sacar_carta());

    cout << "Cartas repartidas." << endl;
    cout << "Tu mano:" << endl;
    juego_jugador.ver_cartas();

    int valor_mano = calcular_valor_baraja(juego_jugador.obtener_baraja());

    cout << "Valor de mano: " << valor_mano << endl;

    cout << "Mano del dealer:" << endl;
    dealer_juego.ver_cartas();

    if (valor_mano == 21){
        cout << "Ganaste con 21 puntos" << endl;
        return;
    } else if (valor_mano>21){
        cout << "Perdiste, te sobraron: " << valor_mano-21 << "puntos." << endl;
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

            nueva_carta = sacar_carta();
            cout << "Te dieron la carta: '"<< nueva_carta << "'" << endl;
            juego_jugador.agregar_carta(nueva_carta);
            cout << "Tu nueva mano: " << endl;
            juego_jugador.ver_cartas();

            valor_mano = calcular_valor_baraja(juego_jugador.obtener_baraja());
            cout << "Valor:" << valor_mano << endl;

            if (valor_mano == 21){
                cout << "Ganaste con 21 puntos" << endl;
                return;
            } else if (valor_mano>21){
                cout << "Perdiste, te sobraron: " << valor_mano-21 << "puntos." << endl;
                return;
            }

            break;
        case 2:
            cout << "Te plantaste." << endl;
            plantado = true;
            break;
        default:
            cout << "Opcion invalida, unicas opciones (1) o (2).";
            break;
        }

        int valor_mano_dealer = calcular_valor_baraja(dealer_juego.obtener_baraja());
        int valor_mano_jugador = calcular_valor_baraja(juego_jugador.obtener_baraja());

        cout << "Turno del dealer:" << endl;

        // el dealer se planta
        if (valor_mano_dealer>=17){
            cout << "El dealer se a plantado." << endl;
            if (plantado){
                if (valor_mano_jugador == valor_mano_dealer){
                    cout << "Hubo un empate!" << endl;
                } else if (valor_mano_jugador>valor_mano_dealer){
                    cout << "Ganaste por " << valor_mano_jugador-valor_mano_dealer << " puntos. " << endl;
                } else {
                    cout << "Perdiste, el dealer tenia: " << valor_mano_dealer << " puntos."<< endl;
                }
                return;
            }
        } 
        // el dealer pide carta
        else {

            nueva_carta = sacar_carta();
            cout << "El dealer toma una nueva carta: " << nueva_carta << endl;

            dealer_juego.agregar_carta(nueva_carta);

            cout << "Su mano: " << endl;
            dealer_juego.ver_cartas();

            valor_mano_dealer = calcular_valor_baraja(dealer_juego.obtener_baraja());

            if (valor_mano_dealer>21) {
                cout << "Has ganado!, el dealer se paso por " << valor_mano_dealer-21 << " puntos." << endl;
            }
            
        }
    }
}
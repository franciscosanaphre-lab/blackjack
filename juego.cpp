#include <iostream>
#include "juego.h"
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>

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
        cerr << "Error: No fue posible abrir el archivo!!!" << endl;
        return;
    }
    archivoOut << texto << endl;
    archivoOut.close();
}

void juego::guardar_juego(){
    string nombre_archivo = "juegos/juego_"+to_string(id)+".txt";
    escribir_archivo(nombre_archivo, logs);
}

void juego::guardar_estado(){
    vector<string> mano_jugador = juego_jugador.obtener_baraja();
    vector<string> mano_dealer = dealer_juego.obtener_baraja();

    string mano_jugador_string = "";
    for (size_t i=0; i<mano_jugador.size(); i++)
        mano_jugador_string += mano_jugador[i]+" ";

    string mano_dealer_string = "";
    for (size_t i=0; i<mano_dealer.size(); i++)
        mano_dealer_string += mano_dealer[i]+" ";

    int valor_jugador = calcular_valor_baraja(juego_jugador.obtener_baraja_sin_formato());
    int valor_dealer = calcular_valor_baraja(dealer_juego.obtener_baraja_sin_formato());

    logs+="\n-----------------------";
    logs+="\nMano del jugador: "+mano_jugador_string;
    logs+="\nValor de su mano: " +to_string(valor_jugador);
    logs+="\nMano del dealer: "+mano_dealer_string;
    logs+="\nValor de su mano: "+to_string(valor_dealer);
}
void juego::mostrar_estado() {
    limpiar_pantalla();

    set_color(CIAN);
    cout << NEGRITA;
    cout << "======================================" << endl;
    cout << "              BLACKJACK                " << endl;
    cout << "======================================" << endl;
    set_color(RESET);
    cout << endl;

    // Mano del jugador
    set_color(AZUL);
    cout << "[+] TU MANO:" << endl;
    set_color(RESET);

    juego_jugador.ver_cartas();

    int valor_jug = calcular_valor_baraja(juego_jugador.obtener_baraja_sin_formato());

    if (valor_jug > 21)
        set_color(ROJO);
    else
        set_color(VERDE);

    cout << "Valor: " << valor_jug << endl;
    set_color(RESET);
    cout << endl;

    // Mano del dealer
    set_color(AMARILLO);
    cout << "[?] MANO DEL DEALER:" << endl;
    set_color(RESET);

    dealer_juego.ver_cartas(false);   // oculta la segunda carta

    vector<string> dealer_baraja_parcial = dealer_juego.obtener_baraja_sin_formato();
    vector<string> cartas_visibles_dealer;

    for (size_t i = 0; i < dealer_baraja_parcial.size(); i++) {
        if (i == 1) {
            continue; // saltamos la segunda carta porque está oculta
        }

        cartas_visibles_dealer.push_back(dealer_baraja_parcial[i]);
    }

    if (!cartas_visibles_dealer.empty()) {
        int valor_minimo = calcular_valor_baraja(cartas_visibles_dealer);

        cout << "Valor del dealer es al menos: ";

        if (valor_minimo > 21)
            set_color(ROJO);
        else
            set_color(VERDE);

        cout << valor_minimo << endl;
        set_color(RESET);
    }

    cout << endl;
}
juego::juego(){
    int numero_juego = stoi(leer_archivo("no_juego.txt")) + 1;
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

    juego_jugador.limpiar_cartas();
    dealer_juego.limpiar_cartas();

    juego_jugador.agregar_carta(sacar_carta());
    juego_jugador.agregar_carta(sacar_carta());
    dealer_juego.agregar_carta(sacar_carta());
    dealer_juego.agregar_carta(sacar_carta());

    mostrar_estado();
    guardar_estado();

    int valor_mano = calcular_valor_baraja(juego_jugador.obtener_baraja_sin_formato());
    if (valor_mano == 21){
        set_color(VERDE); cout << NEGRITA << "¡BLACKJACK! Has ganado con 21 puntos." << RESET << endl;
        logs += "\nEl jugador gano con 21 puntos";
        return;
    } else if (valor_mano > 21){
        set_color(ROJO); cout << "Perdiste, te pasaste por " << (valor_mano-21) << " puntos." << RESET << endl;
        logs += "\nEl jugador perdio, le sobraron: "+to_string(valor_mano-21)+" puntos.";
        return;
    }

    // Turno del jugador
    bool plantado = false;
    while (!plantado) {
        int opcion;
        cout << NEGRITA << "Tu turno:" << RESET << endl;
        cout << "  (1) " << VERDE << "Pedir carta" << RESET << endl;
        cout << "  (2) " << AMARILLO << "Plantarse" << RESET << endl;
        cout << "Elige: ";
        cin >> opcion;

        if (opcion == 1) {
            animacion_cargando("Pidiendo carta nueva");
            string nueva_carta = sacar_carta();
            logs += "\nEl jugador pidio carta nueva: "+ nueva_carta;
            juego_jugador.agregar_carta(nueva_carta);
            mostrar_estado();
            guardar_estado();

            set_color(MAGENTA); cout << "Te dieron: "; mostrar_carta(nueva_carta); cout << RESET << endl;

            valor_mano = calcular_valor_baraja(juego_jugador.obtener_baraja_sin_formato());
            if (valor_mano == 21){
                set_color(VERDE); cout << NEGRITA << "¡Has alcanzado 21! Ganas automáticamente." << RESET << endl;
                logs += "\nEl jugador gano con 21 puntos";
                return;
            } else if (valor_mano > 21){
                set_color(ROJO); cout << "Te pasaste por " << (valor_mano-21) << " puntos. ¡Perdiste!" << RESET << endl;
                logs += "\nEl jugador perdio, le sobraron: "+to_string(valor_mano-21)+" puntos.";
                return;
            }
        } else if (opcion == 2) {
            cout << AMARILLO << "Te has plantado." << RESET << endl;
            logs += "\nEl jugador se planto";
            plantado = true;
        } else {
            cout << ROJO << "Opción inválida. Elige 1 o 2." << RESET << endl;
        }
    }

    // Turno del dealer
    cout << NEGRITA << "Turno del dealer:" << RESET << endl;
    logs += "\nTurno del dealer.";

    limpiar_pantalla();
    set_color(CIAN); cout << "=== REVELANDO CARTA OCULTA ===" << endl; set_color(RESET);
    set_color(AMARILLO); cout << "Mano completa del dealer:" << endl; set_color(RESET);
    dealer_juego.ver_cartas(true);
    int valor_dealer = calcular_valor_baraja(dealer_juego.obtener_baraja_sin_formato());
    if (valor_dealer <= 21) set_color(VERDE); else set_color(ROJO);
    cout << "Valor actual: " << valor_dealer << RESET << endl;
    this_thread::sleep_for(chrono::seconds(1));

    while (valor_dealer < 17) {
        animacion_cargando("El dealer pide una carta", 12, 200);
        string nueva_carta = sacar_carta();
        logs += "\nEl dealer toma nueva carta: "+nueva_carta;
        dealer_juego.agregar_carta(nueva_carta);
        mostrar_estado();
        guardar_estado();
        cout << "El dealer recibe: "; mostrar_carta(nueva_carta); cout << endl;
        valor_dealer = calcular_valor_baraja(dealer_juego.obtener_baraja_sin_formato());
        if (valor_dealer > 21) break;
        this_thread::sleep_for(chrono::seconds(1));
    }

    int valor_jugador = calcular_valor_baraja(juego_jugador.obtener_baraja_sin_formato());
    cout << "\n" << NEGRITA << "=== RESULTADO FINAL ===" << RESET << endl;
    cout << "Tu puntuación: " << (valor_jugador <= 21 ? VERDE : ROJO) << valor_jugador << RESET << endl;
    cout << "Puntuación del dealer: " << (valor_dealer <= 21 ? VERDE : ROJO) << valor_dealer << RESET << endl;

    if (valor_dealer > 21) {
        set_color(VERDE); cout << NEGRITA << "¡El dealer se pasó! ¡Has ganado!" << RESET << endl;
        logs += "\nEl jugador ha ganado!, el dealer se paso por:"+to_string(valor_dealer-21)+" puntos";
    } else if (valor_jugador > valor_dealer) {
        set_color(VERDE); cout << NEGRITA << "¡Felicidades! Has ganado." << RESET << endl;
        logs += "\nEl jugador gana por: "+to_string(valor_jugador-valor_dealer)+" puntos.";
    } else if (valor_jugador == valor_dealer) {
        set_color(AMARILLO); cout << NEGRITA << "Empate." << RESET << endl;
        logs += "\nHubo empate";
    } else {
        set_color(ROJO); cout << NEGRITA << "El dealer gana. ¡Suerte la próxima!" << RESET << endl;
        logs += "\nEl jugador perdio, el dealer tenia:"+to_string(valor_dealer)+" puntos.";
    }
}
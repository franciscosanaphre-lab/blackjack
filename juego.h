#ifndef __JUEGO__
#define __JUEGO__

#include <iostream>
#include <string>
#include "jugador.h"
#include "dealer.h"
#include "funciones.h"

class juego{
    private:
        dealer dealer_juego;
        jugador juego_jugador;
        std::string logs;
        std::vector<std::string> baraja_default = {
            "2", "2", "2", "2",
            "3", "3", "3", "3",
            "4", "4", "4", "4",
            "5", "5", "5", "5",
            "6", "6", "6", "6",
            "7", "7", "7", "7",
            "8", "8", "8", "8",
            "9", "9", "9", "9",
            "10", "10", "10", "10",
            "J", "J", "J", "J",
            "Q", "Q", "Q", "Q",
            "K", "K", "K", "K",
            "A", "A", "A", "A"
        };

        std::vector<std::string> baraja;
    public:
        juego();

        std::string sacar_carta();
        void empezar_juego();
        void mostrar_estado();

};

#endif
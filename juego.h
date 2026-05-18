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
            "A 2", "B 2", "C 2", "D 2",
            "A 3", "B 3", "C 3", "D 3",
            "A 4", "B 4", "C 4", "D 4",
            "A 5", "B 5", "C 5", "D 5",
            "A 6", "B 6", "C 6", "D 6",
            "A 7", "B 7", "C 7", "D 7",
            "A 8", "B 8", "C 8", "D 8",
            "A 9", "B 9", "C 9", "D 9",
            "A 10", "B 10", "C 10", "D 10",
            "A J", "B J", "C J", "D J",
            "A Q", "B Q", "C Q", "D Q",
            "A K", "B K", "C K", "D K",
            "A A", "B A", "C A", "D A"
        };

        int id;

        std::vector<std::string> baraja;
    public:
        juego();

        std::string sacar_carta();
        void empezar_juego();
        void mostrar_estado();
        void guardar_estado();
        void guardar_juego();

};

#endif
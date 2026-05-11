#ifndef __JUGADOR__
#define __JUGADOR__

#include <iostream>
#include <vector>
#include <string>

class jugador{
    protected:
        std::vector<std::string> baraja;
    public:
        jugador(){};
        ~jugador(){};

        void agregar_carta(std::string carta);
        void limpiar_cartas();
        virtual void ver_cartas();
        std::vector<std::string> obtener_baraja();
};

#endif
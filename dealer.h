#ifndef __DEALER__
#define __DEALER__

#include "jugador.h"

class dealer: public jugador{
    public:
        void ver_cartas(bool mostrar_oculta = false);
        // Sobrecarga para mantener compatibilidad con llamadas existentes sin parámetro
        void ver_cartas() override { ver_cartas(false); }
};

#endif
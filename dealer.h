#ifndef __DEALER__
#define __DEALER__

#include "jugador.h"


class dealer: public jugador{
    public:
        void ver_cartas() override;
};

#endif
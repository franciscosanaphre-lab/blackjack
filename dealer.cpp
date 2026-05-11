#include "dealer.h"
#include <iostream>

using namespace std;

void dealer::ver_cartas(){
    std::cout << "# ";
    for (int i=1; i<baraja.size(); i++){
        std::cout << baraja[i]<< " ";
    }
    std::cout<<std::endl;
}
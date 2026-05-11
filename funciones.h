#ifndef __FUNCIONES__
#define __FUNCIONES__

#include <iostream>
#include <string>
#include <vector>
#include <map>

extern const std::map<std::string, int> valoresCartas;
int calcular_valor_baraja(std::vector<std::string> baraja);
void animacion_cargando(std::string mensaje, int vueltas = 12, int velocidad_ms = 120);
void limpiar_pantalla();
#endif
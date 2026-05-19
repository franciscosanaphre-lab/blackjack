#ifndef __FUNCIONES__
#define __FUNCIONES__

#include <iostream>
#include <string>
#include <vector>
#include <map>

// Colores ANSI
#define RESET   "\033[0m"
#define NEGRO   "\033[30m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL    "\033[34m"
#define MAGENTA "\033[35m"
#define CIAN    "\033[36m"
#define BLANCO  "\033[37m"
#define NEGRITA "\033[1m"

extern const std::map<std::string, int> valoresCartas;

int calcular_valor_baraja(std::vector<std::string> baraja);
void animacion_cargando(std::string mensaje, int vueltas = 12, int velocidad_ms = 120);
void limpiar_pantalla();
void mostrar_carta(const std::string& carta);
void configurar_terminal();  // Nueva: configura UTF-8

inline void set_color(const std::string& color) {
    std::cout << color;
}

#endif
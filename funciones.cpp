#include "funciones.h"
#include <algorithm>
#include <map>
#include <thread>
#include <chrono>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const map<string, int> valoresCartas = {
    {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8},
    {"9", 9}, {"10", 10}, {"J", 10}, {"Q", 10}, {"K", 10}
};

void limpiar_pantalla() {
    cout << "\033[2J\033[3J\033[H" << flush;
}

void animacion_cargando(string mensaje, int vueltas, int velocidad_ms) {
    char frames[] = {'|', '/', '-', '\\'};
    for (int i = 0; i < vueltas; i++) {
        cout << "\r" << mensaje << " " << frames[i % 4] << flush;
        this_thread::sleep_for(chrono::milliseconds(velocidad_ms));
    }
    cout << "\r\033[2K" << flush;
}

int calcular_valor_baraja(vector<string> baraja) {
    int valor_actual = 0;
    int aces = 0;
    for (size_t i = 0; i < baraja.size(); i++) {
        if (baraja[i] == "A") {
            aces++;
            continue;
        }
        valor_actual += valoresCartas.at(baraja[i]);
    }
    vector<int> manos_perdidas, manos_no_perdidas;
    for (int i = 0; i <= aces; i++) {
        int valor_prueba = valor_actual + i*11 + (aces - i);
        if (valor_prueba <= 21)
            manos_no_perdidas.push_back(valor_prueba);
        else
            manos_perdidas.push_back(valor_prueba);
    }
    if (aces > 0) {
        if (!manos_no_perdidas.empty())
            valor_actual = *max_element(manos_no_perdidas.begin(), manos_no_perdidas.end());
        else
            valor_actual = *min_element(manos_perdidas.begin(), manos_perdidas.end());
    }
    return valor_actual;
}

// Devuelve el símbolo del palo como string (Unicode)
static string palo_a_simbolo(char p) {
    switch(p) {
        case 'A': return "♠";
        case 'B': return "♥";
        case 'C': return "♣";
        case 'D': return "♦";
        default: return "?";
    }
}

void mostrar_carta(const string& carta) {
    stringstream ss(carta);
    char palo_letra;
    string valor;

    if (!(ss >> palo_letra >> valor)) {
        cout << AMARILLO << NEGRITA << "[?]" << RESET << " ";
        return;
    }

    string simbolo = palo_a_simbolo(palo_letra);

    if (simbolo == "♥" || simbolo == "♦")
        cout << ROJO << NEGRITA;
    else
        cout << BLANCO << NEGRITA;

    cout << "[" << simbolo << valor << "]" << RESET << " ";
}

void configurar_terminal() {
#ifdef _WIN32
    // Habilitar salida UTF-8 en Windows
    SetConsoleOutputCP(CP_UTF8);
    // También habilitar modo VT100 para colores ANSI
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
    // En Linux/Mac ya es UTF-8 por defecto
}
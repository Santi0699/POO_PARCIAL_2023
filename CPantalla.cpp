#include "CPantalla.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

void CPantalla::ajustarColor(int numero) {
    for (auto &px : data) {
        int A = int((px >> 24) & 0xFF) + numero;
        A = std::clamp(A, 0, 255);
        px = (uint32_t(A) << 24) | (px & 0x00FFFFFFu); // sólo cambia AA
    }
}

void CPantalla::borrarVerde() {
    for (auto &px : data) {
        px &= 0xFFFF00FFu; // G = 0
    }
}

void CPantalla::reforzarRojo(double porcentaje) {
    const double factor = 1.0 + porcentaje; // ej: 0.35 -> 1.35
    for (auto &px : data) {
        uint8_t A = (px >> 24) & 0xFF;
        int R = int((px >> 16) & 0xFF);
        R = std::clamp(int(double(R) * factor), 0, 255);
        px = (uint32_t(A) << 24) | (uint32_t(R) << 16) | (px & 0x0000FFFFu);
    }
}

void CPantalla::guardarTxt(const std::string& ruta) const {
    std::ofstream out(ruta);
    if (!out) throw std::runtime_error("No se pudo abrir " + ruta);
    out << "Pantalla (" << filas << "x" << columnas << ")\n";
    out << *this << '\n'; // usa operator<< de CMatriz (hex 0xAARRGGBB)
}

#pragma once
#include <iostream>
#include <cstdint>

class CColor {
    uint32_t value; // Formato 0xAARRGGBB
public:
    explicit CColor(uint32_t v = 0) : value(v) {}

    // Accesores
    uint8_t a() const { return (value >> 24) & 0xFF; }
    uint8_t r() const { return (value >> 16) & 0xFF; }
    uint8_t g() const { return (value >> 8)  & 0xFF; }
    uint8_t b() const { return  value        & 0xFF; }

    // Mutadores
    void setA(uint8_t A) { value = (value & 0x00FFFFFFu) | (uint32_t(A) << 24); }
    void setR(uint8_t R) { value = (value & 0xFF00FFFFu) | (uint32_t(R) << 16); }
    void setG(uint8_t G) { value = (value & 0xFFFF00FFu) | (uint32_t(G) << 8 ); }
    void setB(uint8_t B) { value = (value & 0xFFFFFF00u) |  uint32_t(B); }

    uint32_t raw() const { return value; }
};

// Imprime en el formato requerido por el enunciado (sin encabezado)
inline std::ostream& operator<<(std::ostream& os, const CColor& c) {
    os << "componente azul: "  << int(c.b()) << '\n'
       << "componente verde: " << int(c.g()) << '\n'
       << "componente rojo: "  << int(c.r()) << '\n'
       << "componentealpha: "  << int(c.a());
    return os;
}

#include "CMatriz.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

void CMatriz::cargar(const std::string& archivoBin) {
    std::ifstream in(archivoBin, std::ios::binary);
    if (!in) throw std::runtime_error("No se pudo abrir " + archivoBin);

    // Cabecera: [uint32 filas][uint32 columnas]
    uint32_t f = 0, c = 0;
    if (!in.read(reinterpret_cast<char*>(&f), sizeof(uint32_t)))
        throw std::runtime_error("Lectura incompleta de filas");
    if (!in.read(reinterpret_cast<char*>(&c), sizeof(uint32_t)))
        throw std::runtime_error("Lectura incompleta de columnas");

    filas = f; columnas = c;
    data.resize(static_cast<size_t>(filas) * columnas);

    // Bloque de datos de una sola vez
    const std::streamsize bytes = static_cast<std::streamsize>(data.size() * sizeof(uint32_t));
    if (!in.read(reinterpret_cast<char*>(data.data()), bytes))
        throw std::runtime_error("Lectura incompleta de datos de la matriz");
}

CMatriz CMatriz::operator+(uint32_t escalar) const {
    // Suma escalar sobre R,G,B (no cambia A); saturación por canal
    CMatriz r(*this);
    for (auto &px : r.data) {
        uint8_t A = (px >> 24) & 0xFF;
        uint8_t R = std::min<uint32_t>(0xFFu, ((px >> 16) & 0xFFu) + escalar);
        uint8_t G = std::min<uint32_t>(0xFFu, ((px >> 8 ) & 0xFFu) + escalar);
        uint8_t B = std::min<uint32_t>(0xFFu, ( px        & 0xFFu) + escalar);
        px = (uint32_t(A) << 24) | (uint32_t(R) << 16) | (uint32_t(G) << 8) | uint32_t(B);
    }
    return r;
}

CMatriz& CMatriz::operator+=(const CMatriz& other) {
    if (filas != other.filas || columnas != other.columnas)
        throw std::runtime_error("Dimensiones incompatibles en operator+=");
    for (size_t i = 0; i < data.size(); ++i) {
        uint32_t a = data[i], b = other.data[i];
        uint8_t A = (a >> 24) & 0xFF; // mantenemos alpha de 'a' (podrías definir otra política)
        int R = int((a>>16)&0xFF) + int((b>>16)&0xFF);
        int G = int((a>>8 )&0xFF) + int((b>>8 )&0xFF);
        int B = int( a     &0xFF) + int( b     &0xFF);
        R = std::clamp(R, 0, 255);
        G = std::clamp(G, 0, 255);
        B = std::clamp(B, 0, 255);
        data[i] = (uint32_t(A) << 24) | (uint32_t(R) << 16) | (uint32_t(G) << 8) | uint32_t(B);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const CMatriz& m) {
    if (m.filas == 0 || m.columnas == 0) { os << "<vacia>"; return os; }
    // Imprime cada valor como 0xAARRGGBB (8 dígitos hex) separado por espacios
    std::ios::fmtflags f(os.flags());
    os << std::uppercase << std::hex;
    for (size_t i = 0; i < m.filas; ++i) {
        for (size_t j = 0; j < m.columnas; ++j) {
            uint32_t v = m.data[i * m.columnas + j];
            os << "0x" << std::setw(8) << std::setfill('0') << v;
            if (j + 1 < m.columnas) os << ' ';
        }
        if (i + 1 < m.filas) os << '\n';
    }
    os.flags(f);
    return os;
}

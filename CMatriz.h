#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

class CMatriz {
protected:
    size_t filas {0};
    size_t columnas {0};
    std::vector<uint32_t> data; // Cada elemento = 0xAARRGGBB

public:
    CMatriz() = default;
    CMatriz(size_t f, size_t c, uint32_t valor = 0) : filas(f), columnas(c), data(f*c, valor) {}
    CMatriz(const CMatriz&) = default;
    CMatriz& operator=(const CMatriz&) = default;
    virtual ~CMatriz() = default;

    // 1) Lectura binaria optimizada: cabecera + bloque de datos en 2 lecturas
    void cargar(const std::string& archivoBin);

    // Acceso
    size_t getFilas() const { return filas; }
    size_t getColumnas() const { return columnas; }
    uint32_t* getPtr() { return data.empty() ? nullptr : data.data(); }
    const uint32_t* getPtr() const { return data.empty() ? nullptr : data.data(); }

    // Aritmética
    CMatriz operator+(uint32_t escalar) const;  // suma escalar por canal (con saturación)
    CMatriz& operator+=(const CMatriz& other);  // suma elemento a elemento (con saturación)

    // Impresión en hexadecimal con prefijo 0x y 8 dígitos (AARRGGBB)
    friend std::ostream& operator<<(std::ostream& os, const CMatriz& m);
};

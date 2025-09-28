#pragma once
#include "CMatriz.h"
#include "CColor.h"
#include <string>

class CPantalla : public CMatriz {
public:
    CPantalla() = default;
    explicit CPantalla(const CMatriz& base) : CMatriz(base) {}

    // 2a) Suma 'numero' a la componente alpha (AA) de todos los píxeles (con saturación 0..255)
    void ajustarColor(int numero);

    // 2b) Pone G=0 en todos los píxeles
    void borrarVerde();

    // 2c) Aumenta R en 'porcentaje' (ej: 0.35 => +35%), con saturación a 255
    void reforzarRojo(double porcentaje);

    // 3) Persistencia a texto
    void guardarTxt(const std::string& ruta) const;
};

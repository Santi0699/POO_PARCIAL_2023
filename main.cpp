#include <iostream>
#include "CMatriz.h"
#include "CPantalla.h"
#include "CColor.h"

int main() {
  
        CMatriz original;
        original.cargar("colores.bin");
        std::cout << "Matriz original:" << std::endl << original << std::endl;

        CMatriz copia(original), suma;
        suma = original;
        suma += (copia + 5);
        std::cout << "Matriz suma:" << std::endl << suma << std::endl;

        CPantalla pantalla(original);
        std::cout << "Pantalla original:" << std::endl << pantalla << std::endl;

        pantalla.ajustarColor(3);
        std::cout << "Pantalla con ajuste de color:" << std::endl << pantalla << std::endl;

        pantalla.borrarVerde();
        std::cout << "Pantalla sin componente verde:" << std::endl << pantalla << std::endl;

        pantalla.reforzarRojo(0.35);
        std::cout << "Pantalla modificada (rojo reforzado):" << std::endl << pantalla << std::endl;

        pantalla.guardarTxt("pantalla.txt");

        CColor color(pantalla.getPtr()[pantalla.getFilas()*pantalla.getColumnas()-1]);
        std::cout << "El color del ultimo punto de la pantalla es: " << std::endl
                  << color << std::endl;

    return 0;
}

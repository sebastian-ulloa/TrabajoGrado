#include "ManejadorGestos.h"



ManejadorGestos::ManejadorGestos() {
}


ManejadorGestos::~ManejadorGestos() {
}

void ManejadorGestos::asignarValores ( float anterior, int actual, int completo ) {
    this->valorAnterior = anterior;
    this->gestoProgreso = actual;
    this->gestoCompleto = completo;
}

float ManejadorGestos::getValorAnterior() {
    return this->valorAnterior;
}

float ManejadorGestos::getGestoProgreso() {
    return this->gestoProgreso;
}

int ManejadorGestos::getGestoCompleto() {
    return this->gestoCompleto;
}

void ManejadorGestos::aumentarProgreso() {
    this->gestoProgreso++;
}

void ManejadorGestos::setValorAnterior ( float anterior ) {
    this->valorAnterior = anterior;
}

void ManejadorGestos::reiniciarValores() {
    this->valorAnterior = this->predeterminado;
    this->gestoProgreso = 0;
}


#include "ManejadorGestos.h"



ManejadorGestos::ManejadorGestos()
{
    this->valorAnterior2 = 0;
    this->predeterminado2 = 0;
}


ManejadorGestos::~ManejadorGestos()
{
}

void ManejadorGestos::asignarValores ( float anterior, int completo )
{
    this->valorAnterior = anterior;
    this->predeterminado = anterior;
    this->gestoProgreso = 0;
    this->gestoCompleto = completo;
}

void ManejadorGestos::asignarValores ( float anterior, float anterior2, int completo )
{
    this->valorAnterior = anterior;
    this->valorAnterior2 = anterior2;
    this->predeterminado = anterior;
    this->predeterminado2 = anterior2;
    this->gestoProgreso = 0;
    this->gestoCompleto = completo;
}

float ManejadorGestos::getValorAnterior()
{
    return this->valorAnterior;
}

float ManejadorGestos::getValorAnterior2()
{
    return valorAnterior2;
}

int ManejadorGestos::getGestoProgreso()
{
    return this->gestoProgreso;
}

int ManejadorGestos::getGestoCompleto()
{
    return this->gestoCompleto;
}

void ManejadorGestos::aumentarProgreso()
{
    this->gestoProgreso++;
}

void ManejadorGestos::setValorAnterior ( float anterior )
{
    this->valorAnterior = anterior;
}

void ManejadorGestos::setValorAnterior ( float anterior, float anterior2 )
{
    this->valorAnterior = anterior;
    this->valorAnterior2 = anterior2;
}

void ManejadorGestos::reiniciarValores()
{
    this->valorAnterior = this->predeterminado;
    this->valorAnterior2 = this->predeterminado2;
    this->gestoProgreso = 0;
}

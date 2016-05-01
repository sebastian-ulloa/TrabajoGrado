#include "ManejadorGestos.h"


ManejadorGestos::ManejadorGestos()
{
	this->valorAnterior2 = 0;
	this->predeterminado2 = 0;
}

ManejadorGestos::~ManejadorGestos()
{
}

/**********************************************************************************************//**
 * Asigna valores iniciales. Define cuál es el valor con el que debe comenzar el gesto
 * y la duración del mismo.
 **************************************************************************************************/

void ManejadorGestos::asignarValores(float anterior, int completo)
{
	this->valorAnterior = anterior;
	this->predeterminado = anterior;
	this->gestoProgreso = 0;
	this->gestoCompleto = completo;
}

/**********************************************************************************************//**
* Asigna valores iniciales. Define cuál es el valor con el que debe comenzar el gesto
* y la duración del mismo. Método diseñado para gestos que necesitan recordar dos coordenadas o 
distancias.
**************************************************************************************************/

void ManejadorGestos::asignarValores(float anterior, float anterior2, int completo)
{
	this->valorAnterior = anterior;
	this->valorAnterior2 = anterior2;
	this->predeterminado = anterior;
	this->predeterminado2 = anterior2;
	this->gestoProgreso = 0;
	this->gestoCompleto = completo;
}

/**********************************************************************************************//**
 * Obtiene el valor de la coordenada o distancia anterior.
 **************************************************************************************************/

float ManejadorGestos::getValorAnterior()
{
	return this->valorAnterior;
}

/**********************************************************************************************//**
 * Obtiene el valor de la coordenada2 o distancia2 anterior.
 **************************************************************************************************/

float ManejadorGestos::getValorAnterior2()
{
	return valorAnterior2;
}

/**********************************************************************************************//**
 * Obtiene el progreso del gesto.
 **************************************************************************************************/

int ManejadorGestos::getGestoProgreso()
{
	return this->gestoProgreso;
}

/**********************************************************************************************//**
 * Obtiene el valor con el que el gesto se define como completo.
 **************************************************************************************************/

int ManejadorGestos::getGestoCompleto()
{
	return this->gestoCompleto;
}

/** Aumentar progreso sobre el gesto realizado. */
void ManejadorGestos::aumentarProgreso()
{
	this->gestoProgreso++;
}

/**********************************************************************************************//**
 * Modifica el valor de la coordenada o distancia anterior.
 **************************************************************************************************/

void ManejadorGestos::setValorAnterior(float anterior)
{
	this->valorAnterior = anterior;
}

/**********************************************************************************************//**
 * Modifica el valor de la coordenada/distancia y la coordenada2/distancia2 anterior.	
 **************************************************************************************************/

void ManejadorGestos::setValorAnterior(float anterior, float anterior2)
{
	this->valorAnterior = anterior;
	this->valorAnterior2 = anterior2;
}

/** Reiniciar valores del gesto. */
void ManejadorGestos::reiniciarValores()
{
	this->valorAnterior = this->predeterminado;
	this->valorAnterior2 = this->predeterminado2;
	this->gestoProgreso = 0;
}

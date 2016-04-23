#pragma once
#include "../Modelo/Deformacion.h"
#include "../Vista/Visualizacion.h"
#include "ole2.h"
#include <Windows.h>
#include <NuiApi.h>
#include <math.h>
#include "ManejadorGestos.h"
#include <vector>



#ifndef _GESTO_
#define _GESTO_
typedef
enum _GESTO
{
    MANO_DERECHA_ARRIBA = 1,
    MANO_IZQUIERDA_ARRIBA = 2,

    ROTAR_DERECHA = 3,
    ROTAR_IZQUIERDA = 4,
    ROTAR_ARRIBA = 5,
    ROTAR_ABAJO = 6,

    MANOS_ARRIBA = 7,

    ZOOM_IN = 8,
    ZOOM_OUT = 9,

    MOVER_DERECHA = 10,
    MOVER_IZQUIERDA = 11,
    MOVER_ARRIBA = 12,
    MOVER_ABAJO = 13,
    NO_GESTO = 0
} 	GESTO;

#endif _GESTO_

class Kinect
{
public:
    Kinect();
    ~Kinect();
    void inicializar();
private:
    int empezarGesto;
    GESTO gesto;
    INuiSensor* sensor;
    HANDLE m_hNextSkeletonEvent;
    Deformacion *deformacion;
    Visualizacion *visualizacion;
    bool identificador;
    float distanciaInicial;
    float inicialDerechaY;
    float inicialIzquierdaY;
    void deformar();
    bool inicializarKinect();
    float redondear ( float n );
    void deteccion();
    void procesarGestos();
    float distancia ( float x1, float x2, float y1, float y2 );
    std::vector<ManejadorGestos> valoresGestos;
    void asignarValoresGestos();
    void reiniciarGestos();
    void convertirCoordenadas ( double x, double y );

};


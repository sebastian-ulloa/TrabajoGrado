#pragma once
#include "../Modelo/Deformacion.h"
#include "../Vista/Visualizacion.h"
#include <Windows.h>
#include <NuiApi.h>
#include <math.h>
#include "ManejadorGestos.h"
#include <vector>



#ifndef _GESTO_
#define _GESTO_
typedef
enum _GESTO {
    MANO_DERECHA_ARRIBA = 1,
    MANO_IZQUIERDA_ARRIBA = 2,

    ROTAR_DERECHA = 3,
    ROTAR_IZQUIERDA = 4,

    MANOS_ARRIBA = 5,
    ZOOM_IN= 6,
    ZOOM_OUT= 7,

    NO_GESTO = 0,
} 	GESTO;

#endif _GESTO_

class Kinect {
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
    void deformar();
    bool inicializarKinect();
    void deteccion();
    void procesarGestos();
    float distancia ( float x1, float x2, float y1, float y2 );
    std::vector<ManejadorGestos> valoresGestos;
    void asignarValoresGestos();
};


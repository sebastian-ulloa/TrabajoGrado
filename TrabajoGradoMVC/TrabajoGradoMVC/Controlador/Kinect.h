#pragma once
#include "../Modelo/Deformacion.h"
#include "../Vista/Visualizacion.h"
#include <ole2.h>
#include <windows.h>
#include <NuiApi.h>
#include <iostream>
#include <math.h>
#include "ManejadorGestos.h"
#include <vector>
#include <KinectInteraction.h>
using namespace std;

#ifndef _GESTO_
#define _GESTO_
typedef
enum _GESTO
{
    MANO_DERECHA_ARRIBA = 1,
    MANO_IZQUIERDA_ARRIBA = 2,

    ROTAR_DERECHA = 3,
    ROTAR_IZQUIERDA = 4,

    MANOS_ARRIBA = 5,
    ZOOM_IN = 6,
    ZOOM_OUT = 7,
    MOVER_DERECHA = 8,
    MOVER_IZQUIERDA = 9,
    MOVER_ARRIBA = 10,
    MOVER_ABAJO = 11,
    NO_GESTO = 0,
} 	GESTO;

#endif _GESTO_

class ineractionClient :public INuiInteractionClient
{
public:
    ineractionClient()
    {
        ;
    }
    ~ineractionClient()
    {
        ;
    }
    STDMETHOD ( GetInteractionInfoAtLocation ) ( THIS_ DWORD skeletonTrackingId, NUI_HAND_TYPE handType, FLOAT x, FLOAT y,
            _Out_ NUI_INTERACTION_INFO *pInteractionInfo )
    {
        if ( pInteractionInfo )
        {
            pInteractionInfo->IsPressTarget = FALSE;//must add
            pInteractionInfo->IsGripTarget = TRUE;    //must add
            pInteractionInfo->PressTargetControlId  = 0;
            pInteractionInfo->PressAttractionPointX = 0.f;
            pInteractionInfo->PressAttractionPointY = 0.f;
            return S_OK;
        }
        return E_POINTER;
        //return S_OK;
    }

    STDMETHODIMP_ ( ULONG )    AddRef()
    {
        return 2;
    }
    STDMETHODIMP_ ( ULONG )    Release()
    {
        return 1;
    }
    STDMETHODIMP            QueryInterface ( REFIID riid, void **ppv )
    {
        return S_OK;
    }


};

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
    ineractionClient m_nuiIClient;
    INuiInteractionStream *m_nuiIStream;
    HANDLE m_hNextInteractionEvent;
    HANDLE m_hNextDepthFrameEvent;
    HANDLE m_pDepthStreamHandle;
    void deformar();
    void getDepthData();
    bool inicializarKinect();
    void deteccion();
    int ShowInteraction();
    void procesarGestos();
    float distancia ( float x1, float x2, float y1, float y2 );
    std::vector<ManejadorGestos> valoresGestos;
    void asignarValoresGestos();
    void reiniciarGestos();

};


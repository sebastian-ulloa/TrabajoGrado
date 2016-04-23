#include "Kinect.h"


Kinect::Kinect()
{
    deformacion = new Deformacion();
    visualizacion = new Visualizacion();
    gesto = NO_GESTO;
    empezarGesto = 0;
    identificador = false;
}


Kinect::~Kinect()
{
}

void Kinect::procesarGestos()
{
    NUI_SKELETON_FRAME skeletonFrame = { 0 };
    HRESULT hr = sensor->NuiSkeletonGetNextFrame ( 0, &skeletonFrame );
    if ( FAILED ( hr ) )
    {
        return;
    }
    sensor->NuiTransformSmooth ( &skeletonFrame, NULL );
    for ( int i = 0; i < NUI_SKELETON_COUNT; ++i )
    {
        NUI_SKELETON_TRACKING_STATE trackingState = skeletonFrame.SkeletonData[i].eTrackingState;
        if ( NUI_SKELETON_TRACKED == trackingState )
        {
            Vector4 manoDerecha = skeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT];
            Vector4 codoDerecho = skeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT];
            Vector4 manoIzquierda = skeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT];
            Vector4 codoIzquierdo = skeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT];
            Vector4 hombroCentro = skeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER];
            if ( gesto == NO_GESTO )
            {
                if ( ( manoDerecha.y >= codoDerecho.y ) && ( manoIzquierda.y >= codoIzquierdo.y )
                        && valoresGestos[MANOS_ARRIBA].getGestoProgreso() <= valoresGestos[MANOS_ARRIBA].getGestoCompleto() )
                {
                    valoresGestos[MANOS_ARRIBA].aumentarProgreso();
                    if ( valoresGestos[MANOS_ARRIBA].getGestoProgreso() == valoresGestos[MANOS_ARRIBA].getGestoCompleto() )
                    {
                        valoresGestos[MANOS_ARRIBA].reiniciarValores();
                        std::cout << "Empezo gesto manos arriba" << std::endl;
                        gesto = MANOS_ARRIBA;
                        identificador = true;
                    }
                }
                else
                {
                    if ( ( manoDerecha.y > codoDerecho.y )
                            && valoresGestos[MANO_DERECHA_ARRIBA].getGestoProgreso() <= valoresGestos[MANO_DERECHA_ARRIBA].getGestoCompleto() )
                    {
                        valoresGestos[MANO_DERECHA_ARRIBA].aumentarProgreso();
                        if ( valoresGestos[MANO_DERECHA_ARRIBA].getGestoProgreso() == valoresGestos[MANO_DERECHA_ARRIBA].getGestoCompleto() )
                        {
                            valoresGestos[MANO_DERECHA_ARRIBA].reiniciarValores();
                            std::cout << "Empezo gesto mano derecha" << std::endl;
                            gesto = MANO_DERECHA_ARRIBA;
                        }
                    }
                    if ( ( manoIzquierda.y > codoIzquierdo.y )
                            && valoresGestos[MANO_IZQUIERDA_ARRIBA].getGestoProgreso() <= valoresGestos[MANO_IZQUIERDA_ARRIBA].getGestoCompleto() )
                    {
                        valoresGestos[MANO_IZQUIERDA_ARRIBA].aumentarProgreso();
                        if ( valoresGestos[MANO_IZQUIERDA_ARRIBA].getGestoProgreso() == valoresGestos[MANO_IZQUIERDA_ARRIBA].getGestoCompleto() )
                        {
                            valoresGestos[MANO_IZQUIERDA_ARRIBA].reiniciarValores();
                            std::cout << "Empezo gesto mano izquierda" << std::endl;
                            gesto = MANO_IZQUIERDA_ARRIBA;
                        }
                    }
                }
            }
            else
            {
                if ( gesto == MANOS_ARRIBA )
                {
                    if ( hombroCentro.z - manoDerecha.z < 0.3 && hombroCentro.z - manoIzquierda.z < 0.3 )
                    {
                        std::cout << "Termino gesto" << std::endl;
                        reiniciarGestos();
                        gesto = NO_GESTO;
                    }
                    else
                    {
                        /*---------------------------------------------------------------------------------------------------------*/
                        /*MOVER DERECHA*/
                        if ( valoresGestos[MOVER_DERECHA].getValorAnterior() < redondear ( manoDerecha.x )
                                &&  valoresGestos[MOVER_DERECHA].getValorAnterior2() < redondear ( manoIzquierda.x )
                                && valoresGestos[MOVER_DERECHA].getGestoProgreso() <= valoresGestos[MOVER_DERECHA].getGestoCompleto()
                           )
                        {
                            valoresGestos[MOVER_DERECHA].aumentarProgreso();
                            valoresGestos[MOVER_DERECHA].setValorAnterior ( redondear ( manoDerecha.x ), redondear ( manoIzquierda.x ) );
                            if ( valoresGestos[MOVER_DERECHA].getGestoProgreso() == valoresGestos[MOVER_DERECHA].getGestoCompleto() )
                            {
                                std::cout << "mover derecha" << std::endl;
                                visualizacion->moverHorizontal ( true );
                                reiniciarGestos();
                            }
                        }
                        /*---------------------------------------------------------------------------------------------------------*/
                        /*MOVER IZQUIERDA*/
                        if ( valoresGestos[MOVER_IZQUIERDA].getValorAnterior() > redondear ( manoDerecha.x )
                                &&  valoresGestos[MOVER_IZQUIERDA].getValorAnterior2() > redondear ( manoIzquierda.x )
                                && valoresGestos[MOVER_IZQUIERDA].getGestoProgreso() <= valoresGestos[MOVER_IZQUIERDA].getGestoCompleto()
                           )
                        {
                            valoresGestos[MOVER_IZQUIERDA].aumentarProgreso();
                            valoresGestos[MOVER_IZQUIERDA].setValorAnterior ( redondear ( manoDerecha.x ), redondear ( manoIzquierda.x ) );
                            if ( valoresGestos[MOVER_IZQUIERDA].getGestoProgreso() == valoresGestos[MOVER_IZQUIERDA].getGestoCompleto() )
                            {
                                std::cout << "mover izquierda" << std::endl;
                                visualizacion->moverHorizontal ( false );
                                reiniciarGestos();
                            }
                        }
                        /*---------------------------------------------------------------------------------------------------------*/
                        /*MOVER ARRIBA*/
                        if ( valoresGestos[MOVER_ARRIBA].getValorAnterior() < redondear ( manoDerecha.y )
                                &&  valoresGestos[MOVER_ARRIBA].getValorAnterior2() < redondear ( manoIzquierda.y )
                                && valoresGestos[MOVER_ARRIBA].getGestoProgreso() <= valoresGestos[MOVER_ARRIBA].getGestoCompleto()
                           )
                        {
                            valoresGestos[MOVER_ARRIBA].aumentarProgreso();
                            valoresGestos[MOVER_ARRIBA].setValorAnterior ( redondear ( manoDerecha.y ), redondear ( manoIzquierda.y ) );
                            if ( valoresGestos[MOVER_ARRIBA].getGestoProgreso() == valoresGestos[MOVER_ARRIBA].getGestoCompleto() )
                            {
                                std::cout << "mover arriba" << std::endl;
                                visualizacion->moverVertical ( true );
                                reiniciarGestos();
                            }
                        }
                        /*---------------------------------------------------------------------------------------------------------*/
                        /*MOVER ABAJO*/
                        if ( valoresGestos[MOVER_ABAJO].getValorAnterior() > redondear ( manoDerecha.y )
                                &&  valoresGestos[MOVER_ABAJO].getValorAnterior2() > redondear ( manoIzquierda.y )
                                && valoresGestos[MOVER_ABAJO].getGestoProgreso() <= valoresGestos[MOVER_ABAJO].getGestoCompleto()
                           )
                        {
                            valoresGestos[MOVER_ABAJO].aumentarProgreso();
                            valoresGestos[MOVER_ABAJO].setValorAnterior ( redondear ( manoDerecha.y ), redondear ( manoIzquierda.y ) );
                            if ( valoresGestos[MOVER_ABAJO].getGestoProgreso() == valoresGestos[MOVER_ABAJO].getGestoCompleto() )
                            {
                                std::cout << "mover abajo" << std::endl;
                                visualizacion->moverVertical ( false );
                                reiniciarGestos();
                            }
                        }
                    }
                }
                if ( gesto == MANO_IZQUIERDA_ARRIBA )
                {
                    if ( manoDerecha.y > codoDerecho.y )
                    {
                        if ( hombroCentro.z - manoDerecha.z < 0.3 && hombroCentro.z - manoIzquierda.z < 0.3 )
                        {
                            std::cout << "Termino gesto" << std::endl;
                            reiniciarGestos();
                            gesto = NO_GESTO;
                        }
                        else
                        {
                            float dist = distancia ( manoDerecha.x, manoIzquierda.x, manoDerecha.y, manoIzquierda.y );
                            /*---------------------------------------------------------------------------------------------------------*/
                            /*ZOOM IN*/
                            if ( dist > valoresGestos[ZOOM_IN].getValorAnterior()
                                    && valoresGestos[ZOOM_IN].getGestoProgreso() <= valoresGestos[ZOOM_IN].getGestoCompleto()
                               )
                            {
                                valoresGestos[ZOOM_IN].aumentarProgreso();
                                valoresGestos[ZOOM_IN].setValorAnterior ( dist );
                                if ( valoresGestos[ZOOM_IN].getGestoProgreso() == valoresGestos[ZOOM_IN].getGestoCompleto() )
                                {
                                    std::cout << "zoom in" << std::endl;
                                    visualizacion->zoom ( true );
                                    reiniciarGestos();
                                }
                            }
                            /*---------------------------------------------------------------------------------------------------------*/
                            /*ZOOM OUT*/
                            if ( dist < valoresGestos[ZOOM_OUT].getValorAnterior()
                                    && valoresGestos[ZOOM_OUT].getGestoProgreso() <= valoresGestos[ZOOM_OUT].getGestoCompleto() )
                            {
                                valoresGestos[ZOOM_OUT].aumentarProgreso();
                                valoresGestos[ZOOM_OUT].setValorAnterior ( dist );
                                if ( valoresGestos[ZOOM_OUT].getGestoProgreso() == valoresGestos[ZOOM_OUT].getGestoCompleto() )
                                {
                                    std::cout << "zoom out" << std::endl;
                                    visualizacion->zoom ( false );
                                    reiniciarGestos();
                                }
                            }
                        }
                    }
                    else
                    {
                        if ( hombroCentro.z - manoIzquierda.z < 0.3 )
                        {
                            std::cout << "Termino gesto" << std::endl;
                            reiniciarGestos();
                        }
                        else
                        {
                            /*---------------------------------------------------------------------------------------------------------*/
                            /*ROTAR IZQUIERDA*/
                            if ( valoresGestos[ROTAR_IZQUIERDA].getValorAnterior() > redondear ( manoIzquierda.x )
                                    && valoresGestos[ROTAR_IZQUIERDA].getGestoProgreso() <= valoresGestos[ROTAR_IZQUIERDA].getGestoCompleto() )
                            {
                                valoresGestos[ROTAR_IZQUIERDA].aumentarProgreso();
                                valoresGestos[ROTAR_IZQUIERDA].setValorAnterior ( redondear ( manoIzquierda.x ) );
                                if ( valoresGestos[ROTAR_IZQUIERDA].getGestoProgreso() == valoresGestos[ROTAR_IZQUIERDA].getGestoCompleto() )
                                {
                                    std::cout << "rotar izquierda\n";
                                    visualizacion->rotarHorizontal ( false );
                                    reiniciarGestos();
                                }
                            }
                            /*---------------------------------------------------------------------------------------------------------*/
                            /*ROTAR DERECHA*/
                            if ( valoresGestos[ROTAR_DERECHA].getValorAnterior() < redondear ( manoIzquierda.x )
                                    && valoresGestos[ROTAR_DERECHA].getGestoProgreso() <= valoresGestos[ROTAR_DERECHA].getGestoCompleto() )
                            {
                                valoresGestos[ROTAR_DERECHA].aumentarProgreso();
                                valoresGestos[ROTAR_DERECHA].setValorAnterior ( redondear ( manoIzquierda.x ) );
                                if ( valoresGestos[ROTAR_DERECHA].getGestoProgreso() == valoresGestos[ROTAR_DERECHA].getGestoCompleto() )
                                {
                                    std::cout << "rotar derecha\n";
                                    visualizacion->rotarHorizontal ( true );
                                    reiniciarGestos();
                                }
                            }
                            /*---------------------------------------------------------------------------------------------------------*/
                            /*ROTAR ARRIBA*/
                            if ( valoresGestos[ROTAR_ARRIBA].getValorAnterior() < redondear ( manoIzquierda.y )
                                    && valoresGestos[ROTAR_ARRIBA].getGestoProgreso() <= valoresGestos[ROTAR_ARRIBA].getGestoCompleto() )
                            {
                                valoresGestos[ROTAR_ARRIBA].aumentarProgreso();
                                valoresGestos[ROTAR_ARRIBA].setValorAnterior ( redondear ( manoIzquierda.y ) );
                                if ( valoresGestos[ROTAR_ARRIBA].getGestoProgreso() == valoresGestos[ROTAR_ARRIBA].getGestoCompleto() )
                                {
                                    std::cout << "rotar arriba\n";
                                    visualizacion->rotarVertical ( true );
                                    reiniciarGestos();
                                }
                            }
                            /*---------------------------------------------------------------------------------------------------------*/
                            /*ROTAR ABAJO*/
                            if ( valoresGestos[ROTAR_ABAJO].getValorAnterior() > redondear ( manoIzquierda.y )
                                    && valoresGestos[ROTAR_ABAJO].getGestoProgreso() <= valoresGestos[ROTAR_ABAJO].getGestoCompleto() )
                            {
                                valoresGestos[ROTAR_ABAJO].aumentarProgreso();
                                valoresGestos[ROTAR_ABAJO].setValorAnterior ( redondear ( manoIzquierda.y ) );
                                if ( valoresGestos[ROTAR_ABAJO].getGestoProgreso() == valoresGestos[ROTAR_ABAJO].getGestoCompleto() )
                                {
                                    std::cout << "rotar abajo\n";
                                    visualizacion->rotarVertical ( true );
                                    reiniciarGestos();
                                }
                            }
                        }
                    }
                }
                if ( gesto == MANO_DERECHA_ARRIBA )
                {
                    visualizacion->activarDeformacion ( true );
                    convertirCoordenadas ( manoDerecha.x, manoDerecha.y );
                }
                if ( manoDerecha.y < 0 && manoIzquierda.y < 0 )
                {
                    std::cout << "Termino gesto" << std::endl;
                    gesto = NO_GESTO;
                }
            }
            /*std::cout << "---------------------------------------------" << std::endl;
            std::cout << "Mano derecha: ";
            std::cout << manoDerecha.x << " ";
            std::cout << manoDerecha.y << " ";
            std::cout << manoDerecha.z << std::endl;
            std::cout << "Mano izquierda: ";
            std::cout << manoIzquierda.x << " ";
            std::cout << manoIzquierda.y << " ";
            std::cout << manoIzquierda.z << std::endl;*/
        }
    }
}

float Kinect::distancia ( float x1, float x2, float y1, float y2 )
{
    return sqrt ( pow ( x2 - x1, 2 ) + pow ( y2 - y1, 2 ) );
}

void Kinect::asignarValoresGestos()
{
    ManejadorGestos mj;
    for ( int i = 0; i < 14; i++ )
    {
        valoresGestos.push_back ( mj );
    }
    valoresGestos[MANO_DERECHA_ARRIBA].asignarValores ( 0, 20 );
    valoresGestos[MANO_IZQUIERDA_ARRIBA].asignarValores ( 0, 20 );
    valoresGestos[ROTAR_DERECHA].asignarValores ( -2, 10 );
    valoresGestos[ROTAR_IZQUIERDA].asignarValores ( 2, 10 );
    valoresGestos[ROTAR_ARRIBA].asignarValores ( -2, 10 );
    valoresGestos[ROTAR_ABAJO].asignarValores ( 2, 10 );
    valoresGestos[MANOS_ARRIBA].asignarValores ( 0, 5 );
    valoresGestos[ZOOM_IN].asignarValores ( 0, 8 );
    valoresGestos[ZOOM_OUT].asignarValores ( 10, 8 );
    valoresGestos[MOVER_DERECHA].asignarValores ( -2, -2, 7 );
    valoresGestos[MOVER_IZQUIERDA].asignarValores ( 2, 2, 7 );
    valoresGestos[MOVER_ARRIBA].asignarValores ( 0, 0, 7 ); //TODO
    valoresGestos[MOVER_ABAJO].asignarValores ( 4, 4, 7 ); //TODO
}

void Kinect::reiniciarGestos()
{
    for ( int i = 0; i < 14; i++ )
    {
        valoresGestos[i].reiniciarValores();
    }
    identificador = true;
}

void Kinect::deteccion()
{
    if ( WAIT_OBJECT_0 == WaitForSingleObject ( m_hNextSkeletonEvent, 0 ) )
    {
        procesarGestos();
        // Sleep ( 3000 );
    }
}

void Kinect::inicializar()
{
    if ( !inicializarKinect() )
    {
        std::cout << "Kinect no esta conectado";
        return;
    }
    visualizacion->mostrarObjetoInicial ( deformacion->crearEsfera() );
    this->asignarValoresGestos();
    while ( true )
    {
        this->deteccion();
    }
}

void Kinect::deformar()
{
    visualizacion->actualizarVentana ( deformacion->inflar() );
}

bool Kinect::inicializarKinect()
{
    INuiSensor * pNuiSensor;
    int iSensorCount = 0;
    HRESULT hr = NuiGetSensorCount ( &iSensorCount );
    if ( FAILED ( hr ) )
    {
        return false;
    }
    // Look at each Kinect sensor
    for ( int i = 0; i < iSensorCount; ++i )
    {
        // Create the sensor so we can check status, if we can't create it, move on to the next
        hr = NuiCreateSensorByIndex ( i, &pNuiSensor );
        if ( FAILED ( hr ) )
        {
            continue;
        }
        // Get the status of the sensor, and if connected, then we can initialize it
        hr = pNuiSensor->NuiStatus();
        if ( S_OK == hr )
        {
            sensor = pNuiSensor;
            break;
        }
        // This sensor wasn't OK, so release it since we're not using it
        pNuiSensor->Release();
    }
    if ( NULL != sensor )
    {
        // Initialize the Kinect and specify that we'll be using skeleton
        hr = sensor->NuiInitialize ( NUI_INITIALIZE_FLAG_USES_SKELETON );
        if ( SUCCEEDED ( hr ) )
        {
            // Create an event that will be signaled when skeleton data is available
            m_hNextSkeletonEvent = CreateEventW ( NULL, TRUE, FALSE, NULL );
            // Open a skeleton stream to receive skeleton data
            hr = sensor->NuiSkeletonTrackingEnable ( m_hNextSkeletonEvent, 0 );
        }
    }
    if ( NULL == sensor || FAILED ( hr ) )
    {
        std::cout << "No ready Kinect found!";
        return false;
    }
    return true;
}

float Kinect::redondear ( float n )
{
    return roundf ( n * 100 ) / 100;
}

void Kinect::convertirCoordenadas ( double x, double y )
{
    x = ( ( x ) * 22 ) / 1;
    y = ( ( y ) * 11 ) / 1;
    visualizacion->ubicacionEsferaDeformacion ( x, y );
    double *d = visualizacion->puntoCercano ( x, y );
    if ( d != NULL )
    {
        visualizacion->actualizarVentana ( deformacion->deformar ( d, true ) );
    }
}
#include "Kinect.h"


Kinect::Kinect()
{
    deformacion = new Deformacion();
    visualizacion = new Visualizacion();
    gesto = NO_GESTO;
    empezarGesto = 0;
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
                    float dist = distancia ( manoDerecha.x, manoIzquierda.x, manoDerecha.y, manoIzquierda.y );
                    if ( dist > valoresGestos[ZOOM_IN].getValorAnterior()
                            && valoresGestos[ZOOM_IN].getGestoProgreso() <= valoresGestos[ZOOM_IN].getGestoCompleto() )
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
                    if ( valoresGestos[MOVER_DERECHA].getValorAnterior() < manoDerecha.x &&  valoresGestos[MOVER_DERECHA].getValorAnterior2() < manoIzquierda.x
                            && valoresGestos[MOVER_DERECHA].getGestoProgreso() <= valoresGestos[MOVER_DERECHA].getGestoCompleto() )
                    {
                        valoresGestos[MOVER_DERECHA].aumentarProgreso();
                        valoresGestos[MOVER_DERECHA].setValorAnterior ( manoDerecha.x , manoIzquierda.x );
                        if ( valoresGestos[MOVER_DERECHA].getGestoProgreso() == valoresGestos[MOVER_DERECHA].getGestoCompleto() )
                        {
                            std::cout << "mover derecha" << std::endl;
                            visualizacion->moverHorizontal ( true );
                            reiniciarGestos();
                        }
                    }
                    if ( valoresGestos[MOVER_IZQUIERDA].getValorAnterior() > manoDerecha.x &&  valoresGestos[MOVER_IZQUIERDA].getValorAnterior2() > manoIzquierda.x
                            && valoresGestos[MOVER_IZQUIERDA].getGestoProgreso() <= valoresGestos[MOVER_IZQUIERDA].getGestoCompleto() )
                    {
                        valoresGestos[MOVER_IZQUIERDA].aumentarProgreso();
                        valoresGestos[MOVER_IZQUIERDA].setValorAnterior ( manoDerecha.x, manoIzquierda.x );
                        if ( valoresGestos[MOVER_IZQUIERDA].getGestoProgreso() == valoresGestos[MOVER_IZQUIERDA].getGestoCompleto() )
                        {
                            std::cout << "mover izquierda" << std::endl;
                            visualizacion->moverHorizontal ( false );
                            reiniciarGestos();
                        }
                    }
                }
                //Aca se empieza a deformar
                /*if (gesto == MANO_DERECHA_ARRIBA) {
                	if (manoIzquierda.y > codoIzquierdo.y && empezarRotar <= 5) {// rotar con la mano izquierda
                		empezarRotar++;
                		if (empezarRotar == 5) {
                			rotar = true;
                			empezarRotar = 0;
                		}
                	}
                	if (manoIzquierda.y < codoIzquierdo.y) {
                		rotar = false;
                		empezarGestoRD = 0;
                		empezarGestoRI = 0;
                		empezarRotar = 0;
                		anteriorManoRotarD = -2;
                		anteriorManoRotarI = 2;
                	}

                	if (rotar) {
                		if ((manoIzquierda.x > anteriorManoRotarD) && empezarGestoRD <= gestoCompleto) {
                			empezarGestoRD++;
                			anteriorManoRotarD = manoIzquierda.x;
                			if (empezarGestoRD == gestoCompleto) {
                				std::cout << "Rotar mano izquierda hacia la derecha" << std::endl;
                				cambiarColor(true);
                				empezarGestoRD = 0;
                				anteriorManoRotarD = -2;
                			}
                		}
                		if ((manoIzquierda.x < anteriorManoRotarI) && empezarGestoRI <= gestoCompleto) {
                			empezarGestoRI++;
                			anteriorManoRotarI = manoIzquierda.x;
                			if (empezarGestoRI == gestoCompleto) {
                				std::cout << "Rotar mano izquierda hacia la izquierda" << std::endl;
                				cambiarColor(false);
                				empezarGestoRI = 0;
                				anteriorManoRotarI = 2;
                			}
                		}
                	}

                }


                if (gesto == MANO_IZQUIERDA_ARRIBA) {
                	if (manoDerecha.y > codoDerecho.y && empezarRotar <= 5) {// rotar con la mano izquierda
                		empezarRotar++;
                		if (empezarRotar == 5) {
                			rotar = true;
                			empezarRotar = 0;
                		}
                	}
                	if (manoDerecha.y < codoDerecho.y) {
                		rotar = false;
                		empezarGestoRD = 0;
                		empezarGestoRI = 0;
                		empezarRotar = 0;
                		anteriorManoRotarD = -2;
                		anteriorManoRotarI = 2;
                	}

                	if (rotar) {
                		if ((manoDerecha.x > anteriorManoRotarD) && empezarGestoRD <= gestoCompleto) {
                			empezarGestoRD++;
                			anteriorManoRotarD = manoDerecha.x;
                			if (empezarGestoRD == gestoCompleto) {
                				std::cout << "Rotar mano derecha hacia la derecha" << std::endl;
                				empezarGestoRD = 0;
                				cambiarColor(true);
                				anteriorManoRotarD = -2;
                			}
                		}
                		if ((manoDerecha.x < anteriorManoRotarI) && empezarGestoRI <= gestoCompleto) {
                			empezarGestoRI++;
                			anteriorManoRotarI = manoDerecha.x;
                			if (empezarGestoRI == gestoCompleto) {
                				std::cout << "Rotar mano derecha hacia la izquierda" << std::endl;
                				empezarGestoRI = 0;
                				cambiarColor(false);
                				anteriorManoRotarI = 2;
                			}
                		}
                	}

                }
                */
                if ( manoDerecha.y < 0 && manoIzquierda.y < 0 )
                {
                    std::cout << "Termino gesto" << std::endl;
                    gesto = NO_GESTO;
                    reiniciarGestos();
                }
            }
            /*std::cout << "---------------------------------------------" << std::endl;
            std::cout << "Mano derecha: ";
            std::cout << manoDerecha.x << " ";
            std::cout << manoDerecha.y << " ";
            std::cout << manoDerecha.z << std::endl;*/
        }
    }
}

void Kinect::reiniciarGestos()
{
    for ( int i = 0; i < 11; i++ )
    {
        valoresGestos[i].reiniciarValores();
    }
}
float Kinect::distancia ( float x1, float x2, float y1, float y2 )
{
    return sqrt ( pow ( x2 - x1, 2 ) + pow ( y2 - y1, 2 ) );
}

void Kinect::asignarValoresGestos()
{
    ManejadorGestos mj;
    for ( int i = 0; i <= 11; i++ )
    {
        valoresGestos.push_back ( mj );
    }
    // Valor "anterior" determina el progreso del gesto (Tiempos o distancias)
    // Valor "completo" para determinar cuando el gesto acaba
    valoresGestos[MANO_DERECHA_ARRIBA].asignarValores ( 0, 20 );
    valoresGestos[MANO_IZQUIERDA_ARRIBA].asignarValores ( 0, 20 );
    valoresGestos[ROTAR_DERECHA].asignarValores ( -2, 10 );
    valoresGestos[ROTAR_IZQUIERDA].asignarValores ( 2, 10 );
    valoresGestos[MANOS_ARRIBA].asignarValores ( 0, 5 );
    valoresGestos[ZOOM_IN].asignarValores ( 0, 8 );
    valoresGestos[ZOOM_OUT].asignarValores ( 10, 8 );
    valoresGestos[MOVER_DERECHA].asignarValores ( -2,-2, 7 );
    valoresGestos[MOVER_IZQUIERDA].asignarValores ( 2, 2, 7 );
    valoresGestos[MOVER_ARRIBA].asignarValores ( -2, 10 ); //TODO
    valoresGestos[MOVER_ABAJO].asignarValores ( -2, 10 ); //TODO
}

void Kinect::deteccion()
{
    if ( WAIT_OBJECT_0 == WaitForSingleObject ( m_hNextInteractionEvent, 0 ) )
    {
        cout << "entro ";
        ShowInteraction();
    }
    if ( WAIT_OBJECT_0 == WaitForSingleObject ( m_hNextSkeletonEvent, 0 ) )
    {
        // procesarGestos();
    }
    if (  WAIT_OBJECT_0 == WaitForSingleObject ( m_hNextDepthFrameEvent, 0 ) )
    {
        getDepthData();
    }
}

void Kinect::getDepthData()
{
    HRESULT hr;
    NUI_IMAGE_FRAME imageFrame;
    // GET DEPTH FRAME
    hr = sensor->NuiImageStreamGetNextFrame ( m_pDepthStreamHandle, 0, &imageFrame );
    if ( FAILED ( hr ) )
    {
        return;
    }
    BOOL nearMode;
    INuiFrameTexture* pTexture;
    hr = sensor->NuiImageFrameGetDepthImagePixelFrameTexture (
             m_pDepthStreamHandle, &imageFrame, &nearMode, &pTexture );
    if ( FAILED ( hr ) )
    {
        sensor->NuiImageStreamReleaseFrame ( m_pDepthStreamHandle, &imageFrame );
        return;
    }
    NUI_LOCKED_RECT LockedRect;
    // LOCK THE FRAME SO THE KINECT KNOWS NOT TO MODIFY IT
    pTexture->LockRect ( 0, &LockedRect, NULL, 0 );
    // TEST IF THE RECEIVED DATA IS VALID
    if ( LockedRect.Pitch != 0 )
    {
        //HAND INTERACTION
        m_nuiIStream->ProcessDepth ( LockedRect.size, LockedRect.pBits, imageFrame.liTimeStamp );
    }
    pTexture->UnlockRect ( 0 );
    pTexture->Release();
    sensor->NuiImageStreamReleaseFrame ( m_pDepthStreamHandle, &imageFrame );
}

int Kinect::ShowInteraction()
{
    NUI_INTERACTION_FRAME Interaction_Frame;
    HRESULT hr = m_nuiIStream->GetNextFrame ( 0, &Interaction_Frame );
    if ( hr != S_OK )
    {
        if ( hr == E_POINTER )
            cout << "E_POINTER          " << endl;
        else if ( hr == E_NUI_FRAME_NO_DATA )
        {
            cout << "E_NUI_FRAME_NO_DATA" << endl;
        }
        return -1;
    }
    int trackingID = 0;
    int event;
    for ( int i = 0; i<NUI_SKELETON_COUNT; i++ )
    {
        COORD pos = { 0,0 };
        HANDLE hOut = GetStdHandle ( STD_OUTPUT_HANDLE );
        SetConsoleCursorPosition ( hOut, pos );
        static int frameCount = 0;
        frameCount++;
        for ( int j = 0; j<NUI_USER_HANDPOINTER_COUNT; j++ )
        {
            if ( ( frameCount % 3 ) == 1 )
            {
                trackingID = Interaction_Frame.UserInfos[i].SkeletonTrackingId;
                event = Interaction_Frame.UserInfos[i].HandPointerInfos[j].HandEventType;
                DWORD state = Interaction_Frame.UserInfos[i].HandPointerInfos[j].State;
                NUI_HAND_TYPE type = Interaction_Frame.UserInfos[i].HandPointerInfos[j].HandType;
                if ( type == NUI_HAND_TYPE_NONE )
                    continue;
                if ( ( state&&NUI_HANDPOINTER_STATE_TRACKED ) == 0 )
                    continue;
                if ( ( state&&NUI_HANDPOINTER_STATE_ACTIVE ) == 0 )
                    continue;
                cout << "id=" << trackingID << "--------HandEventType=";
                if ( event == NUI_HAND_EVENT_TYPE_GRIP )
                {
                    cout << "Grip ！！！   ";
                }
                else if ( event == NUI_HAND_EVENT_TYPE_GRIPRELEASE )
                {
                    cout << "Grip Release ";
                }
                else
                {
                    cout << "No Event!    ";
                }
                cout << "    HandType=";
                if ( type == NUI_HAND_TYPE_NONE )
                    cout << "No    Hand";
                else if ( type == NUI_HAND_TYPE_LEFT )
                    cout << "Left  Hand";
                else if ( type == NUI_HAND_TYPE_RIGHT )
                    cout << "Right Hand";
                cout << endl;
                //////NUI_HANDPOINTER_STATE
                cout << "STATE_TRACKED =      ";
                if ( ( state&&NUI_HANDPOINTER_STATE_TRACKED ) == 1 )
                    cout << "   TRACKED!";
                else
                    cout << " No TRACKED";
                cout << endl;
                cout << "STATE_ACTIVE =       ";
                if ( ( state&&NUI_HANDPOINTER_STATE_ACTIVE ) == 1 )
                    cout << "     ACTIVE";
                else
                    cout << " Not ACTIVE";
                cout << endl;
                cout << "STATE_INTERACTIVE =  ";
                if ( ( state&&NUI_HANDPOINTER_STATE_INTERACTIVE ) == 1 )
                    cout << "    INTERACTIVE!";
                else
                    cout << " Not INTERACTIVE";
                cout << endl;
                cout << "STATE_PRESSED =      ";
                if ( ( state&&NUI_HANDPOINTER_STATE_PRESSED ) == 1 )
                    cout << "    PRESSED!";
                else
                    cout << " Not PRESSED";
                cout << endl;
                cout << "PRIMARY_FOR_USER =   ";
                if ( ( state&&NUI_HANDPOINTER_STATE_PRIMARY_FOR_USER ) == 1 )
                    cout << "    PRIMARY!";
                else
                    cout << " Not PRIMARY";
                cout << endl;
                //	system("\f");
            }
        }
    }
    return 0;
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
    visualizacion->mostrarObjetoInicial ( deformacion->crearEsfera() ); //Crear la esfera y mostrarla en VTK
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
        hr = sensor->NuiInitialize ( NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_SKELETON );
        if ( SUCCEEDED ( hr ) )
        {
            // Create an event that will be signaled when skeleton data is available
            m_hNextSkeletonEvent = CreateEventW ( NULL, TRUE, FALSE, NULL );
            // Open a skeleton stream to receive skeleton data
            hr = sensor->NuiSkeletonTrackingEnable ( m_hNextSkeletonEvent, 0 );
            m_hNextDepthFrameEvent=CreateEventW ( NULL, TRUE, FALSE, NULL );
            m_pDepthStreamHandle = NULL;
            hr = sensor->NuiImageStreamOpen ( NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, NUI_IMAGE_RESOLUTION_640x480, 0, 2, m_hNextDepthFrameEvent,
                                              &m_pDepthStreamHandle );
            if ( FAILED ( hr ) )
            {
                cout << "Could not open depth" << endl;
                return hr;
            }
            //create event interaction
            m_hNextInteractionEvent = CreateEventW ( NULL, TRUE, FALSE, NULL );
            hr = NuiCreateInteractionStream ( sensor, ( INuiInteractionClient * ) &m_nuiIClient, &m_nuiIStream );
            if ( FAILED ( hr ) )
            {
                cout << "Could not open Interation stream video" << endl;
                return hr;
            }
            hr = m_nuiIStream->Enable ( m_hNextInteractionEvent );
            if ( FAILED ( hr ) )
            {
                cout << "Could not open Interation stream video" << endl;
                return hr;
            }
        }
    }
    if ( NULL == sensor || FAILED ( hr ) )
    {
        std::cout << "No ready Kinect found!";
        return false;
    }
    return true;
}
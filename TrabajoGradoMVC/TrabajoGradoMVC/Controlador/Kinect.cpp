#include "Kinect.h"


Kinect::Kinect() {
    deformacion = new Deformacion();
    visualizacion = new Visualizacion();
    gesto = NO_GESTO;
    empezarGesto = 0;
}


Kinect::~Kinect() {
}

void Kinect::procesarGestos() {
    NUI_SKELETON_FRAME skeletonFrame = { 0 };
    HRESULT hr = sensor->NuiSkeletonGetNextFrame ( 0, &skeletonFrame );
    if ( FAILED ( hr ) ) {
        return;
    }
    sensor->NuiTransformSmooth ( &skeletonFrame, NULL );
    for ( int i = 0; i < NUI_SKELETON_COUNT; ++i ) {
        NUI_SKELETON_TRACKING_STATE trackingState = skeletonFrame.SkeletonData[i].eTrackingState;
        if ( NUI_SKELETON_TRACKED == trackingState ) {
            Vector4 manoDerecha = skeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT];
            Vector4 codoDerecho = skeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT];
            Vector4 manoIzquierda = skeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT];
            Vector4 codoIzquierdo = skeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT];
            if ( gesto == NO_GESTO ) {
                if ( ( manoDerecha.y > codoDerecho.y ) && empezarGesto <= iniciarGesto ) {
                    empezarGesto++;
                    if ( empezarGesto == iniciarGesto ) {
                        std::cout << "Empezo gesto mano derecha" << std::endl;
                        gesto = MANO_DERECHA_ARRIBA;
                        empezarGesto = 0;
                    }
                }
                if ( ( manoIzquierda.y > codoIzquierdo.y ) && empezarGesto <= iniciarGesto ) {
                    empezarGesto++;
                    if ( empezarGesto == iniciarGesto ) {
                        std::cout << "Empezo gesto mano izquierda" << std::endl;
                        gesto = MANO_IZQUIERDA_ARRIBA;
                        empezarGesto = 0;
                    }
                }
                if ( ( manoDerecha.y >= codoDerecho.y ) && ( manoIzquierda.y > codoIzquierdo.y )
                        && valoresGestos[MANOS_ARRIBA].getGestoProgreso() <=
                        valoresGestos[MANOS_ARRIBA].getGestoCompleto() ) {
                    empezarGesto++;
                    if ( empezarGesto == iniciarGesto ) {
                        std::cout << "Empezo gesto manos arriba" << std::endl;
                        gesto = MANOS_ARRIBA;
                        empezarGesto = 0;
                    }
                }
            } else {
                if ( gesto == MANOS_ARRIBA ) {
                    float dist = distancia ( manoDerecha.x, manoIzquierda.x, manoDerecha.y,manoIzquierda.y );
                    if ( dist > valoresGestos[ZOOM_IN].getValorAnterior
                            && valoresGestos[ZOOM_IN].getGestoProgreso() <= valoresGestos[ZOOM_IN].getGestoCompleto() ) {
                        valoresGestos[ZOOM_IN].aumentarProgreso();
                        valoresGestos[ZOOM_IN].setValorAnterior ( dist );
                        if ( valoresGestos[ZOOM_IN].getGestoProgreso == valoresGestos[ZOOM_IN].getGestoCompleto ) {
                            this->deformar();
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
                if ( manoDerecha.y < 0 && manoIzquierda.y < 0 ) {
                    std::cout << "Termino gesto" << std::endl;
                    gesto = NO_GESTO;
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

float Kinect::distancia ( float x1, float x2, float y1, float y2 ) {
    return sqrt ( pow ( x2 - x1, 2 ) + pow ( y2 - y1, 2 ) );
}

void Kinect::asignarValoresGestos() {
    ManejadorGestos mj;
    for ( int i = 0; i < 7; i++ ) {
        valoresGestos.push_back ( mj );
    }
    valoresGestos[MANO_DERECHA_ARRIBA];
    valoresGestos[MANO_IZQUIERDA_ARRIBA];
    valoresGestos[ROTAR_DERECHA];
    valoresGestos[ROTAR_IZQUIERDA];
    valoresGestos[MANOS_ARRIBA];
    valoresGestos[ZOOM_IN];
    valoresGestos[ZOOM_OUT];
}

void Kinect::deteccion() {
    if ( WAIT_OBJECT_0 == WaitForSingleObject ( m_hNextSkeletonEvent, 0 ) ) {
        procesarGestos();
    }
}

void Kinect::inicializar() {
    if ( !inicializarKinect() ) {
        std::cout << "Kinect no esta conectado";
        return;
    }
    visualizacion->mostrarObjetoInicial ( deformacion->crearEsfera() );
    this->asignarValoresGestos();
    while ( true ) {
        this->deteccion();
    }
}

void Kinect::deformar() {
    visualizacion->actualizarVentana ( deformacion->inflar() );
}

bool Kinect::inicializarKinect() {
    INuiSensor * pNuiSensor;
    int iSensorCount = 0;
    HRESULT hr = NuiGetSensorCount ( &iSensorCount );
    if ( FAILED ( hr ) ) {
        return false;
    }
    // Look at each Kinect sensor
    for ( int i = 0; i < iSensorCount; ++i ) {
        // Create the sensor so we can check status, if we can't create it, move on to the next
        hr = NuiCreateSensorByIndex ( i, &pNuiSensor );
        if ( FAILED ( hr ) ) {
            continue;
        }
        // Get the status of the sensor, and if connected, then we can initialize it
        hr = pNuiSensor->NuiStatus();
        if ( S_OK == hr ) {
            sensor = pNuiSensor;
            break;
        }
        // This sensor wasn't OK, so release it since we're not using it
        pNuiSensor->Release();
    }
    if ( NULL != sensor ) {
        // Initialize the Kinect and specify that we'll be using skeleton
        hr = sensor->NuiInitialize ( NUI_INITIALIZE_FLAG_USES_SKELETON );
        if ( SUCCEEDED ( hr ) ) {
            // Create an event that will be signaled when skeleton data is available
            m_hNextSkeletonEvent = CreateEventW ( NULL, TRUE, FALSE, NULL );
            // Open a skeleton stream to receive skeleton data
            hr = sensor->NuiSkeletonTrackingEnable ( m_hNextSkeletonEvent, 0 );
        }
    }
    if ( NULL == sensor || FAILED ( hr ) ) {
        std::cout << "No ready Kinect found!";
        return false;
    }
    return true;
}
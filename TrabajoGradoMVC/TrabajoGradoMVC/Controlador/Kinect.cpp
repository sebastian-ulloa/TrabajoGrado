#include "Kinect.h"



Kinect::Kinect()
{
	deformacion = new Deformacion();
	visualizacion = new Visualizacion();
}


Kinect::~Kinect()
{
}

void Kinect::inicializar()
{
	visualizacion->mostrarGridInicial(deformacion->crearEsfera());

}

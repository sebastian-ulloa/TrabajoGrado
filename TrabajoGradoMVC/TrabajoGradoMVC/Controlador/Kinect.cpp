#include "Kinect.h"
#include <Windows.h>


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
//	this->deformar();
//	visualizacion->actualizarVentana();
}

void Kinect::deformar()
{
	deformacion->inflar();
}

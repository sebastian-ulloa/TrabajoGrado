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
	this->deformar();
	
	std::cout << "despues de visualizar" << std::endl;
}

void Kinect::deformar()
{
	visualizacion->actualizarVentana(deformacion->inflar());
}

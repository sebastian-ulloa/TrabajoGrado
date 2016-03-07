#pragma once
#include "../Modelo/Deformacion.h"
#include "../Vista/Visualizacion.h"
#ifdef _WIN32
#include <Windows.h>
#endif
class Kinect
{
public:
	Kinect();
	~Kinect();
	void inicializar();
private:
	Deformacion *deformacion;
	Visualizacion *visualizacion;
	void deformar();
};


#pragma once
#include "..\Modelo\Deformacion.h"
#include "..\Vista\Visualizacion.h"
class Kinect
{
public:
	Kinect();
	~Kinect();

	void inicializar();
private:
	Deformacion *deformacion;
	Visualizacion *visualizacion;
	
};


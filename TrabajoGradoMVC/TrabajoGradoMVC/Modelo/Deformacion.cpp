#include "Deformacion.h"


Deformacion::Deformacion()
{
}

Deformacion::~Deformacion()
{
}

vtkUnstructuredGrid* Deformacion::crearEsfera()
{
	TEsfera::Pointer esfera = TEsfera::New();
	TEsfera::VectorType escala;
	escala.Fill(5.0);
	esfera->SetScale(escala);
	esfera->SetResolution(5);
	esfera->Update();
	esferaSimplex = triangularASimplex(esfera->GetOutput());
	grid = conversor.MeshToUnstructuredGrid(esfera->GetOutput());
	return grid;
}

TMallaSimplex::Pointer Deformacion::triangularASimplex(TMallaTriangular::Pointer malla)
{
	TConvertir::Pointer convertir = TConvertir::New();
	convertir->SetInput(malla);
	convertir->Update();
	return convertir->GetOutput();
}



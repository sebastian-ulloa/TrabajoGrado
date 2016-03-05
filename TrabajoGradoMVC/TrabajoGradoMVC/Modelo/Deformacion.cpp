#include "Deformacion.h"


Deformacion::Deformacion()
{
}

Deformacion::~Deformacion()
{
}

vtkPolyData* Deformacion::crearEsfera()
{
	TEsfera::Pointer esfera = TEsfera::New();
	TEsfera::VectorType escala;
	escala.Fill(5.0);
	esfera->SetScale(escala);
	esfera->SetResolution(5);
	esfera->Update();
	esferaSimplex = triangularASimplex(esfera->GetOutput());
	this->inflar();
	grid = conversor.meshToPolydata(simplexATriangular(esferaSimplex));
	return grid;
}

TMallaSimplex::Pointer Deformacion::triangularASimplex(TMallaTriangular::Pointer malla)
{
	TConvertir::Pointer convertir = TConvertir::New();
	convertir->SetInput(malla);
	convertir->Update();
	return convertir->GetOutput();
}

TMallaTriangular* Deformacion::simplexATriangular(TMallaSimplex::Pointer malla)
{
	TConvertirContrario::Pointer convertir = TConvertirContrario::New();
	convertir->SetInput(malla);
	convertir->Update();
	return convertir->GetOutput();
}

void Deformacion::inflar()
{
	TDeformar::Pointer balloon = TDeformar::New();
	balloon->SetInput(esferaSimplex);
	balloon->SetAlpha(0.2);
	balloon->SetBeta(0.1);
	balloon->SetKappa(0.01);
	balloon->SetIterations(20);
	balloon->SetRigidity(0);
	balloon->Update();
	esferaSimplex = balloon->GetOutput();
	grid = conversor.meshToPolydata(simplexATriangular(esferaSimplex));
}



#include "Deformacion.h"


Deformacion::Deformacion()
{
	esferaSimplex = TMallaSimplex::New();
	grid = vtkPolyData::New();
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
	//this->inflar();
	TConvertir::Pointer convertir = TConvertir::New();
	convertir->SetInput(esfera->GetOutput());
	//convertir->Update();

	TConvertirContrario::Pointer convertir2 = TConvertirContrario::New();
	convertir2->SetInput(convertir->GetOutput());
	//convertir2->Update();
/*	TMallaTriangular* mt = TMallaTriangular::New();
	mt = simplexATriangular(esferaSimplex);*/
	grid = conversor.meshToPolydata(esfera->GetOutput());
	return grid;
}

TMallaSimplex* Deformacion::triangularASimplex(TMallaTriangular* malla)
{
	TConvertir::Pointer convertir = TConvertir::New();
	convertir->SetInput(malla);
	convertir->Update();
	return convertir->GetOutput();
}

TMallaTriangular* Deformacion::simplexATriangular(TMallaSimplex* malla)
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
//	grid = conversor.meshToPolydata(simplexATriangular(esferaSimplex));
}



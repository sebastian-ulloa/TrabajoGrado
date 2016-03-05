#include "Deformacion.h"


Deformacion::Deformacion()
{
	esferaSimplex = TMallaSimplex::New();
	grid = vtkPolyData::New();
	balloon = TDeformar::New();
	convertirSimplex = TConvertir::New();
	convertirTriangulo = TConvertirContrario::New();
	calculadora = Tcalculadora::New();
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
	convertirSimplex->SetInput(esfera->GetOutput());
	esferaSimplex = convertirSimplex->GetOutput();
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
	calculadora->SetSimplexMesh(convertirSimplex->GetOutput());
	calculadora->Compute();
	std::cout << "1: " << calculadora->GetVolume();
	balloon->SetInput(esferaSimplex);
	balloon->SetAlpha(0.2);
	balloon->SetBeta(0.1);
	balloon->SetKappa(0.01);
	balloon->SetIterations(20);
	balloon->SetRigidity(0);
	esferaSimplex = balloon->GetOutput();
	convertirTriangulo->SetInput(esferaSimplex);
	convertirTriangulo->Update();
	calculadora->SetSimplexMesh(esferaSimplex);
	calculadora->Compute();
	std::cout << "  -2: " << calculadora->GetVolume();
	balloon->SetInput(esferaSimplex);
	balloon->SetAlpha(0.3);
	balloon->SetBeta(0.1);
	balloon->SetKappa(0.1);
	balloon->SetIterations(200);
	balloon->SetRigidity(0);
	esferaSimplex = balloon->GetOutput();
	calculadora->SetSimplexMesh(esferaSimplex);
	calculadora->Compute();
	std::cout << "  -3: " << calculadora->GetVolume();
	grid = conversor.meshToPolydata(convertirTriangulo->GetOutput());
}



#include "Deformacion.h"

Deformacion::Deformacion() {
	esferaSimplex = TMallaSimplex::New();
	grid = vtkPolyData::New();
	balloon = TDeformar::New();
	convertirSimplex = TConvertir::New();
	convertirTriangulo = TConvertirContrario::New();
	calculadora = Tcalculadora::New();
}

Deformacion::~Deformacion() {
}

vtkPolyData* Deformacion::crearEsfera() {
	TEsfera::Pointer esfera = TEsfera::New();
	TEsfera::VectorType escala;
	escala.Fill(5.0);
	esfera->SetScale(escala);
	esfera->SetResolution(5);
	esfera->Update();
	convertirSimplex->SetInput(esfera->GetOutput());
	//convertirSimplex->Update();
	esferaSimplex = convertirSimplex->GetOutput();
	grid = conversor.meshToPolydata(esfera->GetOutput());
	return grid;
}

TMallaSimplex* Deformacion::triangularASimplex(TMallaTriangular* malla) {
	TConvertir::Pointer convertir = TConvertir::New();
	convertir->SetInput(malla);
	convertir->Update();
	return convertir->GetOutput();
}

TMallaTriangular* Deformacion::simplexATriangular(TMallaSimplex* malla) {
	TConvertirContrario::Pointer convertir = TConvertirContrario::New();
	convertir->SetInput(malla);
	convertir->Update();
	return convertir->GetOutput();
}

void Deformacion::inflar() {
	balloon->SetInput(esferaSimplex);
	balloon->SetAlpha(0.2);
	balloon->SetBeta(0.1);
	balloon->SetKappa(0.01);
	balloon->SetIterations(2000);
	balloon->SetRigidity(0);
	esferaSimplex = balloon->GetOutput();
	convertirTriangulo->SetInput(esferaSimplex);
	convertirTriangulo->Update();
	grid = conversor.meshToPolydata(convertirTriangulo->GetOutput());
}


#include "Deformacion.h"

Deformacion::Deformacion() {
	esferaSimplex = TMallaSimplex::New();
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
	esferaSimplex = triangularASimplex(esfera->GetOutput());
	esferaSimplex->DisconnectPipeline();
	return conversor.meshToPolydata(esfera->GetOutput());
}

TMallaSimplex::Pointer Deformacion::triangularASimplex(TMallaTriangular::Pointer malla) {
	TConvertir::Pointer convertir = TConvertir::New();
	convertir->SetInput(malla);
	convertir->Update();
	return convertir->GetOutput();
}

TMallaTriangular::Pointer Deformacion::simplexATriangular(TMallaSimplex::Pointer malla) {
	TConvertirContrario::Pointer convertir = TConvertirContrario::New();
	convertir->SetInput(malla);
	convertir->Update();
	return convertir->GetOutput();
}

vtkPolyData* Deformacion::inflar() {
	balloon->SetInput(esferaSimplex);
	//balloon->SetAlpha(0.1);
	//balloon->SetBeta(5);
	balloon->SetKappa(0.01);
	balloon->Update();
	esferaSimplex = balloon->GetOutput();
	esferaSimplex->DisconnectPipeline();
	return conversor.meshToPolydata(simplexATriangular(esferaSimplex));
}


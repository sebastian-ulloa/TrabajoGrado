#pragma once

#include "ITKaVTK.h"
#include <itkRegularSphereMeshSource.h>
#include <itkTriangleMeshToSimplexMeshFilter.h>
#include <itkSimplexMeshToTriangleMeshFilter.h>
#include <itkDeformableSimplexMesh3DBalloonForceFilter.h>
#include <itkSimplexMeshVolumeCalculator.h>
typedef itk::SimplexMesh< float, 3 > TMallaSimplex;
typedef itk::RegularSphereMeshSource< TMallaTriangular > TEsfera;
typedef itk::TriangleMeshToSimplexMeshFilter< TMallaTriangular, TMallaSimplex > TConvertir;
typedef itk::SimplexMeshToTriangleMeshFilter < TMallaSimplex, TMallaTriangular > TConvertirContrario;
typedef itk::DeformableSimplexMesh3DBalloonForceFilter< TMallaSimplex, TMallaSimplex > TDeformar;
typedef itk::SimplexMeshVolumeCalculator <TMallaSimplex> Tcalculadora;

class Deformacion
{
public:
	Deformacion();
	~Deformacion();
	vtkPolyData* crearEsfera();
	void inflar();
private:
	ITKaVTK conversor;
	TMallaSimplex* esferaSimplex;
	TDeformar::Pointer balloon;
	TConvertir::Pointer convertirSimplex;
	TConvertirContrario::Pointer convertirTriangulo;
	vtkPolyData* grid;
	TMallaSimplex* triangularASimplex(TMallaTriangular* malla);
	TMallaTriangular* simplexATriangular(TMallaSimplex* malla);
	Tcalculadora::Pointer calculadora;

};


#pragma once

#include "ITKaVTK.h"
#include <itkRegularSphereMeshSource.h>
#include <itkTriangleMeshToSimplexMeshFilter.h>
#include <itkSimplexMeshToTriangleMeshFilter.h>
#include <itkDeformableSimplexMesh3DBalloonForceFilter.h>

typedef itk::SimplexMesh< float, 3 > TMallaSimplex;
typedef itk::RegularSphereMeshSource< TMallaTriangular > TEsfera;
typedef itk::TriangleMeshToSimplexMeshFilter< TMallaTriangular, TMallaSimplex > TConvertir;
typedef itk::SimplexMeshToTriangleMeshFilter < TMallaSimplex, TMallaTriangular > TConvertirContrario;
typedef itk::DeformableSimplexMesh3DBalloonForceFilter< TMallaSimplex, TMallaSimplex > TDeformar;

class Deformacion
{
public:
	Deformacion();
	~Deformacion();
	vtkPolyData* crearEsfera();
	void inflar();
private:
	ITKaVTK conversor;
	TMallaSimplex::Pointer esferaSimplex;
	vtkPolyData* grid;
	TMallaSimplex::Pointer triangularASimplex(TMallaTriangular::Pointer malla);
	TMallaTriangular* simplexATriangular(TMallaSimplex::Pointer malla);

};


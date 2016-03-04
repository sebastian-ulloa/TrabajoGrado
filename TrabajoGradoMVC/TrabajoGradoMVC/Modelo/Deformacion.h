#pragma once

#include <itkSimplexMesh.h>
#include <itkRegularSphereMeshSource.h>
#include <itkTriangleMeshToSimplexMeshFilter.h>
#include <itkDeformableSimplexMesh3DBalloonForceFilter.h>
#include "ITKaVTK.h"

typedef itk::Mesh< float, 3 >  TMallaTriangular;
typedef itk::SimplexMesh< float, 3 > TMallaSimplex;
typedef itk::RegularSphereMeshSource< TMallaTriangular > TEsfera;
typedef itk::TriangleMeshToSimplexMeshFilter< TMallaTriangular, TMallaSimplex > TConvertir;

class Deformacion
{
public:
	Deformacion();
	~Deformacion();
	vtkUnstructuredGrid* crearEsfera();
private:
	ITKaVTK conversor;
	TMallaSimplex::Pointer esferaSimplex;
	vtkUnstructuredGrid* grid;
	TMallaSimplex::Pointer triangularASimplex(TMallaTriangular::Pointer malla);

};


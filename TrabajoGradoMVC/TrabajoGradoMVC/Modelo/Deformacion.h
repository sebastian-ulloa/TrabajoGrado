#pragma once

#include "ITKaVTK.h"
#include <itkRegularSphereMeshSource.h>
#include <itkTriangleMeshToSimplexMeshFilter.h>
#include <itkSimplexMeshToTriangleMeshFilter.h>
#include <itkDeformableSimplexMesh3DBalloonForceFilter.h>
#include <itkSimplexMeshVolumeCalculator.h>
#include <itkPointsLocator.h>
typedef itk::SimplexMesh< float, 3 > TMallaSimplex;
typedef itk::RegularSphereMeshSource< TMallaTriangular > TEsfera;
typedef itk::TriangleMeshToSimplexMeshFilter< TMallaTriangular, TMallaSimplex > TConvertir;
typedef itk::SimplexMeshToTriangleMeshFilter < TMallaSimplex, TMallaTriangular > TConvertirContrario;
typedef itk::DeformableSimplexMesh3DBalloonForceFilter< TMallaSimplex, TMallaSimplex > TDeformar;
typedef itk::PointsLocator <TMallaSimplex::PointsContainer> TPointsLocator;

class Deformacion
{
public:
    Deformacion();
    ~Deformacion();
    vtkPolyData* crearEsfera();
    vtkPolyData* inflar();
    vtkPolyData * deformar ( double  *punto, bool repeler );


private:
    ITKaVTK conversor;
    TMallaTriangular::Pointer triangulo;
    TMallaSimplex::Pointer esferaSimplex;
    TDeformar::Pointer balloon;
    TConvertir::Pointer convertirSimplex;
    TConvertirContrario::Pointer convertirTriangulo;
    TMallaSimplex::Pointer triangularASimplex ( TMallaTriangular::Pointer malla );
    TMallaTriangular::Pointer simplexATriangular ( TMallaSimplex::Pointer malla );


};


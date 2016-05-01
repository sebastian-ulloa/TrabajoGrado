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

/** Clase encargada de la creación y deformación del modelo tridimensional. */
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
    /** Malla simplex que es manipulada y deformada a lo largo de la ejecución */
    TMallaSimplex::Pointer esferaSimplex;    
    TMallaSimplex::Pointer triangularASimplex ( TMallaTriangular::Pointer malla );
    TMallaTriangular::Pointer simplexATriangular ( TMallaSimplex::Pointer malla );


};


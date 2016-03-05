#pragma once

#include <itkQuadrilateralCell.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <itkSimplexMesh.h>

typedef itk::Mesh< float, 3 >  TMallaTriangular;


class ITKaVTK
{
public:
	ITKaVTK();
	~ITKaVTK();
	vtkUnstructuredGrid* MeshToUnstructuredGrid(TMallaTriangular* mesh);
};


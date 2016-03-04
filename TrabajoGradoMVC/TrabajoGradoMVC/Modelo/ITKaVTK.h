#pragma once

#include <itkQuadrilateralCell.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include "Deformacion.h"

class ITKaVTK
{
public:
	ITKaVTK();
	~ITKaVTK();
	vtkUnstructuredGrid* MeshToUnstructuredGrid(TMallaTriangular::Pointer mesh);
};


#pragma once

#include <itkQuadrilateralCell.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <itkSimplexMesh.h>
#include <vtkPolyData.h>
#include <itkPoint.h>
typedef itk::Mesh< float, 3 >  TMallaTriangular;
typedef itk::Point< float, 3 > PointType;
typedef TMallaTriangular::CellsContainer::ConstIterator  CellIterator;
typedef TMallaTriangular::PointsContainer::ConstIterator  PointIterator;
class ITKaVTK
{
public:
	ITKaVTK();
	~ITKaVTK();
	vtkPolyData* meshToPolydata(TMallaTriangular* mesh);
};


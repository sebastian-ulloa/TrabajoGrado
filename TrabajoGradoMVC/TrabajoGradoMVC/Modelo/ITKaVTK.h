#pragma once


/*=========================================================================
    Esta clase esta basada en el codigo encontrado en la siguiente pagina:
  
  https://github.com/InsightSoftwareConsortium/ITKApps/blob/master/Auxiliary/vtk/vtkPolyDataToITKMesh.cxx
  
  A continuacion se presenta los derechos presentados sobre el codigo por parte
  de InsightSoftwareConsortium:
=========================================================================*/

/*=========================================================================
  Program:   Insight Segmentation & Registration Toolkit
  Module:    vtkPolyDataToITKMesh.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$
  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.
     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.
=========================================================================*/

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

/**     Esta clase esta basada en el codigo encontrado en la siguiente pagina:
  
  https://github.com/InsightSoftwareConsortium/ITKApps/blob/master/Auxiliary/vtk/vtkPolyDataToITKMesh.cxx */
class ITKaVTK
{
public:
	ITKaVTK();
	~ITKaVTK();
	vtkPolyData* meshToPolydata(TMallaTriangular* mesh);
};


#include "ITKaVTK.h"

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

class VistVTKCellsClass
{
    vtkCellArray* m_Cells;
    int* m_LastCell;
    int* m_TypeArray;
public:
    // typedef the itk cells we are interested in
    typedef itk::CellInterface<
    TMallaTriangular::PixelType,
                     TMallaTriangular::CellTraits >  CellInterfaceType;

    typedef itk::LineCell<CellInterfaceType> floatLineCell;
    typedef itk::TriangleCell<CellInterfaceType>      floatTriangleCell;
    typedef itk::QuadrilateralCell<CellInterfaceType> floatQuadrilateralCell;

    // Set the vtkCellArray that will be constructed
    void SetCellArray ( vtkCellArray* a )
    {
        m_Cells = a;
    }

    // Set the cell counter pointer
    void SetCellCounter ( int* i )
    {
        m_LastCell = i;
    }

    // Set the type array for storing the vtk cell types
    void SetTypeArray ( int* i )
    {
        m_TypeArray = i;
    }

    // Visit a triangle and create the VTK_TRIANGLE cell
    void Visit ( unsigned long, floatTriangleCell* t )
    {
        m_Cells->InsertNextCell ( 3, ( vtkIdType* ) t->PointIdsBegin() );
        m_TypeArray[*m_LastCell] = VTK_TRIANGLE;
        ( *m_LastCell )++;
    }

    // Visit a triangle and create the VTK_QUAD cell
    void Visit ( unsigned long, floatQuadrilateralCell* t )
    {
        m_Cells->InsertNextCell ( 4, ( vtkIdType* ) t->PointIdsBegin() );
        m_TypeArray[*m_LastCell] = VTK_QUAD;
        ( *m_LastCell )++;
    }

    // Visit a line and create the VTK_LINE cell
    void Visit ( unsigned long, floatLineCell* t )
    {
        m_Cells->InsertNextCell ( 2, ( vtkIdType* ) t->PointIdsBegin() );
        m_TypeArray[*m_LastCell] = VTK_LINE;
        ( *m_LastCell )++;
    }
};

ITKaVTK::ITKaVTK()
{
}


ITKaVTK::~ITKaVTK()
{
}


vtkPolyData * ITKaVTK::meshToPolydata ( TMallaTriangular* mesh )
{
    //Creat a new vtkPolyData*
    vtkPolyData* newPolyData = vtkPolyData::New();
    //Creat vtkPoints for insertion into newPolyData
    vtkPoints *points = vtkPoints::New();
    //Copy all points into the vtkPolyData structure
    PointIterator pntIterator = mesh->GetPoints()->Begin();
    PointIterator pntItEnd = mesh->GetPoints()->End();
    for ( int i = 0; pntIterator != pntItEnd; ++i, ++pntIterator )
    {
        PointType pnt = pntIterator.Value();
        points->InsertPoint ( i, pnt[0], pnt[1], pnt[2] );
    }
    newPolyData->SetPoints ( points );
    points->Delete();
    //Copy all cells into the vtkPolyData structure
    //Creat vtkCellArray into which the cells are copied
    vtkCellArray* triangle = vtkCellArray::New();
    CellIterator cellIt = mesh->GetCells()->Begin();
    CellIterator cellItEnd = mesh->GetCells()->End();
    for ( int it = 0; cellIt != cellItEnd; ++it, ++cellIt )
    {
        TMallaTriangular::CellType * cellptr = cellIt.Value();
        TMallaTriangular::CellType::PointIdIterator pntIdIter = cellptr->PointIdsBegin();
        TMallaTriangular::CellType::PointIdIterator pntIdEnd = cellptr->PointIdsEnd();
        vtkIdList* pts = vtkIdList::New();
        for ( ; pntIdIter != pntIdEnd; ++pntIdIter )
        {
            pts->InsertNextId ( *pntIdIter );
        }
        triangle->InsertNextCell ( pts );
    }
    newPolyData->SetPolys ( triangle );
    triangle->Delete();
    return newPolyData;
}





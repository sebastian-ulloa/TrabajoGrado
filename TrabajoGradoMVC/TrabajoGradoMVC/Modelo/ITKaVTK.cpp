#include "ITKaVTK.h"
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

	typedef itk::TriangleCell<CellInterfaceType>      floatTriangleCell;
	typedef itk::QuadrilateralCell<CellInterfaceType> floatQuadrilateralCell;

	// Set the vtkCellArray that will be constructed
	void SetCellArray(vtkCellArray* a)
	{
		m_Cells = a;
	}
	// Set the cell counter pointer
	void SetCellCounter(int* i)
	{
		m_LastCell = i;
	}
	// Set the type array for storing the vtk cell types
	void SetTypeArray(int* i)
	{
		m_TypeArray = i;
	}
	// Visit a triangle and create the VTK_TRIANGLE cell 
	void Visit(unsigned long, floatTriangleCell* t)
	{
		m_Cells->InsertNextCell(3, (vtkIdType*)t->PointIdsBegin());
		m_TypeArray[*m_LastCell] = VTK_TRIANGLE;
		(*m_LastCell)++;
	}
	// Visit a triangle and create the VTK_QUAD cell 
	void Visit(unsigned long, floatQuadrilateralCell* t)
	{
		m_Cells->InsertNextCell(4, (vtkIdType*)t->PointIdsBegin());
		m_TypeArray[*m_LastCell] = VTK_QUAD;
		(*m_LastCell)++;
	}
};


ITKaVTK::ITKaVTK()
{
}


ITKaVTK::~ITKaVTK()
{
}



typedef itk::CellInterfaceVisitorImplementation<
	float, TMallaTriangular::CellTraits,
	itk::TriangleCell< itk::CellInterface<TMallaTriangular::PixelType, TMallaTriangular::CellTraits > >,
	VistVTKCellsClass> TriangleVisitor;


typedef itk::CellInterfaceVisitorImplementation<
	float, TMallaTriangular::CellTraits,
	itk::QuadrilateralCell< itk::CellInterface<TMallaTriangular::PixelType, TMallaTriangular::CellTraits > >,
	VistVTKCellsClass> QuadrilateralVisitor;

vtkUnstructuredGrid * ITKaVTK::MeshToUnstructuredGrid(TMallaTriangular::Pointer mesh)
{
	// Get the number of points in the mesh
	int numPoints = mesh->GetNumberOfPoints();
	if (numPoints == 0)
	{
		mesh->Print(std::cerr);
		std::cerr << "no points in Grid " << std::endl;
		exit(-1);
	}
	// Create a vtkUnstructuredGrid
	vtkUnstructuredGrid* vgrid = vtkUnstructuredGrid::New();

	// Create the vtkPoints object and set the number of points
	vtkPoints* vpoints = vtkPoints::New();
	vpoints->SetNumberOfPoints(numPoints);
	// iterate over all the points in the itk mesh filling in
	// the vtkPoints object as we go
	TMallaTriangular::PointsContainer::Pointer points = mesh->GetPoints();
	for (TMallaTriangular::PointsContainer::Iterator i = points->Begin();
	i != points->End(); ++i)
	{
		// Get the point index from the point container iterator
		int idx = i->Index();
		// Set the vtk point at the index with the the coord array from itk
		// itk returns a const pointer, but vtk is not const correct, so
		// we have to use a const cast to get rid of the const
		vpoints->SetPoint(idx, const_cast<float*>(i->Value().GetDataPointer()));
	}
	// Set the points on the vtk grid
	vgrid->SetPoints(vpoints);

	// Now create the cells using the MulitVisitor
	// 1. Create a MultiVisitor
	TMallaTriangular::CellType::MultiVisitor::Pointer mv =
		TMallaTriangular::CellType::MultiVisitor::New();
	// 2. Create a triangle and quadrilateral visitor
	TriangleVisitor::Pointer tv = TriangleVisitor::New();
	QuadrilateralVisitor::Pointer qv = QuadrilateralVisitor::New();
	// 3. Set up the visitors
	int vtkCellCount = 0; // running counter for current cell being inserted into vtk
	int numCells = mesh->GetNumberOfCells();
	int *types = new int[numCells]; // type array for vtk 
									// create vtk cells and estimate the size
	vtkCellArray* cells = vtkCellArray::New();
	cells->EstimateSize(numCells, 4);
	// Set the TypeArray CellCount and CellArray for both visitors
	tv->SetTypeArray(types);
	tv->SetCellCounter(&vtkCellCount);
	tv->SetCellArray(cells);
	qv->SetTypeArray(types);
	qv->SetCellCounter(&vtkCellCount);
	qv->SetCellArray(cells);
	// add the visitors to the multivisitor
	mv->AddVisitor(tv);
	mv->AddVisitor(qv);
	// Now ask the mesh to accept the multivisitor which
	// will Call Visit for each cell in the mesh that matches the
	// cell types of the visitors added to the MultiVisitor
	mesh->Accept(mv);

	// Now set the cells on the vtk grid with the type array and cell array
	vgrid->SetCells(types, cells);

	// Clean up vtk objects (no vtkSmartPointer ... )
	cells->Delete();
	vpoints->Delete();
	// return the vtkUnstructuredGrid
	return vgrid;
}



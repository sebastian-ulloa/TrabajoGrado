#pragma once
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <stdlib.h>
class Visualizacion
{
public:
	Visualizacion();
	~Visualizacion();
	void mostrarGridInicial(vtkUnstructuredGrid* grid);
	void actualizarVentana();
private:
	vtkUnstructuredGrid* grid;
	vtkSmartPointer<vtkRenderWindow> ventana;
	vtkSmartPointer<vtkRenderWindowInteractor> interactor;
};


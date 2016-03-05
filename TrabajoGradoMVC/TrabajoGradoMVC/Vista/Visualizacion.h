#pragma once
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
class Visualizacion
{
public:
	Visualizacion();
	~Visualizacion();
	void mostrarGridInicial(vtkPolyData* grid);
	void actualizarVentana();
	void esferaprueba();
private:
	vtkPolyData* grid;
	vtkSmartPointer<vtkRenderWindow> ventana;
	vtkSmartPointer<vtkRenderWindowInteractor> interactor;
};


#include "Visualizacion.h"



Visualizacion::Visualizacion() {
	ventana = vtkSmartPointer<vtkRenderWindow>::New();
	interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(ventana);
}


Visualizacion::~Visualizacion()
{
}

void Visualizacion::mostrarGridInicial(vtkUnstructuredGrid * grid)
{
	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	mapper->SetInputData(grid);
	actor->SetMapper(mapper);
	renderer->AddActor(actor);
	ventana->AddRenderer(renderer);
	actualizarVentana();
}

void Visualizacion::actualizarVentana()
{
	ventana->Render();
	interactor->Start();
}

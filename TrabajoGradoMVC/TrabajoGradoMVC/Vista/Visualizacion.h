#pragma once
#include  <vtkDataSetMapper.h>
#include  <vtkRenderer.h>
#include  <vtkRenderWindow.h>
#include  <vtkActor.h>
#include  <vtkRenderWindowInteractor.h>
#include  <vtkSmartPointer.h>
#include  <vtkUnstructuredGrid.h>
#include  <vtkSphereSource.h>
#include  <vtkPolyData.h>
#include  <vtkPolyDataMapper.h>
#include  <vtkProperty.h>
#include  <vtkCamera.h>
class Visualizacion {
public:
	Visualizacion();
	~Visualizacion();
	void mostrarObjetoInicial(vtkPolyData* polydata);
	void actualizarVentana(vtkPolyData* p);
	void esferaprueba();
private:
	vtkPolyData* polydata;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkRenderWindow> ventana;
	vtkSmartPointer<vtkRenderWindowInteractor> interactor;
	vtkSmartPointer<vtkCamera> camera ;
};


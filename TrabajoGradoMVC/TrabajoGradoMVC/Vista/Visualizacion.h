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
#include <vtkSphereSource.h>
#include <vtkTransform.h>
#include <vtkKdTree.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
class Visualizacion
{
public:
    Visualizacion();
    ~Visualizacion();
    void mostrarObjetoInicial ( vtkPolyData* polydata );
    void actualizarVentana ( vtkPolyData* p );
    void zoom ( bool accion );
    void moverHorizontal ( bool direccion );
    void moverVertical ( bool direccion );
    void rotarVertical ( bool direccion );
    void rotarHorizontal ( bool direccion );
    void activarDeformacion ( bool activar );
    void ubicacionEsferaDeformacion ( double x, double y );
    void cambioDeformacion ( bool repeler );
    double* puntoCercano ( double x, double y );
    void textoGesto ( const char* texto );
private:
    int z[8];
    int zActual;
    int holguraX;
    int holguraY;
    vtkPolyData* polydata;
    vtkSmartPointer<vtkSphereSource> esferaDeformar;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkPolyDataMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkPolyDataMapper> mapperEsfera;
    vtkSmartPointer<vtkActor> actorEsfera;
    vtkSmartPointer<vtkRenderWindow> ventana;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;
    vtkSmartPointer<vtkCamera> camera;
    vtkSmartPointer<vtkTextActor> textAccion;
    vtkSmartPointer<vtkTextActor> textGesto;

};

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
/** Clase visualización.
Encargada de desplegar en pantalla el modelo tridimensional y los cambios sobre la misma*/
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
    /** Define cuales son las coordenadas en z sobre las que se deforma la esfera en cada rotación. */
    int z[8];
    /** Define la coordena en z actual sobre la que se está deformando en un momento determinado. */
    int zActual;
    /** Define la holgura x que se debe agregar a la esfera deformadora, luego de trasladar horizontalmente el modelo tridimensional. */
    int holguraX;
	/** Define la holgura y que se debe agregar a la esfera deformadora, luego de trasladar verticalmente el modelo tridimensional. */
    int holguraY;
    /** Define el modelo tridimensional. */
    vtkPolyData* polydata;
    /** Define la esfera deformadora. */
    vtkSmartPointer<vtkSphereSource> esferaDeformar;
    
	/** Mapper del modelo tridimensional. */
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	/** Mapper de la esfera deformadora. */
    vtkSmartPointer<vtkPolyDataMapper> mapperEsfera;

	/** Actor del modelo tridimensional. */
	vtkSmartPointer<vtkActor> actor;
	/** Actor de la esfera deformadora. */
	vtkSmartPointer<vtkActor> actorEsfera;
	/** Texto que define la accion que se está realizando. */
	vtkSmartPointer<vtkTextActor> textAccion;
	/** Texto que define el gesto que se está realizando. */
	vtkSmartPointer<vtkTextActor> textGesto;

    vtkSmartPointer<vtkCamera> camera;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkRenderWindow> ventana;
	vtkSmartPointer<vtkRenderWindowInteractor> interactor;
};

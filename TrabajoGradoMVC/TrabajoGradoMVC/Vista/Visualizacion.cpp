#include "Visualizacion.h"

Visualizacion::Visualizacion()
{
    actor = vtkSmartPointer<vtkActor>::New();
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    ventana = vtkSmartPointer<vtkRenderWindow>::New();
    camera = vtkSmartPointer<vtkCamera>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    camera->SetPosition ( 0, 0, 40 );
    ventana->SetSize ( 500, 500 );
    interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow ( ventana );
}

Visualizacion::~Visualizacion()
{
}

void Visualizacion::mostrarObjetoInicial ( vtkPolyData * polydata )
{
    this->polydata = polydata;
    renderer->SetActiveCamera ( camera );
    mapper->SetInputData ( polydata );
    actor->SetMapper ( mapper );
    renderer->AddActor ( actor );
    ventana->AddRenderer ( renderer );
    ventana->Render();
}

void Visualizacion::actualizarVentana ( vtkPolyData* p )
{
    polydata->ShallowCopy ( p );
    ventana->Render();
}
void Visualizacion::esferaprueba()
{
    // Create a sphere
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<
            vtkSphereSource>::New();
    sphereSource->SetCenter ( 0.0, 0.0, 0.0 );
    sphereSource->SetRadius ( 5.0 );
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<
            vtkPolyDataMapper>::New();
    mapper->SetInputConnection ( sphereSource->GetOutputPort() );
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper ( mapper );
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<
            vtkRenderWindow>::New();
    renderWindow->AddRenderer ( renderer );
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow ( renderWindow );
    renderer->AddActor ( actor );
    renderer->SetBackground ( .3, .6, .3 ); // Background color green
    renderWindow->Render();
    renderWindowInteractor->Start();
}

void Visualizacion::zoom ( bool accion )
{
    double factor = 0.8;
    if ( accion )
    {
        factor = 1.25;
    }
    renderer->GetActiveCamera()->Zoom ( factor );
    ventana->Render();
}

void Visualizacion::moverHorizontal ( bool direccion )
{
    double factor = -6.5;
    if ( direccion )
    {
        factor = 6.5;
    }
    renderer->GetActiveCamera()->Yaw ( factor );
    ventana->Render();
}

void Visualizacion::moverVertical ( bool direccion )
{
    double factor = 6.5;
    if ( direccion )
    {
        factor = -6.5;
    }
    renderer->GetActiveCamera()->Pitch ( factor );
    ventana->Render();
}
void Visualizacion::rotarVertical ( bool direccion )
{
    double factor = 45;
    if ( direccion )
    {
        factor = -45;
    }
    renderer->GetActiveCamera()->Azimuth ( factor );
    ventana->Render();
}
void Visualizacion::rotarHorizontal ( bool direccion )
{
    double factor = 45;
    if ( direccion )
    {
        factor = -45;
    }
    renderer->GetActiveCamera()->Roll ( factor );
    ventana->Render();
}
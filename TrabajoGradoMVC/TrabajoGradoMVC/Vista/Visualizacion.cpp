#include "Visualizacion.h"

Visualizacion::Visualizacion()
{
    esferaDeformar = vtkSmartPointer<vtkSphereSource>::New();
    actor = vtkSmartPointer<vtkActor>::New();
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    actorEsfera = vtkSmartPointer<vtkActor>::New();
    mapperEsfera = vtkSmartPointer<vtkPolyDataMapper>::New();
    ventana = vtkSmartPointer<vtkRenderWindow>::New();
    camera = vtkSmartPointer<vtkCamera>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    esferaDeformar->SetRadius ( 1 );
    camera->SetPosition ( 0, 0, 40 );
    ventana->SetSize ( 1366, 670 );
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
    mapperEsfera->SetInputConnection ( esferaDeformar->GetOutputPort() );
    actorEsfera->SetMapper ( mapperEsfera );
    actorEsfera->GetProperty()->SetColor ( 0,0.50196,1 );
    renderer->AddActor ( actorEsfera );
    ventana->AddRenderer ( renderer );
    actorEsfera->VisibilityOff();
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
    double posicion[3];
    actor->GetPosition ( posicion );
    if ( direccion )
    {
        posicion[0] = posicion[0] + 2;
    }
    else
    {
        posicion[0] = posicion[0] - 2;
    }
    actor->SetPosition ( posicion );
    ventana->Render();
}

void Visualizacion::moverVertical ( bool direccion )
{
    double posicion[3];
    actor->GetPosition ( posicion );
    if ( direccion )
    {
        posicion[1] = posicion[1] + 2;
    }
    else
    {
        posicion[1] = posicion[1] - 2;
    }
    actor->SetPosition ( posicion );
    ventana->Render();
}
void Visualizacion::rotarVertical ( bool direccion )
{
    double factor = 45;
    if ( direccion )
    {
        factor = -45;
    }
    actor->RotateY ( factor );
    ventana->Render();
}
void Visualizacion::rotarHorizontal ( bool direccion )
{
    double factor = 45;
    if ( direccion )
    {
        factor = -45;
    }
    actor->RotateX ( factor );
    ventana->Render();
}

void Visualizacion::activarDeformacion ( bool activar )
{
    if ( activar )
    {
        actorEsfera->VisibilityOn();
    }
    else
    {
        actorEsfera->VisibilityOff();
    }
    ventana->Render();
}

void Visualizacion::ubicacionEsferaDeformacion ( double x, double y )
{
    esferaDeformar->SetCenter ( x, y, 0 );
    ventana->Render();
}

double* Visualizacion::puntoCercano ( double x, double y )
{
    double d[3] = { x,y,0 };
    double dist;
    vtkSmartPointer<vtkKdTree> kdtree =
        vtkSmartPointer<vtkKdTree>::New();
    kdtree->BuildLocatorFromPoints ( polydata ) ;
    vtkIdType id =kdtree->FindClosestPointWithinRadius ( 1.0, d, dist );
    return polydata->GetPoint ( id );
}

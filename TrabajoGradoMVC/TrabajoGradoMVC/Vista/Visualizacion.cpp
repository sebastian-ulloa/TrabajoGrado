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
    int secuenciaZ[8] = { 3, 4.8, 3, -0.9, -3, -4.8, -3, 0.9 };
    zActual = 0;
    for ( int i = 0; i < 8; i++ )
    {
        z[i] = secuenciaZ[i];
    }
    holguraX = 0;
    holguraY = 0;
    textAccion = vtkSmartPointer<vtkTextActor>::New();
    textAccion->SetPosition ( 500, 640 );
    textAccion->GetTextProperty()->SetFontSize ( 26 );
    textAccion->GetTextProperty()->SetColor ( 0, 0, 0 );
    textGesto = vtkSmartPointer<vtkTextActor>::New();
    textGesto->SetPosition ( 0, 640 );
    textGesto->GetTextProperty()->SetFontSize ( 26 );
    textGesto->GetTextProperty()->SetColor ( 0, 0, 0 );
}

Visualizacion::~Visualizacion()
{
}

/**********************************************************************************************//**
 * Método encargado de mostrar la escena. Recibe y muestra el modelo tridimensional inicial
 **************************************************************************************************/

void Visualizacion::mostrarObjetoInicial ( vtkPolyData * polydata )
{
    this->polydata = polydata;
    renderer->SetActiveCamera ( camera );
    mapper->SetInputData ( polydata );
    actor->SetMapper ( mapper );
    mapperEsfera->SetInputConnection ( esferaDeformar->GetOutputPort() );
    actorEsfera->SetMapper ( mapperEsfera );
    actorEsfera->GetProperty()->SetColor ( 0, 0.50196, 1 );
    renderer->SetBackground ( 0.52941, 0.82745, 0.92157 );
    renderer->AddActor ( actor );
    renderer->AddActor ( actorEsfera );
    renderer->AddActor2D ( textAccion );
    renderer->AddActor2D ( textGesto );
    ventana->AddRenderer ( renderer );
    actorEsfera->VisibilityOff();
    ventana->Render();
}

/**********************************************************************************************//**
 * Actualizar ventana
 **************************************************************************************************/

void Visualizacion::actualizarVentana ( vtkPolyData* p )
{
    polydata->ShallowCopy ( p );
    ventana->Render();
}

/**********************************************************************************************//**
 * Acerca o aleja la camara sobre el modelo tridimensional
 **************************************************************************************************/

void Visualizacion::zoom ( bool accion )
{
    double factor = 0.8;
    if ( accion )
    {
        textAccion->SetInput ( "Accion: Acercar" );
        factor = 1.25;
    }
    else
    {
        textAccion->SetInput ( "Accion: Alejar" );
    }
    renderer->GetActiveCamera()->Zoom ( factor );
    ventana->Render();
}

/**********************************************************************************************//**
 * Mueve horizontalmente el modelo tridimensional
 **************************************************************************************************/

void Visualizacion::moverHorizontal ( bool direccion )
{
    double posicion[3];
    actor->GetPosition ( posicion );
    if ( direccion )
    {
        posicion[0] = posicion[0] + 4;
        holguraX += 2;
        textAccion->SetInput ( "Accion: Mover derecha" );
    }
    else
    {
        posicion[0] = posicion[0] - 4;
        holguraX -= 2;
        textAccion->SetInput ( "Accion: Mover izquierda" );
    }
    actor->SetPosition ( posicion );
    ventana->Render();
}
/**********************************************************************************************//**
* Mueve verticalmente el modelo tridimensional
**************************************************************************************************/
void Visualizacion::moverVertical ( bool direccion )
{
    double posicion[3];
    actor->GetPosition ( posicion );
    if ( direccion )
    {
        posicion[1] = posicion[1] + 4;
        holguraY += 2;
        textAccion->SetInput ( "Accion: Mover arriba" );
    }
    else
    {
        posicion[1] = posicion[1] - 4;
        holguraY -= 2;
        textAccion->SetInput ( "Accion: Mover abajo" );
    }
    actor->SetPosition ( posicion );
    ventana->Render();
}

/**********************************************************************************************//**
* Rota verticalmente el modelo tridimensional
**************************************************************************************************/
void Visualizacion::rotarVertical ( bool direccion )
{
    double factor = 45;
    if ( direccion )
    {
        factor *= -1;
        textAccion->SetInput ( "Accion: Rotar arriba" );
    }
    else
    {
        textAccion->SetInput ( "Accion: Rotar abajo" );
    }
    actor->RotateWXYZ ( factor, 1, 0, 0 );
    ventana->Render();
}
/**********************************************************************************************//**
* Rota horizontalmente el modelo tridimensional
**************************************************************************************************/
void Visualizacion::rotarHorizontal ( bool direccion )
{
    double factor = -45;
    if ( direccion )
    {
        factor *= -1;
        zActual != 7 ? zActual++ : zActual = 0;
        textAccion->SetInput ( "Accion: Rotar derecha" );
    }
    else
    {
        zActual != 0 ? zActual-- : zActual = 7;
        textAccion->SetInput ( "Accion: Rotar izquierda" );
    }
    actor->RotateWXYZ ( factor, 0, 1, 0 );
    ventana->Render();
}
/**********************************************************************************************//**
* Activa o desactiva la visualización de la esfera deformadora
**************************************************************************************************/
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
/**********************************************************************************************//**
* Define las coordenadas en las que se encuentra la esfera deformadora
**************************************************************************************************/
void Visualizacion::ubicacionEsferaDeformacion ( double x, double y )
{
    actorEsfera->SetPosition ( x + holguraX, y + holguraY, 3 );
    ventana->Render();
}

/**********************************************************************************************//**
 * Cambio sobre la deformacion: atraer o repeler
 **************************************************************************************************/

void Visualizacion::cambioDeformacion ( bool repeler )
{
    if ( repeler )
    {
        textAccion->SetInput ( "Accion: Deformar - repeler" );
        actorEsfera->GetProperty()->SetColor ( 0, 0.50196, 1 );
    }
    else
    {
        textAccion->SetInput ( "Accion: Deformar - atraer" );
        actorEsfera->GetProperty()->SetColor ( 0.8, 0, 0 );
    }
    ventana->Render();
}

/**********************************************************************************************//**
 * Busca el punto más cercano del modelo tridimensional con respecto a la coordenada (x,y) recibida.
 * La coordenada z está definida por el atributo zActual de está clase.
 **************************************************************************************************/

double* Visualizacion::puntoCercano ( double x, double y )
{
    if ( zActual >= 1 && zActual < 5 )
    {
        x *= -1;
    }
    x -= holguraX;
    y -= holguraY;
    double d[3] = { x, y, z[zActual] };
    double dist;
    vtkSmartPointer<vtkKdTree> kdtree = vtkSmartPointer<vtkKdTree>::New();
    kdtree->BuildLocatorFromPoints ( polydata );
    vtkIdType id = kdtree->FindClosestPoint ( d, dist );
    if ( dist <= 1.0 )
    {
        return polydata->GetPoint ( id );
    }
    return NULL;
}

/**********************************************************************************************//**
 * Muestra en pantalla el texto del gesto que se está realizando
 **************************************************************************************************/

void Visualizacion::textoGesto ( const char* texto )
{
    if ( std::strcmp ( texto, "" ) == 0 )
    {
        textAccion->SetInput ( "" );
    }
    textGesto->SetInput ( texto );
    ventana->Render();
}
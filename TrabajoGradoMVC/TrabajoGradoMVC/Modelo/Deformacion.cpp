#include "Deformacion.h"

Deformacion::Deformacion()
{
    esferaSimplex = TMallaSimplex::New();
    balloon = TDeformar::New();
    convertirSimplex = TConvertir::New();
    convertirTriangulo = TConvertirContrario::New();
}

Deformacion::~Deformacion()
{
}

vtkPolyData* Deformacion::crearEsfera()
{
    TEsfera::Pointer esfera = TEsfera::New();
    TEsfera::VectorType escala;
    escala.Fill ( 5.0 );
    esfera->SetScale ( escala );
    esfera->SetResolution ( 5 );
    esfera->Update();
    triangulo = esfera->GetOutput();
    triangulo->DisconnectPipeline();
    esferaSimplex = triangularASimplex ( esfera->GetOutput() );
    esferaSimplex->DisconnectPipeline();
    return conversor.meshToPolydata ( simplexATriangular ( esferaSimplex ) );
}

TMallaSimplex::Pointer Deformacion::triangularASimplex ( TMallaTriangular::Pointer malla )
{
    TConvertir::Pointer convertir = TConvertir::New();
    convertir->SetInput ( malla );
    convertir->Update();
    return convertir->GetOutput();
}

TMallaTriangular::Pointer Deformacion::simplexATriangular ( TMallaSimplex::Pointer malla )
{
    TConvertirContrario::Pointer convertir = TConvertirContrario::New();
    convertir->SetInput ( malla );
    convertir->Update();
    return convertir->GetOutput();
}

vtkPolyData* Deformacion::inflar()
{
    balloon->SetInput ( esferaSimplex );
    //balloon->SetAlpha(0.1);
    //balloon->SetBeta(5);
    balloon->SetKappa ( 0.01 );
    balloon->Update();
    esferaSimplex = balloon->GetOutput();
    esferaSimplex->DisconnectPipeline();
    return conversor.meshToPolydata ( simplexATriangular ( esferaSimplex ) );
}

vtkPolyData * Deformacion::deformar ( double * punto , bool repeler )
{
    TPointsLocator::Pointer ptLocator = TPointsLocator::New();
    ptLocator->SetPoints ( esferaSimplex->GetPoints() );
    ptLocator->Initialize();
    PointType p;
    p[0] = punto[0];
    p[1] = punto[1];
    p[2] = punto[2];
    double idPunto= ptLocator->FindClosestPoint ( p );
    PointType p1=  esferaSimplex->GetPoint ( idPunto );
    if ( repeler )
    {
        if ( p1[0]>=0 )
        {
            p1[0] -= 1;
        }
        else
        {
            p1[0] += 1;
        }
        if ( p1[1] >= 0 )
        {
            p1[1] -= 1;
        }
        else
        {
            p1[1] += 1;
        }
    }
    else
    {
        if ( p1[0] < 0 )
        {
            p1[0] -= 1;
        }
        else
        {
            p1[0] += 1;
        }
        if ( p1[1] < 0 )
        {
            p1[1] -= 1;
        }
        else
        {
            p1[1] += 1;
        }
    }
    esferaSimplex->SetPoint ( idPunto, p1 );
    return conversor.meshToPolydata ( simplexATriangular ( esferaSimplex ) );
}


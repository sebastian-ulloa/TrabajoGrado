#pragma once



class ManejadorGestos
{
public:
    ManejadorGestos();
    ~ManejadorGestos();
    void asignarValores ( float anterior, int completo );
    void asignarValores ( float anterior, float anterior2, int completo );
    float getValorAnterior();
    float getValorAnterior2();// mano izquierda
    int getGestoProgreso();
    int getGestoCompleto();
    void aumentarProgreso();
    void setValorAnterior ( float anterior );
    void setValorAnterior ( float anterior, float anterior2 );
    void reiniciarValores();
private:
    float valorAnterior; // valor anterior de posición o distancia que define el gesto
    float valorAnterior2;// para gestos con dos manos
    int gestoProgreso; // numero del frame en el que el gesto se encuentra
    int gestoCompleto; // numero de frames que determina si el gesto esta completo
    float predeterminado; // valor predeterminado de valorAnterior
    float predeterminado2;
};


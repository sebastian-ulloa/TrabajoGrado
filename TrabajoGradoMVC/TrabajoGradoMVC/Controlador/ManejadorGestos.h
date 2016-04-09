#pragma once



class ManejadorGestos {
public:
    ManejadorGestos();
    ~ManejadorGestos();
    void asignarValores ( float anterior, int actual, int completo );
    float getValorAnterior();
    float getGestoProgreso();
    int getGestoCompleto();
    void aumentarProgreso();
    void setValorAnterior ( float anterior );
    void reiniciarValores();
private:
    float valorAnterior; // valor anterior de posición o distancia que define el gesto
    int gestoProgreso; // numero del frame en el que el gesto se encuentra
    int gestoCompleto; // numero de frames que determina si el gesto esta completo
    float predeterminado; // valor predeterminado de valorAnterior
};


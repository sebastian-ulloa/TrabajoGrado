#pragma once



/** Clase encargarda de administrar el progreso de los gestos.
	Define cuáles deben ser los valores para que se cumpla o no un gesto.
*/
class ManejadorGestos
{
public:
	ManejadorGestos();
	~ManejadorGestos();
	void asignarValores(float anterior, int completo);
	void asignarValores(float anterior, float anterior2, int completo);
	float getValorAnterior();
	float getValorAnterior2();
	int getGestoProgreso();
	int getGestoCompleto();
	void aumentarProgreso();
	void setValorAnterior(float anterior);
	void setValorAnterior(float anterior, float anterior2);
	void reiniciarValores();
private:
	/** valor anterior de posición o distancia que define el gesto. */
	float valorAnterior;
	/** valor anterior de posición2 o distancia2 que define el gesto.
	Variable utilizada para gestos con dos manos */
	float valorAnterior2;
	/** numero del frame en el que el gesto se encuentra. */
	int gestoProgreso;
	/** numero de frames que determina si el gesto esta completo. */
	int gestoCompleto;
	/** valor predeterminado de valorAnterior. */
	float predeterminado;
	/** valor predeterminado de valorAnterior2. */
	float predeterminado2;
};


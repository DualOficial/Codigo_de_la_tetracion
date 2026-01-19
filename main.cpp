#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<complex>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<sstream>
#include"ortogonals.hpp"
#include"ortogonalper.hpp"
#include"ApplicationPlot.hpp"
#include"ApplicationPlotComplex.hpp"
#include"TestFunc.hpp"
#include"permutation.hpp"
#include"other_permutations.hpp"
#include"Language.hpp"
#include"Tetration.hpp"
#include<fstream>

using namespace std;
using namespace std::literals;
using namespace boost::math;

//Tetración: Formula descubierta el 13 de enero en la mañana( como entre las 3am y 4am ), por que dormi tarde.

int main(){
	
	//Codigo de ejemplo para graficar la tetración

	adjust_precision< float50 >();

	tetration_complexity = 72; //Aqui se especifica las iteraciones que usara la tetración
	tetration_recursive = false; //Aqui se quita la recursión por defecto, para mejorar la grafica
	//Advertencia: la tetración no soporta iteraciones muy grandes. Si quiere mas iteraciones, aumente decimales.

	ApplicationPlot app;

	app.set_velocity_time( 10 );
	app.add_bi_func( []( long double x ){ return ( long double ) tet< lcomplex >( 3.l , 1.5l , x ).real(); } , Color::Red );

	app.run();

	return 0;
}

/*
//////////////////////  TUTORIAL DE FUNCIONES Y CLASES DEL PROYECTO //////////////////////

////////////Para mayor precisión

Use float50 y float100 para numeros reales.
Y complex50 junto a complex100 para numeros complejos.
Esto es gracias a boost math y su libreria multiprecision entre otras

Para mejorar los decimales mostrados por el c-out, use adjust_precision seguido con su plantilla,
por ejemplo:
adjust_precision< float50 >(); para usar numeros reales con 50 decimales de precisión
adjust_precision< float100 >(); para usar numeros reales con 100 decimales de precisión

////////////Codigo de Ejemplo para hacer una grafica real de la tetración

adjust_precision< float50 >();

tetration_complexity = 72; //Aqui se especifica las iteraciones que usara la tetración
tetration_recursive = false; //Aqui se quita la recursión por defecto, para mejorar la grafica
//Advertencia: la tetración no soporta iteraciones muy grandes. Si quiere mas iteraciones, aumente decimales.

ApplicationPlot app;

app.set_velocity_time( 10 );
app.add_bi_func( []( long double x ){ return ( long double ) tet< lcomplex >( 3.l , 1.5l , x ).real(); } , Color::Red );

app.run();

////////////Codigo de Ejemplo para hacer una grafica real de la permutación

adjust_precision< float50 >();

permutation_complexity = 1000;

ApplicationPlot app;

app.set_velocity_time( 10 );
app.add_bi_func( []( long double x ){ return ( long double ) per< lcomplex >( 2.l , x ).real(); } , Color::Red );

app.run();

////////////Para graficos
1.Use ApplicationPlot para graficar en un plano curvas.
funciones de esta clase:
a) add_func, esta usela para funciones reales
b) add_func_complex, esta grafica el camino que deja una serie de puntos en plano complejo

2.Use ApplicationPlotComplex para graficar con un shader, un plano de colores
Esto es muy usual en el analisis complejo.

Aqui un ejemplo:

ApplicationPlotComplex app;

app.loadShaderFromFile( "tetration_shader.frag" );

app.run();

Aqui hay una serie de shaders que podria compilar:
1.shader.frag //contiene la permutación
2.other_permutations_shader.frag //contiene las funciones de other_permutation.hpp
3.tetration_shader.frag //contiene la tetración natural y la de euler

////////////Por ultimo
1. TestFunc te sirve para ver como una función progresa
2. ortogonals contiene obviante los numeros ortogonales
3. ortogonalper contiene los ortogonales bajo una perspectiva
basicamente, si no quieres trabajar con z sino con log( z ) use la perspectiva 1,
y si quiere trabajar con log( log( z ) ) use la perspectiva 2, por al contrario-
si usa la perspectiva -1 trabajara con exp( z ) y si usa la perspectiva -2
trabajara con exp( exp( z ) ), y así indefinidamente.

4.dual, esta es una clase que permite usar los numeros duales( xddd como DualMath ).
Sirve para derivadas.

5.other_permutations
contiene varias funciones, parecidas a la permutación, en su forma de creación.
Todas ellas tienen un punto fijo con derivada 1, por lo que se puede usar un teorema de acoplación.
Entre estas estan:
a) minus tetration, basada en e^x-1 repetio
b) plus tetration, basada en e^(x-1) repetido
c) hyper square, basada en 1/2 * x^2 + 1/2 repetido
d) neutral tetration, basada en (e^1/e)^x repetido

6.Language: aunque nada que ver, permite crear un mini lenguaje, por cierto, esta en versión beta
por lo que no es tan util.

7.permutation: contiene la permutación( esperabas mas? )
8.tetration: contiene la tetración;
Por otro lado, también contiene unas clases y funciones.
Estas permiten calcular las derivadas de la tetración en alpha.
(alpha seria el numero que cumple: e^alpha=alpha,
por cierto, hay varios alphas posibles que cumplen esta ecuación )

Aqui un ejemplo de su uso:

adjust_precision< long double >();

lcomplex alpha = alpha_tet< long double >( exp( 1.l ) );

cout<<alpha<<" : "<<0<<endl;

Sum sum;
vector< Formula > formulas;
unsigned int n = 2;

cout<<Compute( Resolve( sum , formulas , alpha ) , 0.5l , alpha )<<" : "<<1<<endl;

while( true ){
	
	formulas.push_back( Simplify( Resolve( sum , formulas , alpha ) ) );

	cout<<Compute( formulas.back() , 0.5l , alpha )<<" : "<<n<<endl;

	sum = Derivate( sum );
	n++;

}

// fin del ejemplo

En este ejemplo, se calcularon las derivadas de la tetración de accelo( exponente de tetración ) 0.5
centradas en un alpha.

Gracias te da Dual por ver el tutorial hasta aqui :)

Mi canal: https://www.youtube.com/@DualMath

*/
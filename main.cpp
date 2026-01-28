#include"MathGraphics.hpp"
#include"Math.hpp"

//Tetración: Formula descubierta el 13 de enero en la mañana( como entre las 3am y 4am ), por que dormi tarde.

int main(){
	
	////////////Codigo de Ejemplo para hacer una grafica real de la tetración

	adjust_precision< long double >();

	tetration_complexity = 72; //Aqui se especifica las iteraciones que usara la tetración
	//Advertencia: la tetración no soporta iteraciones muy grandes. Si quiere mas iteraciones, aumente decimales.

	ApplicationPlot app;

	app.set_velocity_time( 10 );
	app.add_bi_func( []( long double x ){ return tet< lcomplex >( 3.l , 1.5l , x ).real(); } , Color::Red );

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

adjust_precision< long double >();

tetration_complexity = 72; //Aqui se especifica las iteraciones que usara la tetración
//Advertencia: la tetración no soporta iteraciones muy grandes. Si quiere mas iteraciones, aumente decimales.

ApplicationPlot app;

app.set_velocity_time( 10 );
app.add_bi_func( []( long double x ){ return tet< lcomplex >( 3.l , 1.5l , x ).real(); } , Color::Red );

app.run();

////////////Codigo de Ejemplo para hacer una grafica real de la permutación

adjust_precision< long double >();

permutation_complexity = 1000; //La complejidad de la permutación puede ser tan grande como usted quiera.
//Pero sus cambios cada vez seran menores.

ApplicationPlot app;

app.set_velocity_time( 10 );
app.add_bi_func( []( long double x ){ return per< lcomplex >( 2.l , x ).real(); } , Color::Red );

app.run();

////////////Para graficos
1.Use ApplicationPlot para graficar en un plano curvas.
funciones de esta clase:
a) add_func, esta usela para funciones reales
b) add_func_complex, esta grafica el camino que deja una serie de puntos en plano complejo

Para esta grafica, hay una serie de teclas que se pueden usar:
O: maximizar
W: arriba
S: abajo
E: derecha
A: izquierda
Direcciones: moverte( obviamente xD )
D: agrandar entorno al mouse( zoom )
A: empequeñezer entorno al mouse
Hay otras teclas en el codigo pero no sirven para nada aun, como el texto index que siempre es 0.

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

Para esta grafica, hay una serie de teclas que se pueden usar:
Pondre a la derecha de algunas teclas las variables que manipulan en el shader.
Direccionales: para morverte
O: para maximizar
D: para agrandar entorno al mouse( zoom )
A: para empequeñezer entorno al mouse
E: moverte a la derecha, igual que la tecla Right
Q: moverte a la izquierda, igual que la tecla Left
W: moverte arriba, igual que Up
S: moverte abajo, igual que Down
Z: mover para abajo el plano en O1 : "index"
X: mover para arriba el plano en O1 : "index"
C: mover para abajo el plano en O2 : "index2"
V: mover para arriba el plano en O2 : "index2"
B: bajar un indice( puede servir, para aumentar las iteraciones de una función ) : "value"
N: aumentar un indice( el mismo que en B ) : "value"

////////////Por ultimo
1. TestFunc te sirve para ver como una función progresa
2. ortogonals contiene obviante los numeros ortogonales
3. ortogonalper contiene los ortogonales bajo una perspectiva
basicamente, si no quieres trabajar con z sino con log( z ) use la perspectiva -1,
y si quiere trabajar con log( log( z ) ) use la perspectiva -2, por al contrario-
si usa la perspectiva 1 trabajara con exp( z ) y si usa la perspectiva 2
trabajara con exp( exp( z ) ), y así indefinidamente.

4.dual, esta es una clase que permite usar los numeros duales( xddd como DualMath ).
Sirve para derivadas.
Aqui un ejemplo:

adjust_precision< long double >();

ApplicationPlot app;

app.set_velocity_time( 10 );
app.add_bi_func( []( long double x ){
	
	//anader, es una función que calcula la derivada de otra a partir de numeros duales
	//para ello debes meterle una función de duales y un numero de cualquier tipo.

	return anader< long double >( []( ldual a ){ return per< ldual >( 2.l , a ); } , x );
	
} , Color::Blue );
app.run();

Fin del ejemplo.
Este fue un metodo viejo, pero si quieres escribir menos lineas y hace multiples derivadas, puedes usar-
la función derivate que funciona con plantillas; Aqui un ejemplo:

adjust_precision< long double >();

ApplicationPlot app;

auto f = []< typename T >( T x ){ return per( T( 2 ) , x ); };
//Tiene que ser una función plantilla, para soportar varias estructuras.

auto g = derivate< 1 >( f ); //se guarda la derivada de f, en otra función g.

app.set_velocity_time( 10 );
app.add_bi_func( [ & ]( long double x ){
	
	return g( x ); //se grafica la derivada

} , Color::Cyan );

app.run();

return 0;

Fin del ejemplo.
En este ejemplo se hizo la segunda derivada de la permutación base 2.

5.coupling
Este tiene la acoplación( coupling en ingles ) y la ascendiente( ascendant ) que también son funciones plantilla.
Aqui un ejemplo:

adjust_precision< long double >();

ApplicationPlot app;

auto f = []< typename T >( T x ){ return per( T( 2 ) , x ); }; //siempre plantilla
auto g = coupling( f ); //se guarda la acoplación

app.set_velocity_time( 10 );
app.add_bi_func( [ & ]( long double x ){
	
	return g( x ); //se grafica la acoplación
	
} , Color::Cyan );

app.run();

Fin del ejemplo.
Por ultimo, se puede crear la versión permutada de una función, osea, g(x,y)=f(f(..f(x)..)) donde aparece f, y veces.
Aqui un ejemplo:

adjust_precision< long double >();

ApplicationPlot app;

auto f = []< typename T >( T x ){ return pow( x , x ); };
auto fi = []< typename T >( T x ){ return wave( x ); };
auto per = Permuted_Function( f , fi , 1.l , 1.l , 2.l );
//El primer argumento es la función a repetir, el segundo es la inversa, el tercero es el atractor-
//que cumple f(a)=a, el cuarto es la derivada, el quinto es la aceleración y, por ultimo y ya predeterminado-
//como 1000 son las iteraciones.

app.set_velocity_time( 10 );
app.add_bi_func( [ & ]( long double x ){

	return per( 2.l , x );

} , Color::Cyan );

app.run();

Fin del ejemplo.
Aqui se recreo la permutación.

6.other_permutations
contiene varias funciones, parecidas a la permutación, en su forma de creación.
Todas ellas tienen un punto fijo con derivada 1, por lo que se puede usar un teorema de acoplación.
Entre estas estan:
a) minus tetration, basada en e^x-1 repetido
b) plus tetration, basada en e^(x-1) repetido
c) hyper square, basada en 1/2 * x^2 + 1/2 repetido
d) natural tetration, basada en (e^1/e)^x repetido

7.Language: aunque nada que ver, permite crear un mini lenguaje, por cierto, esta en versión beta
por lo que no es tan util.

8.permutation: contiene la permutación( esperabas mas? )
9.tetration: contiene la tetración;
Por otro lado, también contiene unas clases y funciones.
Estas permiten calcular las derivadas de la tetración en alpha.
(alpha seria el numero que cumple: e^alpha=alpha,
por cierto, hay varios alphas posibles que cumplen esta ecuación )

Aqui un ejemplo de su uso:

adjust_precision< long double >();

lcomplex alpha = alpha_tet< lcomplex >( exp( 1.l ) );

cout<<alpha<<" : "<<0<<endl;

Sum sum;
vector< lFormula > formulas;
unsigned int n = 1;

while( true ){
	
	formulas.push_back( Resolve( sum , formulas , alpha ) );

	cout<<Compute< lcomplex >( formulas.back() , 0.5l , alpha )<<" : "<<n<<endl;

	sum = Derivate( sum );
	n++;

}

// fin del ejemplo

En este ejemplo, se calcularon las derivadas de la tetración de accelo( exponente de tetración ) 0.5
centradas en un alpha.

También, si quiere obtener las derivadas de la tetración de cualquier base entorno a su alpha
( si la base es b, su alpha cumple: b^a=a )
entonces, puede usar el siguiente codigo:

adjust_precision< long double >();

lcomplex base = 2.l;
lcomplex alpha = alpha_tet< lcomplex >( base );

cout<<alpha<<" : "<<0<<endl;

Sum sum;
vector< lFormula > formulas;
unsigned int n = 1;

while( true ){
	
	formulas.push_back( Resolve( sum , formulas , base , alpha ) );

	cout<<Compute< lcomplex >( formulas.back() , 0.7l , base , alpha )<<" : "<<n<<endl;

	sum = Derivate( sum );
	n++;

}

// fin del ejemplo

En este ejemplo, se calcularon las derivadas de la tetración base 2 de accelo( exponente de tetración ) 0.7
centradas en un alpha.

Por cierto, cuando hagas un shader, que no se te olvide poner "#ADD ORTOGONAL SHADER" para tener numeros ortogonales,
ortoper( con perspectiva ), entre otras funciones.

Gracias te da Dual por ver el tutorial hasta aqui :)

Mi canal: https://www.youtube.com/@DualMath

*/

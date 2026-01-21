#include"ortogonals.hpp"
#include"ortogonalper.hpp"
#include<iostream>
#include<algorithm>
#include<limits>

template<>
float log( float a , float b ){
	
	return logf( b ) / logf( a );

}

template<>
long double log( long double a , long double b ){
	
	return logl( b ) / logl( a );

}

template<>
int is_sing( fcomplex z ){
	
	if( z == 0.f ) return -1;
	if( z == 1.f ) return 0;
	if( z == 2.71828182845904523536f ) return 1;
	if( z == 15.1542622414792641904f ) return 2;
	if( z == 3814279.1047602205947f ) return 3;
	
	return 4;
}

template<>
int is_sing( dcomplex z ){
	
	if( z == 0.0 ) return -1;
	if( z == 1.0 ) return 0;
	if( z == 2.71828182845904523536 ) return 1;
	if( z == 15.1542622414792641904 ) return 2;
	if( z == 3814279.1047602205947 ) return 3;
	
	return 4;
}

template<>
int is_sing( lcomplex z ){
	
	if( z == 0.l ) return -1;
	if( z == 1.l ) return 0;
	if( z == 2.71828182845904523536l ) return 1;
	if( z == 15.1542622414792641904l ) return 2;
	if( z == 3814279.1047602205947l ) return 3;
	
	return 4;
}

template<>
float value_tetration( int k ){
	
	if( k == -1 ) return 0.f;
	if( k == 0 ) return 1.f;
	if( k == 1 ) return 2.71828182845904523536f;
	if( k == 2 ) return 15.1542622414792641904f;
	if( k == 3 ) return 3814279.1047602205947f;
	if( k > 3 ) return INFINITY;
	
	return -1.f;
}

template<>
double value_tetration( int k ){
	
	if( k == -1 ) return 0.0;
	if( k == 0 ) return 1.0;
	if( k == 1 ) return 2.71828182845904523536;
	if( k == 2 ) return 15.1542622414792641904;
	if( k == 3 ) return 3814279.1047602205947;
	if( k > 3 ) return INFINITY;
	
	return -1.0;
}

template<>
long double value_tetration( int k ){
	
	if( k == -1 ) return 0.l;
	if( k == 0 ) return 1.l;
	if( k == 1 ) return 2.71828182845904523536l;
	if( k == 2 ) return 15.1542622414792641904l;
	if( k == 3 ) return 3814279.1047602205947l;
	if( k > 3 ) return INFINITY;
	
	return -1.l;
}

template<>
float e_tetration_positive( float z , unsigned int n ){
	
	while( n ){
		
		z = expf( z );
		n--;

	}

	return z;
}

template<>
long double e_tetration_positive( long double z , unsigned int n ){
	
	while( n ){
		
		z = expl( z );
		n--;

	}

	return z;
}

template<>
float e_tetration_negative( float z , unsigned int n ){
	
	while( n ){
		
		z = logf( z );
		n--;

	}

	return z;
}

template<>
long double e_tetration_negative( long double z , unsigned int n ){
	
	while( n ){
		
		z = logl( z );
		n--;

	}

	return z;
}

lortogonal operator"" ol( long double x ){
	
	return lortogonal( x );
	
}

lortogonal operator"" oil( long double x ){
	
	return lortogonal( 0.l , x );
	
}

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

ortogonal< long double , lcomplex > operator"" ol( long double x ){
	
	return ortogonal< long double , lcomplex >( x );
	
}

ortogonal< long double , lcomplex > operator"" oil( long double x ){
	
	return ortogonal< long double , lcomplex >( 0.l , x );
	
}

template<>
complex50 wlambert( complex50 z , int k ){
	
	//For some particular z and k W(z,k) has simple value:
	if( z == complex50( 0 ) ) return ( k == 0 ) ? 0.l : -INFINITY;
	if( z == -exp( -complex50( 1 ) ) && ( k == 0 || k == -1 ) ) return -complex50( 1 );
	if( z == exp( complex50( 1 ) ) && k == 0 ) return complex50( 1 );
	
	//Halley method begins
	complex50 w( InitPoint( z , k ) ) , wprev; // intermediate values in the Halley method
	const unsigned int maxiter = 30; // max number of iterations. This eliminates improbable infinite loops
	unsigned int iter = 0; // iteration counter
	auto prec = std::numeric_limits< float50 >::epsilon(); // difference threshold between the last two iteration results (or the iter number of iterations is taken)
	
	do{
		
		wprev = w;
		w -= complex50( 2 ) * ( ( zexpz( w ) - z ) * zexpz_d( w ) ) / ( complex50( 2 ) * pow( zexpz_d( w ) , complex50( 2 ) ) - ( zexpz( w ) - z ) * zexpz_dd( w ) );
		iter++;
		
	} while( ( abs( w - wprev ) > prec ) && iter < maxiter );
	
	return w;
}

template<>
complex100 wlambert( complex100 z , int k ){
	
	//For some particular z and k W(z,k) has simple value:
	if( z == complex100( 0 ) ) return ( k == 0 ) ? 0.l : -INFINITY;
	if( z == -exp( -complex100( 1 ) ) && ( k == 0 || k == -1 ) ) return -complex100( 1 );
	if( z == exp( complex100( 1 ) ) && k == 0 ) return complex100( 1 );
	
	//Halley method begins
	complex100 w( InitPoint( z , k ) ) , wprev; // intermediate values in the Halley method
	const unsigned int maxiter = 30; // max number of iterations. This eliminates improbable infinite loops
	unsigned int iter = 0; // iteration counter
	auto prec = std::numeric_limits< float100 >::epsilon(); // difference threshold between the last two iteration results (or the iter number of iterations is taken)
	
	do{
		
		wprev = w;
		w -= complex100( 2 ) * ( ( zexpz( w ) - z ) * zexpz_d( w ) ) / ( complex100( 2 ) * pow( zexpz_d( w ) , complex100( 2 ) ) - ( zexpz( w ) - z ) * zexpz_dd( w ) );
		iter++;
		
	} while( ( abs( w - wprev ) > prec ) && iter < maxiter );
	
	return w;
}

template<>
complex_single wlambert( complex_single z , int k ){
	
	//For some particular z and k W(z,k) has simple value:
	if( z == complex_single( 0 ) ) return ( k == 0 ) ? 0.l : -INFINITY;
	if( z == -exp( -complex_single( 1 ) ) && ( k == 0 || k == -1 ) ) return -complex_single( 1 );
	if( z == exp( complex_single( 1 ) ) && k == 0 ) return complex_single( 1 );
	
	//Halley method begins
	complex_single w( InitPoint( z , k ) ) , wprev; // intermediate values in the Halley method
	const unsigned int maxiter = 30; // max number of iterations. This eliminates improbable infinite loops
	unsigned int iter = 0; // iteration counter
	auto prec = std::numeric_limits< float_single >::epsilon(); // difference threshold between the last two iteration results (or the iter number of iterations is taken)
	
	do{
		
		wprev = w;
		w -= complex_single( 2 ) * ( ( zexpz( w ) - z ) * zexpz_d( w ) ) / ( complex_single( 2 ) * pow( zexpz_d( w ) , complex_single( 2 ) ) - ( zexpz( w ) - z ) * zexpz_dd( w ) );
		iter++;
		
	} while( ( abs( w - wprev ) > prec ) && iter < maxiter );
	
	return w;
}
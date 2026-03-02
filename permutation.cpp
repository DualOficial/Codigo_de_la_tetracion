#include"permutation.hpp"

//mala calidad

long double lag_per( long double x ){
	
	long double a = exp( 1.l );
	long double sum1 = 0.l;
	long double sum2 = 0.l;
	int n = 30;

	for( int i = 0; i <= n; i++ ){
		
		sum1 += pow( -1.l , i ) * a / ( ( x + i ) * factorial< long double >( i ) * factorial< long double >( n - i ) );
		sum2 += pow( -1.l , i ) / ( ( x + i ) * factorial< long double >( i ) * factorial< long double >( n - i ) );
		a = wave( a );

	}

	return sum1 / sum2;
}
#include"permutation.hpp"

int permutation_complexity = 10000;

//mala calidad

float wlambert( float z ){
	
	if( z < -expf( -1.f ) ){
		
		return std::numeric_limits< float >::quiet_NaN();

	}
	
	return lambert_w0( z );
}

double wlambert( double z ){
	
	if( z < -exp( -1.0 ) ){
		
		return std::numeric_limits< double >::quiet_NaN();

	}
	
	return lambert_w0( z );
}

long double wlambert( long double z ){
	
	if( z < -expl( -1.l ) ){
		
		return std::numeric_limits< long double >::quiet_NaN();

	}
	
	return lambert_w0( z );
}

float50 wlambert( float50 z ){
	
	if( z < -exp( -float50( 1 ) ) ){
		
		return std::numeric_limits< float50 >::quiet_NaN();

	}
	
	return lambert_w0( z );
}

float100 wlambert( float100 z ){
	
	if( z < -exp( -float100( 1 ) ) ){
		
		return std::numeric_limits< float100 >::quiet_NaN();

	}
	
	return lambert_w0( z );
}

float_single wlambert( float_single z ){
	
	if( z < -exp( -float_single( 1 ) ) ){
		
		return std::numeric_limits< float_single >::quiet_NaN();

	}
	
	return lambert_w0( z );
}

long double lag_per( long double x ){
	
	long double a = M_E;
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
template< typename T >
real_type< T > real_value( const T & z ){
	
	return z;

}

template< is_complex T >
real_type< T > real_value( const T & z ){
	
	return z.real();

}

template< typename T >
T csc( const T & z ){
	
	return T( 1 ) / sin( z );

}

template< typename T >
T sec( const T & z ){
	
	return T( 1 ) / cos( z );

}

template< typename T >
T cot( const T & z ){
	
	return cos( z ) / sin( z );

}

template< typename T >
T sign( T z ){
	
	return z / abs( z );

}

template< typename T >
T infinity_proj( T z ){
	
	return sign( z ) * ( atan( sqrt( pow( z / T( 2 ) + T( 1 ) / ( z * T( 2 ) ) , T( 2 ) ) - T( 1 ) ) ) * sign( z * z - T( 1 ) ) + constants::half_pi< long double >() );

}

template< typename T >
T inverse_proj( T z ){
	
	return csc( z ) - cot( z );

}

template< typename T >
bool isnan( const std::complex< T > & z ){
	
	return z.real() == std::numeric_limits< T >::quiet_NaN() || z.imag() == std::numeric_limits< T >::quiet_NaN();

}

template< typename T >
bool isinf( const std::complex< T > & z ){
	
	return z.real() == std::numeric_limits< T >::infinity() || z.real() == -std::numeric_limits< T >::infinity()
	|| z.imag() == std::numeric_limits< T >::infinity() || z.imag() == -std::numeric_limits< T >::infinity();

}

template< typename T >
T log( T base , T x ){
	
	return log( x ) / log( base );

}

template< typename T >
void adjust_precision(){
	
	std::cout<<std::setprecision( std::numeric_limits< T >::max_digits10 );

}

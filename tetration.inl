template< typename T >
std::complex< T > alpha_tet( const std::complex< T > & base ){
	
	if( base == exp( T( 1 ) ) ){
		
		std::complex< T > z = 2;
		std::complex< T > prev_z;

		do{
			
			prev_z = z;
			z = log( z );

		} while( abs( z - prev_z ) > std::numeric_limits< T >::epsilon() );
		
		return z;
	}
	
	std::complex< T > z = ( base == T( 2 ) ? 3 : 2 );
	std::complex< T > prev_z;

	do{
		
		prev_z = z;
		z = log( base , z );

	} while( abs( z - prev_z ) > std::numeric_limits< T >::epsilon() );
	
	return z;
}

template< typename T >
T tet( const T & base , const T & final_exp , T height , const T & v ){
	
	if( tetration_recursive ){
		
		auto half = T( 0.5 ).real();

		if( height.real() < v.real() - half ){
			
			int a = ( int ) floor( height.real() - ( v.real() - half ) );

			height = height - T( a );

			return tetration_integer( base , tet( base , final_exp , height , v ) , a );
		}
		
		if( height.real() > v.real() + half ){
			
			int a = ( int ) floor( height.real() - ( v.real() - half ) );

			height = height - T( a );

			return tetration_integer( base , tet( base , final_exp , height , v ) , a );
		}

	}

	if( base == exp( exp( -T( 1 ) ) ) ) return natural_tet( final_exp , height );

	T a = v - T( 1 );
	T b = tetration_integer( base , final_exp , -tetration_complexity ) - a;
	
	T log_base = ( base == exp( T( 1 ) ) ? 1 : log( base ) );
	T c = v * log_base;
	T d = pow( c , height );
	T x = ( log_base * ( d * d - d ) / ( c - T( 1 ) ) - d * d + d ) / ( d * T( 2 ) );

	return tetration_integer( base , pow( b , d * pow( b , x ) ) + a , tetration_complexity );
}

template< typename T >
T tet( const T & base , const T & final_exp , T height ){
	
	return tet( base , final_exp , height , alpha_tet( base ) );
	
}

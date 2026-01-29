//Funciones Tes o Complejas

template< typename T >
T wave( const T & x ){
	
	return exp( wlambert( log( x ) ) );

}

template< typename T >
T wave( const T & x , const T & base ){
	
	if( base == T( 0 ) ) return x;

	return pow( wave( pow( x , base ) ) , T( 1 ) / T( base ) );
}

//Funciones Ortogonales

template< typename T >
T riz( const T & a , const T & b ){
	
	T log_a = log( a );
	
	return log( log( b ) / log_a ) / log_a;
}

template< typename T >
T asc( const T & a , const T & b ){
	
	T log_a = log( a );

	return exp( log_a * exp( log_a * b ) );
}

template< typename T >
T perInteger( T x , int n ){
	
	if( n < 0 ){
		
		n = -n;
		x = log( x );

		while( n ){
			
			x = wlambert( x );
			n--;

		}

		return exp( x );
	}

	if( n == 0 ) return x;

	x = log( x );

	while( n ){
		
		x = x * exp( x );
		n--;

	}
	
	return exp( x );
}

template< typename T >
T per( T u , T v ){
	
	if( permutation_recursive ){
		
		if( Real( v ) > real_type< T >( 1 ) ){
			
			int a = ( int ) floor( Real( v ) );

			return perInteger( per( u , v - T( a ) ) , a );
		}

		if( Real( v ) < real_type< T >( 0 ) ){
			
			int a = ( int ) floor( Real( v ) );

			return perInteger( per( u , v - T( a ) ) , a );
		}
		
	}
	
	T z( perInteger( u , -permutation_complexity ) );
	T n = asc( z , v );
	
	return perInteger( n , permutation_complexity );
}

template< typename T >
T beta_tetration( T u , T v ){
	
	T result;
	T term = u;
	long double n = 0.l;
	
	while( n < 74 ){
		
		result = e_tetration_positive( pow( term , pow( term / log( term ) , v ) ) , ( unsigned int ) n );
		term = log( term );
		n++;
		
	}
	
	return result;
}

template< typename T >
T beta_tetration( T w ){
	
	T term = e_tetration_negative( 1.01l , 74 );
	
	return e_tetration_positive( pow( term , pow( term / log( term ) , w ) ) , 74 );
}

template< typename T >
T F( T x ){
	
	T log_x = log( x );
	T term1 = x;
	T term2 = 1;
	T term3 = exp( T( 1 ) );
	T prev_result;
	T result = 1;
	int n = 1;
	
	do{
		
		prev_result = result;
		term1 = wave( term1 );
		term2 *= term1;
		term3 = wave( term3 );
		result *= ( 1.l + log_x / term2 ) / term3;
		n++;
		
	} while( abs( result - prev_result ) > std::numeric_limits< long double >::epsilon() && n < permutation_complexity );
	
	return result;
}

template< typename T >
T riz( T x ){
	
	return log( log( x ) );
	
}

template< typename T >
T gen( T x , T y ){
	
	return T( 1 ) / log( perInteger( x , -permutation_complexity ) ) - T( 1 ) / log( perInteger( y , -permutation_complexity ) );

}

template< typename T >
T aproxF( T x ){
	
	T u = 4.91l; //este numero cumple la propiedad F(u)=1

	return riz( x * exp( exp( T( 1 ) ) ) / u );
}

template< typename T >
T aprox_per( T x ){
	
	T u = 4.91l;
	T result = log( u );
	T a = x / T( permutation_complexity );
	
	for( unsigned int i = 0; i < permutation_complexity; i++ ){
		
		result *= exp( a * F( exp( result ) ) );
		
	}

	return exp( result );
}

template< typename T >
T F_derivate( T x ){
	
	T prev_result;
	T result;
	T term1 = wave( lortogonal( x ) );
	T term2 = log( x );
	T term3 = term2 + T( 1 );
	unsigned int k = 1;
	
	do{
		
		prev_result = result;
		result += term2 / ( ( term2 + T( 1 ) ) * term3 );
		term1 = wave( T( term1 ) );
		term2 = log( term1 );
		term3 *= term2 + T( 1 );
		k++;
		
	} while( abs( result - prev_result ) > std::numeric_limits< T >::epsilon() && k < permutation_complexity );

	return result;
}

template< typename T >
T perfact_integer( T x , int n ){
	
	if( n >= 0 ){
		
		for( unsigned int i = 1; i <= n; i++ ){
			
			x = asc( x , T( i ) );
			
		}

		return x;
	}

	n = -n;
	
	for( unsigned int i = 0; i < n; i++ ){
		
		x = wave( x , -T( i ) );
		
	}

	return x;
}

template< typename T >
T perfact( const T & x , const T & y ){
	
	T a = perfact_integer( x , -perfact_complexity );
	T mean = ( y + T( 1 ) ) * T( 0.5 );
	
	a = pow( per( pow( a , -T( perfact_complexity ) + mean ) , y ) , T( 1 ) / ( -T( perfact_complexity ) + mean ) );
	
	for( int i = 1; i <= perfact_complexity; i++ ){
		
		a = asc( a , y + T( i - perfact_complexity ) );
		
	}

	return a;
}

template< typename T , typename F >
T sum( F f , T a , T b ){
	
	T result = 0;

	if( a > b ){
		
		a--;
		
		while( a > b ){
			
			result -= f( a );

			a--;
		}

		return result;
	}

	while( a <= b ){
		
		result += f( a );

		a++;
	}

	return result;
}

template< typename T , typename F >
T product( F f , T a , T b ){
	
	T result = 1;

	if( a > b ){
		
		a--;
		
		while( a > b ){
			
			result /= f( a );

			a--;
		}

		return result;
	}

	while( a <= b ){
		
		result *= f( a );

		a++;
	}

	return result;
}

template< typename T , typename F >
T epsilon( F f , T x , T a , T b ){
	
	if( a > b ){
		
		a--;
		
		while( a > b ){
			
			x = wave( x , f( a ) );

			a--;
		}

		return x;
	}

	while( a <= b ){
		
		x = asc( x , f( a ) );

		a++;
	}

	return x;
}

template< typename T , typename F >
T sum_integral( F f , const T & a , const T & b , int complexity ){
	
	T result = 0;
	T y = ( b - a ) / T( complexity );

	for( unsigned int i = 0; i < complexity; i++ ){
		
		result += f( a + y * T( i ) ) * y;

	}

	return result;
}

template< typename T , typename F >
T product_integral( F f , const T & a , const T & b , int complexity ){
	
	T result = 1;
	T y = ( b - a ) / T( complexity );

	for( unsigned int i = 0; i < complexity; i++ ){
		
		result *= pow( f( a + y * T( i ) ) , y );

	}

	return result;
}

template< typename T , typename F >
T epsilon_integral( F f , T x , const T & a , const T & b , int complexity ){
	
	T y = ( b - a ) / T( complexity );

	for( unsigned int i = 0; i < complexity; i++ ){
		
		x = asc( x , f( a + y * T( i ) ) * y );

	}

	return x;
}

template< typename F >
auto product_derivate( F f ){
	
	auto g = derivate( f );

	return [ g = forward< decltype( g ) >( g ) ]< typename T >( T x ){
		
		return exp( g( log( x ) ) );
		
	};
}

template< typename F >
auto epsilon_derivate( F f ){
	
	auto g = derivate( f );

	return [ f = forward< F >( f ) , g = forward< decltype( g ) >( g ) ]< typename T >( T x ){
		
		T y = f( x );
		T z = log( y );

		return g( x ) / ( y * z * z );
	};
}

template< typename T >
T delta_poly_div_factorial( T n , unsigned int k , unsigned int s ){
	
	T sum = 0;
	T term = 1;

	for( unsigned int m = 0; m <= k - s; m++ ){
		
		sum += term * binomial_coefficient< T >( k , m ) * stirling2< T >( k - m , s );
		term *= n;

	}

	return sum;
}

template< typename T >
T delta_poly( T n , unsigned int k , unsigned int s ){
	
	return delta_poly_div_factorial( n , k , s ) * factorial< T >( s );

}

template< typename T >
T uribe( T x , T n , unsigned int k ){
	
	T sum = 0;
	T term = 1;

	for( unsigned int s = 0; s <= k; s++ ){
		
		sum += delta_poly_div_factorial< T >( n , k , s ) * term;
		term *= -x;

	}

	return sum;
}

template< typename T >
T uribe( T x , unsigned int n , unsigned int k ){
	
	return uribe( x , T( n ) , k );

}

template< typename T >
T sum_delta_stirling( T n , unsigned int k , unsigned int s ){
	
	T sum = 0;
	T term = factorial< T >( s );

	for( unsigned int m = 0; m <= k - s; m++ ){
		
		sum += term * binomial_coefficient< T >( k , m + s ) * stirling_sign< T >( k , m + s );
		term *= n * ( m + 1 + s );

	}

	return sum;
}

template< typename T >
T uribe_coefficient( unsigned int k , unsigned int m , unsigned int s ){
	
	T sum = 0;

	for( unsigned int t = m + s; t <= k; t++ ){
		
		sum += binomial_coefficient< T >( t , m ) * stirling2< T >( t - m , s ) * stirling_sign< T >( k , t );

	}

	return sum;
}

template< typename T >
T uribe2( T x , T n , unsigned int k ){
	
	T sum = 0;
	T term = 1;
	T sum2;
	T term2;

	for( unsigned int s = 0; s <= k; s++ ){
		
		sum2 = 0;
		term2 = 1;

		for( unsigned int m = 0; m <= k - s; m++ ){
			
			sum2 += term2 * uribe_coefficient< T >( k , m , s );
			term2 *= n;

		}

		sum += sum2 * term;
		term *= -x;

	}

	return sum;
}

template< typename T >
T uribe2( T x , unsigned int n , unsigned int k ){
	
	return uribe2( x , T( n ) , k );

}

template< typename T >
T phi( T x , unsigned int n ){
	
	return bernoulli< T >( T( n ) - x );

}

template< typename F >
auto phi_operator( F && f , unsigned int complexity ){
	
	auto g = [ f = forward< F >( f ) , N = forward< unsigned int >( complexity ) ]< typename T >( T x ){
		
		return PolyTransform( f , phi< T > , x , T( 1 ) , N );

	};
	
	return g;
}

template< typename F >
auto extensión( F && f , unsigned int complexity ){
	
	auto g = [ f = forward< F >( f ) , N = forward< unsigned int >( complexity ) ]< typename T >( T x ){
		
		return sum_integral( phi_operator( f , N ) , T() , x );

	};

	return g;
}

template< typename F >
auto Near( F && f , unsigned int complexity ){
	
	auto g = [ f = forward< F >( f ) , N = forward< unsigned int >( complexity ) ]
	< typename T , typename U >( T x , U k ){
		
		T s = 0;
		T term = 1;

		for( unsigned int n = 0; n <= N; ){
			
			s += pow( n , k ) / term * f( x , n );

			n++;
			term *= n;

		}

		return s * exp( -x );
	};

	return g;
}

template< typename F >
auto mello( F && f , unsigned int complexity ){
	
	auto g = [ f = forward< F >( f ) , N = forward< unsigned int >( complexity ) ]
	< typename T , typename U >( T M , U k ){
		
		T s = 0;
		T term = 1;

		for( unsigned int n = 0; n <= N; ){
			
			s += pow( n , k ) / term * f( M , n ) * pow( M , n );

			n++;
			term *= n;

		}

		return s * exp( -M ) / pow( M , k );
	};

	return g;
}

template< typename F , typename G , typename T >
T PolyTransform( F && f , G && t , T a , T b , unsigned int complexity ){
	
	T s = 0;
	T term = 1;
	T M = T( complexity );

	for( int n = 0; n <= complexity * 2; ){
		
		s += f( a + b * T( n ) / M ) * pow( M , n ) * t( M , n ) / term;

		n++;
		term *= n;

	}

	return s * exp( -M );
}
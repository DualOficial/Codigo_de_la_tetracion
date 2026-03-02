#include<map>

template< typename T >
T dpow( T x , T n ){
	
	return gamma( x + T( 1 ) ) / gamma< T >( x - n + T( 1 ) );
	
}

template< typename T >
T dpow( T x , unsigned int n ){
	
	T a = 1;

	for( unsigned int k = 0; k < n; k++ ){
		
		a *= x - k;

	}

	return a;
}

template< typename T >
T apow( T x , T n ){
	
	return gamma( x + n + T( 1 ) ) / gamma< T >( x + T( 1 ) );
	
}

template< typename T >
T apow( T x , unsigned int n ){
	
	T a = 1;

	for( unsigned int k = 0; k < n; k++ ){
		
		a *= x + k;

	}

	return a;
}

template< typename T >
T stieltjes( unsigned int n ){
	
	static vector< T > stieltjes_coefficients = vector< T >();

	if( stieltjes_coefficients.empty() ){
		
		stieltjes_coefficients.resize( stieltjes100.size() );

		auto i = stieltjes100.begin();

		for( T & x : stieltjes_coefficients ){
			
			x = T( float100( *i ) );

			i++;
		}

	}
	
	return stieltjes_coefficients[ n ];
}

template< typename T >
T stirling( unsigned int n , unsigned int k ){
	
	static vector< map< unsigned int , T > > stirling_coefficients = vector< map< unsigned int , T > >();

	if( n < stirling_coefficients.size() ){
		
		if( k < stirling_coefficients[ n ].size() ){
			
			return stirling_coefficients[ n ][ k ];

		}

		if( k > n ) return T();
		if( k == 0 ) return T();

		T a = stirling< T >( n - 1 , k - 1 ) + ( n - 1 ) * stirling< T >( n - 1 , k );
		
		stirling_coefficients[ n ].insert( make_pair( k , a ) );

		return a;
	}

	if( n == 0 ){
		
		stirling_coefficients.push_back( { make_pair( 0 , T( 1 ) ) } );

		return k == 0 ? T( 1 ) : T();
	}

	T a = stirling< T >( n - 1 , k - 1 ) + ( n - 1 ) * stirling< T >( n - 1 , k );
	
	stirling_coefficients.push_back( map< unsigned int , T >() );
	stirling_coefficients.back().insert( make_pair( k , a ) );

	return a;
}

template< typename T >
T stirling2( unsigned int n , unsigned int k ){
	
	static vector< map< unsigned int , T > > stirling2_coefficients = vector< map< unsigned int , T > >();

	if( n < stirling2_coefficients.size() ){
		
		if( k < stirling2_coefficients[ n ].size() ){
			
			return stirling2_coefficients[ n ][ k ];

		}

		if( k > n ) return T();

		T a = stirling2< T >( n - 1 , k - 1 ) + k * stirling2< T >( n - 1 , k );
		
		stirling2_coefficients[ n ].insert( make_pair( k , a ) );

		return a;
	}

	if( n == 0 ){
		
		stirling2_coefficients.push_back( { make_pair( 0 , T( 1 ) ) } );

		return k == 0 ? T( 1 ) : T();
	}

	T a = stirling2< T >( n - 1 , k - 1 ) + ( n - 1 ) * stirling2< T >( n - 1 , k );
	
	stirling2_coefficients.push_back( map< unsigned int , T >() );
	stirling2_coefficients.back().insert( make_pair( k , a ) );

	return a;
}

template< typename T >
T stirling_sign( unsigned int n , unsigned int k ){
	
	return stirling< T >( n , k ) * powm1( n + k );

}

template< typename T >
T bernoulli( unsigned int n ){
	
	static vector< T > bernoulli_coefficients = vector< T >();
	
	if( n < bernoulli_coefficients.size() ) return bernoulli_coefficients[ n ];
	if( n % 2 == 1 && n > 1 ){
		
		bernoulli_coefficients.push_back( T() );

		return bernoulli_coefficients.back();
	}

	T sum = 0;
	
	for( unsigned int k = 0; k < n; k++ ){
		
		sum += bernoulli< T >( k ) * binomial_coefficient< T >( n + 1 , k );

	}

	bernoulli_coefficients.push_back( T( 1 ) - sum / T( n + 1 ) );

	return bernoulli_coefficients.back();
}

template< typename T >
T bernoulli2( unsigned int n ){
	
	return n == 1 ? T( -0.5 ) : bernoulli< T >( n );

}

template< typename T >
T bell( unsigned int n ){
	
	static vector< T > bell_coefficients = { T( 1 ) };
	
	if( n < bell_coefficients.size() ) return bell_coefficients[ n ];

	T sum = 0;
	
	for( unsigned int k = 0; k < n; k++ ){
		
		sum += bell< T >( k ) * binomial_coefficient< T >( n - 1 , k );

	}

	bell_coefficients.push_back( sum );

	return bell_coefficients.back();
}

template< typename T >
T bernoulli( unsigned int n , T x ){

	T sum = 0;
	T term = 1;

	for( unsigned int k = 0; k <= n; k++ ){
		
		sum += term * binomial_coefficient< T >( n , k ) * bernoulli< T >( n - k );
		term *= x;

	}

	return sum;
}

template< typename T >
T bernoulli( T x ){
	
	return x == T() ? T( 1 ) : -x * zeta( 1.l - x );

}

template< typename T >
T touchard( unsigned int n , T x ){
	
	T sum = 0;
	T term = 1;

	for( unsigned int k = 0; k <= n; k++ ){
		
		sum += term * stirling2< T >( n , k );
		term *= x;

	}

	return sum;
}

//extensión x^n = Sn(x), Sn es un polinomio de grado n

template< typename T >
T S( unsigned int n , T x ){
	
	return ( bernoulli( n + 1 , x ) - bernoulli< T >( n + 1 ) ) / T( n + 1 );

}
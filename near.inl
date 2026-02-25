template< typename F >
auto Near( F && f , unsigned int complexity ){
	
	auto g = [ f = forward< F >( f ) , N = forward< unsigned int >( complexity ) ]
	< typename T >( T x , unsigned int k ){
		
		T s = 0;
		T term = 1;

		for( unsigned int n = 0; n <= N; ){
			
			s += pow( n , k ) / term * f( x , n );

			n++;
			term *= n;

		}

		return exp( -x ) * s;
	};

	return g;
}

template< typename F , typename G >
auto PolyTransform( F && f , G && t , unsigned int complexity ){
	
	auto g = [ f = forward< F >( f ) , t = forward< G >( t ) , N = forward< unsigned int >( complexity ) ]
	< typename T >( T x ){
		
		T s = 0;
		T term = 1;

		for( int n = 0; n <= N; ){
			
			s += f( x + T( n * 2 ) / T( N ) ) * t( T( N / 2 ) , n ) / term;

			n++;
			term *= n;

		}

		return s;
	};
	
	return g;
}
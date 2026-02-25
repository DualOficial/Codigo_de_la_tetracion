template< typename T >
T stirling( unsigned int n , unsigned int k ){
	
	if( n == 0 ) return k == 0 ? 1 : 0;
	if( k == 0 ) return 0;

	return stirling< T >( n - 1 , k - 1 ) + ( n - 1 ) * stirling< T >( n - 1 , k );
}

template< typename T >
T stirling2( unsigned int n , unsigned int k ){
	
	if( n == 0 ) return k == 0 ? 1 : 0;
	if( k == 0 ) return 0;

	return stirling2< T >( n - 1 , k - 1 ) + k * stirling2< T >( n - 1 , k );
}

template< typename T >
T stirlinng_sign( unsigned int n , unsigned int k ){
	
	return ( n + k ) % 2 == 0 ? stirling< T >( n , k ) : -stirling< T >( n , k );

}

template< typename T >
T bernoulli( unsigned int n ){
	
	T sum = 0;
	
	for( unsigned int k = 0; k < n; k++ ){
		
		sum += bernoulli< T >( k ) * binomial_coefficient< T >( n + 1 , k );

	}

	return T( 1 ) - sum / T( n + 1 );
}

template< typename T >
T bell( unsigned int n ){
	
	if( n == 0 ) return T( 1 );
	
	T sum = 0;

	for( unsigned int k = 0; k < n; k++ ){
		
		sum += bell< T >( k ) * binomial_coefficient< T >( n - 1 , k );

	}

	return sum;
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
T touchard( unsigned int n , T x ){
	
	T sum = 0;
	T term = 1;

	for( unsigned int k = 0; k <= n; k++ ){
		
		sum += term * stirling2< T >( n , k );
		term *= x;

	}

	return sum;
}

//extension x^n = Sn(x), Sn es un polinomio de grado n

template< typename T >
T S( unsigned int n , T x ){
	
	return ( bernoulli( n + 1 , x ) - bernoulli< T >( n + 1 ) ) / T( n + 1 );

}
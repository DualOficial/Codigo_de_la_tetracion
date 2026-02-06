template< typename T >
T zexpz( T z ){
	
	return z * exp( z );
	
}

template< typename T >
T zexpz_d( T z ){
	
	return exp( z ) + z * exp( z );
	
}

template< typename T >
T zexpz_dd( T z ){
	
	return exp( z ) * T( 2 ) + z * exp( z );
	
}

template< typename T >
T InitPoint(T z, int k){
	
	T I( 0 , 1 );
	T two_pi_k_I = T( k ) * T( 3.141592653589793238462643383279502884l * 2.l ) * I;
	T ip( log(z) + two_pi_k_I - log( log( z ) + two_pi_k_I ) );// initial point coming from the general asymptotic approximation
	T p( sqrt( T( 2 ) * ( exp( T( 1 ) ) * z + T( 1 ) ) ) );// used when we are close to the branch cut around zero and when k=0,-1
	
	//we are close to the branch cut, the initial point must be chosen carefully
	if( k == 0 && abs( z - exp( -T( 1 ) ) ) <= real_type< T >( 1 ) ){
		
		if( k == 0 ) ip = -T( 1 ) + p - T( 1 ) / T( 3 ) * ( p * p ) + T( 11 ) / T( 72 ) * ( p * p * p );
		if( k == 1 && z.imag() < T( 0 ).real() ) ip = -T( 1 ) - p - T( 1 ) / T( 3 ) * ( p * p ) - T( 11 ) / T( 72 ) * ( p * p * p );
		if( k == -1 && z.imag() > T( 0 ).real() ) ip = -T( 1 ) - p - T( 1 ) / T( 3 ) * ( p * p ) - T( 11 ) / T( 72 ) * ( p * p * p );
		
	}
	
	if( k == 0 && abs(z - T( 0.5 )) <= real_type< T >( 0.5 ) ){
		
		// (1,1) Pade approximant for W(0,a)
		ip = ( T( 0.35173371l ) * ( T( 0.1237166l ) + T( 7.061302897l ) * z ) ) / ( T( 2 ) + T( 0.827184l ) * ( T( 1 ) + T( 2 ) * z ) );
		
	}
	
	if( k == -1 && abs( z - T( 0.5 ) ) <= real_type< T >( 0.5 ) ){
		
		// (1,1) Pade approximant for W(-1,a)
		ip = -( ( ( T( 2.2591588985l ) +
		T( 4.22096l ) * I ) * ( ( -T( 14.073271l ) - T( 33.767687754l ) * I ) * z - ( T( 12.7127l ) -
		T( 19.071643l ) * I ) * ( T( 1 ) + T( 2 ) * z ) ) ) / ( T( 2 ) - ( T( 17.23103l ) - T( 10.629721l ) * I ) * ( T( 1 ) + T( 2 ) * z ) ) );
		
	}

	return ip;
}

//Creditos por W de Lambert a https://github.com/IstvanMezo/LambertW-function

template< no_number_dual T >
T wlambert( T z , int k ){
	
	//For some particular z and k W(z,k) has simple value:
	if( z == T( 0 ) ) return ( k == 0 ) ? 0.l : -std::numeric_limits< real_type< T > >::infinity();
	if( z == -exp( -T( 1 ) ) && ( k == 0 || k == -1 ) ) return -T( 1 );
	if( z == exp( T( 1 ) ) && k == 0 ) return T( 1 );
	
	//Halley method begins
	T w( InitPoint( z , k ) ) , wprev; // intermediate values in the Halley method
	const unsigned int maxiter = wlambert_complexity; // max number of iterations. This eliminates improbable infinite loops
	unsigned int iter = 0; // iteration counter
	
	do{
		
		wprev = w;
		w -= T( 2 ) * ( ( zexpz( w ) - z ) * zexpz_d( w ) ) / ( T( 2 ) * pow( zexpz_d( w ) , T( 2 ) ) - ( zexpz( w ) - z ) * zexpz_dd( w ) );
		iter++;
		
	} while( abs( w - wprev ) > std::numeric_limits< real_type< T > >::epsilon() && iter < maxiter );
	
	return w;
}
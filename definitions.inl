template< typename T >
T log( T base , T x ){
	
	return log( x ) / log( base );

}

template< typename T >
void adjust_precision(){
	
	std::cout<<std::setprecision( std::numeric_limits< T >::max_digits10 );

}
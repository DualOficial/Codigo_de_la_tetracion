namespace math{
	
	template< typename T >
	T square( const T & x ){
		
		return x * x;
		
	}
	
	template< typename T >
	T cube( const T & x ){
		
		return x * x * x;
		
	}
	
	template< typename T >
	std::complex< T > base_quiet_NaN( const std::complex< T > & x ){
		
		return std::complex< T >( base_quiet_NaN( T() ) , base_quiet_NaN( T() ) );
		
	}
	
	template< typename T >
	dual< T > base_quiet_NaN( const dual< T > & x ){
		
		return dual< T >( base_quiet_NaN( T() ) , base_quiet_NaN( T() ) );
		
	}
	
	template< typename T >
	T quiet_NaN(){
		
		return base_quiet_NaN( T() );
		
	}
	
}

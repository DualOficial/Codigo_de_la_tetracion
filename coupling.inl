#include"coupling.hpp"

template< typename T >
T coupling( const function< Dual_Struct< T >( Dual_Struct< T > , unsigned int index ) > & f , const T & x ){
	
	T derivate_1 = derivate< T >( [ f ]( Dual_Struct< T > a ){ return f( a , 1 ); } , x , 1 );

	return derivate< T >( [ f ]( Dual_Struct< T > a ){ return f( a , 2 ); } , x , 2 ) / 
	( derivate_1 * derivate_1 * T( 2 ) );

}

template< typename T >
T ascendant( const function< Dual_Struct< T >( Dual_Struct< T > , unsigned int index ) > & f , const T & x ){
	
	T derivate_1 = derivate< T >( [ f ]( Dual_Struct< T > a ){ return f( a , 1 ); } , x , 1 );

	return ( derivate< T >( [ f ]( Dual_Struct< T > a ){ return f( a , 2 ); } , x , 2 ) / 
	derivate_1 - derivate_1 + T( 1 ) ) * T( 0.5 );

}

template< typename T >
function< T( T , unsigned int ) > to_recursive( const function< T( T ) > & f ){
	
	function< T( T , unsigned int ) > g = [ f ]( T x , unsigned int index ){
		
		while( index ){
			
			x = f( x );
			index--;

		}

		return x;
	};

	return g;
}

template< typename T >
function< T( T , int ) > to_recursive( const function< T( T ) > & f , const function< T( T ) > & inverse_f ){
	
	function< T( T , int ) > g = [ f , inverse_f ]( T x , int index ){
		
		if( index >= 0 ){
			
			while( index ){
				
				x = f( x );
				index--;

			}

			return x;
		}

		index = -index;

		while( index ){
			
			x = inverse_f( x );
			index--;

		}

		return x;
	};

	return g;
}

template< typename T >
template< typename F1 , typename F2 >
Permuted_Function< T >::Permuted_Function( const F1 & g , const F2 & inverse_g , const T & attractor , const T & d , const T & a , unsigned int iterations ){
	
	attract_point = attractor;
	complexity = iterations;
	generator = g;
	generator_inverse = inverse_g;
	derivate1 = d;
	acceleration = a;

	if( d == T( 1 ) ){
		
		f = [ & ]( T x , T y ){
			
			unsigned int n = complexity;

			while( n ){
				
				x = generator_inverse( x );
				n--;

			}

			T derivate_y = pow( d , y );
			
			x = asc( x - attract_point + T( 1 ) , y / ( acceleration * T( 2 ) ) ) + attract_point - T( 1 );

			n = complexity;

			while( n ){
			
				x = generator( x );
				n--;

			}

			return x;
		};

	}
	else{
		
		f = [ & ]( T x , T y ){
			
			unsigned int n = iterations;

			while( n ){
				
				x = generator_inverse( x );
				n--;

			}

			T derivate_y = pow( d , y );
			
			x = pow( x - attract_point + T( 1 ) , derivate_y * pow( x - attract_point + T( 1 ) ,
			( ( derivate_y - T( 1 ) ) / ( derivate1 - T( 1 ) ) * acceleration / derivate1 - derivate_y + T( 1.0 ) ) * T( 0.5 ) ) ) + attract_point - T( 1 );

			n = iterations;

			while( n ){
			
				x = generator( x );
				n--;

			}

			return x;
		};

	}

}

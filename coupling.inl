template< typename F >
auto coupling( F && f ){
	
	return [ f = forward< F >( f ) ]( auto && v ) -> decltype( auto ){
		
		using T = std::decay_t< decltype( v ) >;

		T d = derivate< 1 >( f )( v );

		return derivate< 2 >( f )( v ) / ( d * d * T( 2 ) );
	};

}

template< typename F >
auto ascendant( F && f ){
	
	return [ f = std::forward< F >( f ) ]( auto && v ) -> decltype( auto ){
		
		using T = std::decay_t< decltype( v ) >;

		T d = derivate< 1 >( f )( v );

		return ( derivate< 2 >( f )( v ) / d - d + T( 1 ) ) * T( 0.5 );
	};

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

template< typename T , typename F >
T get_attractor( F && f , T test ){
	
	T before_test;

	do{
		
		before_test = test;
		test = f( test );

	} while( abs( test - before_test ) > std::numeric_limits< real_type< T > >::epsilon() );

	return test;
}

template< typename T , typename F >
T get_attractor( F && f , T test , unsigned int max_iteration ){
	
	T before_test;
	unsigned int i = 0;

	do{
		
		before_test = test;
		test = f( test );
		i++;

	} while( abs( test - before_test ) > std::numeric_limits< real_type< T > >::epsilon() && i < max_iteration );

	return test;
}

template< typename T , typename F >
T get_attractor_l( F && f , T test , real_type< T > epsilon ){
	
	T before_test;

	do{
		
		before_test = test;
		test = f( test );

	} while( abs( test - before_test ) > epsilon );

	return test;
}

template< typename T , typename F >
T get_attractor_l( F && f , T test , real_type< T > epsilon , unsigned int max_iteration ){
	
	T before_test;
	unsigned int i = 0;

	do{
		
		before_test = test;
		test = f( test );
		i++;

	} while( abs( test - before_test ) > epsilon && i < max_iteration );

	return test;
}

template< typename U , typename V , typename T >
Permuted_Function< U , V , T >::Permuted_Function( U g , V inverse_g , const T & attractor , const T & d , const T & a , unsigned int iterations ){
	
	attract_point = attractor;
	complexity = iterations;
	generator = g;
	generator_inverse = inverse_g;
	derivate1 = d;
	acceleration = a;

}

template< typename U , typename V , typename T >
Permuted_Function< U , V , T >::Permuted_Function( U g , V inverse_g , const T & attractor , unsigned int iterations ) :
Permuted_Function( g , inverse_g , attractor , derivate< 1 >( g )( attractor ) , derivate< 2 >( g )( attractor ) , iterations ){
	
	//nothing

}

template< typename U , typename V , typename T >
template< typename S >
S Permuted_Function< U , V , T >::operator()( S x , const S & y ) const{
	
	if( derivate1 == T( 1 ) ){

		unsigned int n = complexity;

		while( n ){
			
			x = generator_inverse( x );
			n--;

		}

		S derivate_y = pow( S( derivate1 ) , y );
		
		x = asc( x - S( attract_point ) + S( 1 ) , S( acceleration ) * y / S( 2 ) ) + S( attract_point ) - S( 1 );

		n = complexity;

		while( n ){
		
			x = generator( x );
			n--;

		}

		return x;
	}

	unsigned int n = complexity;

	while( n ){
		
		x = generator_inverse( x );
		n--;

	}

	S derivate_y = pow( S( derivate1 ) , y );

	x += S( 1 ) - S( attract_point );
	x = pow( x , derivate_y * pow( x , ( ( derivate_y - S( 1 ) ) / ( S( derivate1 ) - S( 1 ) )
	* S( acceleration ) / S( derivate1 ) - derivate_y + S( 1.0 ) ) * S( 0.5 ) ) ) + S( attract_point ) - S( 1 );

	n = complexity;

	while( n ){
	
		x = generator( x );
		n--;

	}

	return x;
}

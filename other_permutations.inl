//tetration permutation

template< typename T >
T expm( T x ){
	
	return exp( x ) - T( 1 );

}

template< typename T >
T logm( T x ){
	
	return log( x + T( 1 ) );

}

template< typename T >
T expp( T x ){
	
	return exp( x - T( 1 ) );

}

template< typename T >
T logp( T x ){
	
	return log( x ) + T( 1 );

}

template< typename T >
T mtetration_integer( T x , int n ){
	
	if( n >= 0 ){
		
		while( n ){
			
			x = expm( x );

			n--;
		}

		return x;
	}

	n = -n;

	while( n ){
		
		x = logm( x );

		n--;
	}

	return x;
}

template< typename T >
T ptetration_integer( T x , int n ){
	
	if( n >= 0 ){
		
		while( n ){
			
			x = expp( x );

			n--;
		}

		return x;
	}

	n = -n;

	while( n ){
		
		x = logp( x );

		n--;
	}

	return x;
}

template< typename T >
T mtetration( T x , T y ){
	
	T a = mtetration_integer( x , -minus_tetration_complexity );
	
	return mtetration_integer( asc( a + T( 1 ) , y / T( 2 ) ) - T( 1 ) , minus_tetration_complexity );
}

template< typename T >
T ptetration( T x , T y ){
	
	T a = ptetration_integer( x , -plus_tetration_complexity );
	
	return ptetration_integer( asc( a , y / T( 2 ) ) , plus_tetration_complexity );
}

//special squaare permutation

template< typename T >
T special_square( T x ){
	
	return x * x * T( 0.5 ) + T( 0.5 );

}

template< typename T >
T invert_square( T x ){
	
	return sqrt( x * T( 2 ) - T( 1 ) );

}

template< typename T >
T hypersquare_integer( T x , int n ){
	
	if( n >= 0 ){
		
		while( n > 0 ){
			
			x = special_square( x );
			n--;

		}

		return x;
	}

	n = -n;

	while( n > 0 ){
		
		x = invert_square( x );
		n--;

	}

	return x;
}

template< typename T >
T hypersquare( T x , T y ){
	
	T a = hypersquare_integer( x , -hyper_square_complexity );

	return hypersquare_integer( pow( a , pow( a , y / T( 2 ) ) ) , hyper_square_complexity );
}

//real tetration base e^1/e

template< typename T >
T tetration_integer( T base , T final_exp , int height ){
	
	if( height >= 0 ){
		
		while( height > 0 ){
			
			final_exp = pow( base , final_exp );

			height--;
		}

		return final_exp;
	}
	
	height = -height;

	while( height > 0 ){
		
		final_exp = log( base , final_exp );

		height--;
	}

	return final_exp;
}

template< typename T >
T natural_tetration_integer( T final_exp , int height ){
	
	if( height >= 0 ){
		
		while( height > 0 ){
			
			final_exp = exp( final_exp / exp( T( 1 ) ) );

			height--;
		}

		return final_exp;
	}
	
	height = -height;

	while( height > 0 ){
		
		final_exp = log( final_exp ) * exp( T( 1 ) );

		height--;
	}

	return final_exp;
}

template< typename T >
T natural_tet( T x , T y ){
	
	T a = natural_tetration_integer( x , -natural_tetration_complexity );

	return natural_tetration_integer( asc( a - exp( T( 1 ) ) + T( 1 ) , y / ( exp( T( 1 ) ) * T( 2 ) ) ) - T( 1 ) + exp( T( 1 ) ) , natural_tetration_complexity );
}

template< typename T >
T natural_gen( T x , T y ){
	
	return exp( T( 1 ) ) * T( 2 ) * ( T( 1 ) / ( natural_tetration_integer( x , -natural_tetration_complexity ) - exp( T( 1 ) ) ) - T( 1 ) / ( natural_tetration_integer( y , -natural_tetration_complexity ) - exp( T( 1 ) ) ) );

}
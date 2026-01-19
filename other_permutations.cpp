#include"other_permutations.hpp"
#include"permutation.hpp"

int plus_tetration_complexity = 10000;
int minus_tetration_complexity = 10000;
int hyper_square_complexity = 10000;
int natural_tetration_complexity = 10000;

lortogonal iterated_function( lortogonal( *f )( lortogonal w ) , unsigned int repetion , lortogonal w ){
	
	while( repetion > 0 ){
		
		w = f( w );
		repetion--;
	}

	return w;
}

orto_function create_permutation( lortogonal ( *f )( lortogonal w ) , lortogonal ( *f_inverse )( lortogonal w ) , long double accoplation ){
	
	return [ f , f_inverse , accoplation ]( lortogonal a , lortogonal b ){
		
		lortogonal x = iterated_function( f , 10000 , a );

		return iterated_function( f_inverse , 10000 , asc( x , b * accoplation ) );
	};

}
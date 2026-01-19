#include"tetration.hpp"

int tetration_complexity = 20;
bool tetration_recursive = true;

complex_single alpha_tet( const complex_single & base ){
	
	if( base == exp( complex_single( 1 ) ) ){
		
		complex_single z = 2;
		complex_single prev_z;

		do{
			
			prev_z = z;
			z = log( z );

		} while( abs( z - prev_z ) > std::numeric_limits< float_single >::epsilon() );
		
		return z;
	}
	
	complex_single z = ( base == complex_single( 2 ) ? 3 : 2 );
	complex_single prev_z;

	do{
		
		prev_z = z;
		z = log( base , z );

	} while( abs( z - prev_z ) > std::numeric_limits< float_single >::epsilon() );
	
	return z;
}

complex50 alpha_tet( const complex50 & base ){
	
	if( base == exp( complex50( 1 ) ) ){
		
		complex50 z = 2;
		complex50 prev_z;

		do{
			
			prev_z = z;
			z = log( z );

		} while( abs( z - prev_z ) > std::numeric_limits< float50 >::epsilon() );
		
		return z;
	}
	
	complex50 z = ( base == complex50( 2 ) ? 3 : 2 );
	complex50 prev_z;

	do{
		
		prev_z = z;
		z = log( base , z );

	} while( abs( z - prev_z ) > std::numeric_limits< float50 >::epsilon() );
	
	return z;
}

complex100 alpha_tet( const complex100 & base ){
	
	if( base == exp( complex100( 1 ) ) ){
		
		complex100 z = 2;
		complex100 prev_z;

		do{
			
			prev_z = z;
			z = log( z );

		} while( abs( z - prev_z ) > std::numeric_limits< float100 >::epsilon() );
		
		return z;
	}
	
	complex100 z = ( base == complex100( 2 ) ? 3 : 2 );
	complex100 prev_z;

	do{
		
		prev_z = z;
		z = log( base , z );

	} while( abs( z - prev_z ) > std::numeric_limits< float100 >::epsilon() );
	
	return z;
}

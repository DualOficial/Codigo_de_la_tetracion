#version 330 core
#ADD ORTOGONAL SHADER

//vec2

vec2 perInteger( vec2 v , int n ){
	
	if( n >= 0 ){
		
		v = log( v );
		
		while( n > 0 ){
			
			v = p( v , exp( v ) );
			n--;

		}
		
		return exp( v );
	}

	n = -n;
	v = log( v );

	while( n > 0 ){
		
		v = wlambert( v );
		n--;
		
	}
	
	return exp( v );
}

vec2 per( vec2 u , vec2 w ){
	
	vec2 a = perInteger( u , -value );
	
	return perInteger( asc( a , w ) , value );
}

vec2 F( vec2 w ){
	
	vec2 log_w = log( w );
	vec2 term1 = w;
	vec2 term2 = vk( 1.0 );
	vec2 term3 = vk( exp( 1.0 ) );
	vec2 prev_result;
	vec2 result = vk( 1.0 );
	float n = 0.0;
	
	do{
		
		prev_result = result;
		term1 = wave( term1 );
		term2 = p( term2 , term1 );
		term3 = wave( term3 );
		result = p( result , d( vk( 1.0 ) + d( log_w , term2 ) , term3 ) );
		n++;
		
	} while( n < value );
	
	return result;
}

vec2 gen( vec2 x , vec2 y ){
	
	return inverse( log( perInteger( x , -value ) ) ) - inverse( log( perInteger( y , -value ) ) );
	
}

//orto

orto perInteger( orto v , int n ){
	
	if( n >= 0 ){
		
		v = log( v );
		
		while( n > 0 ){
			
			v = p( v , exp( v ) );
			n--;

		}
		
		return exp( v );
	}

	n = -n;
	v = log( v );

	while( n > 0 ){
		
		v = wlambert( v );
		n--;
		
	}
	
	return exp( v );
}

orto per( orto u , orto w ){
	
	orto a = perInteger( u , -value );
	
	return perInteger( asc( a , w ) , value );
}

orto F( orto w ){
	
	orto log_w = log( w );
	orto term1 = w;
	orto term2 = k( 1.0 );
	orto term3 = k( exp( 1.0 ) );
	orto prev_result;
	orto result = k( 1.0 );
	float n = 0.0;
	
	do{
		
		prev_result = result;
		term1 = wave( term1 );
		term2 = p( term2 , term1 );
		term3 = wave( term3 );
		result = p( result , d( s( k( 1.0 ) , d( log_w , term2 ) ) , term3 ) );
		n++;
		
	} while( n < value );
	
	return result;
}

orto gen( orto x , orto y ){
	
	return r( inverse( log( perInteger( x , -value ) ) ) , inverse( log( perInteger( y , -value ) ) ) );
	
}

orto f( orto a ){
	
	return per( k( 2.0 ) , a );

}

void main(){
	
	ortoper number = adjust( getCoords() );
	
	graph( f( to_orto( number ) ).z );
	
}

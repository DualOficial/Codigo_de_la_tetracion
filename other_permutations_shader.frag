#version 330 core
#ADD ORTOGONAL SHADER

ortoper expm( ortoper x ){
	
	return r( exp( x ) , kper( 1.0 ) );

}

ortoper logm( ortoper x ){
	
	return log( s( x , kper( 1.0 ) ) );

}

ortoper mtetration_integer( ortoper x , int n ){
	
	if( n >= 0 ){
		
		while( n > 0 ){
			
			x = expm( x );

			n--;
		}

		return x;
	}

	n = -n;

	while( n > 0 ){
		
		x = logm( x );

		n--;
	}

	return x;
}

ortoper expp( ortoper x ){
	
	return exp( r( x , kper( 1.0 ) ) );

}

ortoper logp( ortoper x ){
	
	return s( log( x ) , kper( 1.0 ) );

}

ortoper ptetration_integer( ortoper x , int n ){
	
	if( n >= 0 ){
		
		while( n > 0 ){
			
			x = expp( x );

			n--;
		}

		return x;
	}

	n = -n;

	while( n > 0 ){
		
		x = logp( x );

		n--;
	}

	return x;
}

ortoper log( ortoper x , ortoper y ){
	
	return d( log( y ) , log( x ) );

}

ortoper asc_mtetration( ortoper x , ortoper y ){
	
	return r( pow( s( x , kper( 1.0 ) ) , pow( s( x , kper( 1.0 ) ) , d( y , kper( 2.0 ) ) ) ) , kper( 1.0 ) );
	
}

ortoper mtetration( ortoper x , ortoper y ){
	
	ortoper a = mtetration_integer( x , -value );
	
	return mtetration_integer( asc_mtetration( a , y ) , value );
}

ortoper asc_ptetration( ortoper x , ortoper y ){
	
	return pow( x , pow( x , d( y , kper( 2.0 ) ) ) );
	
}

ortoper ptetration( ortoper x , ortoper y ){
	
	ortoper a = ptetration_integer( x , -value );
	
	return ptetration_integer( asc_ptetration( a , y ) , value );
}

vec2 g( vec2 x ){
	
	return vk( 0.5 ) + pow( x , 2.0 ) * 0.5;

}

vec2 h( vec2 x ){
	
	return sqrt( x * 2.0 - vk( 1.0 ) );

}

vec2 g_integer( vec2 x , int n ){
	
	if( n >= 0 ){
		
		while( n > 0 ){
			
			x = g( x );

			n--;
		}

		return x;
	}

	n = -n;

	while( n > 0 ){
		
		x = h( x );

		n--;
	}

	return x;
}

vec2 f( vec2 x ){
	
	vec2 a = g_integer( vk( e ) , -value );

	return g_integer( pow( a , pow( a , x * 0.5 ) ) , value );
}

void main(){
	
	ortoper number = adjust( getCoords() );
	
	graph( f( number.w.z ) );
	
}
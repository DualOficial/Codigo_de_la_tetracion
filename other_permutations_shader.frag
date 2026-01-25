#version 330 core
#ADD ORTOGONAL SHADER

//vec2

vec2 expm( vec2 x ){
	
	return exp( x ) - vk( 1.0 );

}

vec2 logm( vec2 x ){
	
	return log( x + vk( 1.0 ) );

}

vec2 mtetration_integer( vec2 x , int n ){
	
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

vec2 expp( vec2 x ){
	
	return exp( x - vk( 1.0 ) );

}

vec2 logp( vec2 x ){
	
	return log( x ) + vk( 1.0 );

}

vec2 ptetration_integer( vec2 x , int n ){
	
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

vec2 asc_mtetration( vec2 x , vec2 y ){
	
	return pow( x + vk( 1.0 ) , pow( x + vk( 1.0 ) , y / vk( 2.0 ) ) ) - vk( 1.0 );
	
}

vec2 mtetration( vec2 x , vec2 y ){
	
	vec2 a = mtetration_integer( x , -value );
	
	return mtetration_integer( asc_mtetration( a , y ) , value );
}

vec2 ptetration( vec2 x , vec2 y ){
	
	vec2 a = ptetration_integer( x , -value );
	
	return ptetration_integer( asc( a , y / 2.0 ) , value );
}

vec2 g( vec2 x ){
	
	return vk( 0.5 ) + p( x , x ) * 0.5;

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

vec2 g_iterared( vec2 x , vec2 y ){
	
	vec2 a = g_integer( x , -value );

	return g_integer( pow( a , pow( a , y / 2.0 ) ) , value );
}

//orto

orto expm( orto x ){
	
	return r( exp( x ) , k( 1.0 ) );

}

orto logm( orto x ){
	
	return log( s( x , k( 1.0 ) ) );

}

orto mtetration_integer( orto x , int n ){
	
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

orto expp( orto x ){
	
	return exp( r( x , k( 1.0 ) ) );

}

orto logp( orto x ){
	
	return s( log( x ) , k( 1.0 ) );

}

orto ptetration_integer( orto x , int n ){
	
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

orto asc_mtetration( orto x , orto y ){
	
	return r( pow( s( x , k( 1.0 ) ) , pow( s( x , k( 1.0 ) ) , d( y , k( 2.0 ) ) ) ) , k( 1.0 ) );
	
}

orto mtetration( orto x , orto y ){
	
	orto a = mtetration_integer( x , -value );
	
	return mtetration_integer( asc_mtetration( a , y ) , value );
}

orto ptetration( orto x , orto y ){
	
	orto a = ptetration_integer( x , -value );
	
	return ptetration_integer( asc( a , d( y , k( 2.0 ) ) ) , value );
}

orto g( orto x ){
	
	return s( k( 0.5 ) , p( p( x , x ) , k( 0.5 ) ) );

}

orto h( orto x ){
	
	return sqrt( r( p( x , k( 2.0 ) ) , k( 1.0 ) ) );

}

orto g_integer( orto x , int n ){
	
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

orto g_iterared( orto x , orto y ){
	
	orto a = g_integer( x , -value );

	return g_integer( pow( a , pow( a , d( y , k( 2.0 ) ) ) ) , value );
}

//ortoper

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

ortoper ptetration( ortoper x , ortoper y ){
	
	ortoper a = ptetration_integer( x , -value );
	
	return ptetration_integer( asc( a , d( y , kper( 2.0 ) ) ) , value );
}

ortoper g( ortoper x ){
	
	return s( kper( 0.5 ) , p( p( x , x ) , kper( 0.5 ) ) );

}

ortoper h( ortoper x ){
	
	return sqrt( r( p( x , kper( 2.0 ) ) , kper( 1.0 ) ) );

}

ortoper g_integer( ortoper x , int n ){
	
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

ortoper g_iterared( ortoper x , ortoper y ){
	
	ortoper a = g_integer( x , -value );

	return g_integer( pow( a , pow( a , d( y , kper( 2.0 ) ) ) ) , value );
}

vec2 f( vec2 x ){
	
	return g_iterared( vk( 2.0 ) ,  x );

}

void main(){
	
	ortoper number = adjust( getCoords() );
	
	graph( f( to_orto( number ).z ) );

}

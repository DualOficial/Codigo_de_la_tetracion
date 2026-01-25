uniform float left;
uniform float bottom;
uniform float width;
uniform float height;
uniform float index;
uniform float index2;
uniform bool mod;
uniform bool colored;
uniform vec2 resolution;
uniform int ortogonal;
uniform int value;

//EXTRA MATH

float pi = 3.14159265358979323846;
float u = 4.90132570266723632812;
float e = exp( 1.0 );
float INFINITY = 3.402823466e+38;
float nan = 1.0 / 0.0;
vec2 vi = vec2( 0.0 , 1.0 );

float module( vec2 v ){
	
	return sqrt( v.x * v.x + v.y * v.y );
	
}

float angle( vec2 v ){
	
	if( isnan( v.x ) || isinf( v.x ) || isinf( -v.x )
	||  isnan( v.y ) || isinf( v.y ) || isinf( -v.y ) ){
		
		return nan;
		
	}
	
	float result = atan( v.y / v.x );
	
	if( isnan( result ) || isinf( result ) || v.x == -0.0 ){
		
		if( v.y == 0.0 ) return nan;
		
		return v.y > 0.0 ? pi / 2.0 : 3.0 * pi / 2.0;
	}
	
	if( v.x < 0.0 ) result += pi;
	if( v.x > 0.0 && v.y < 0.0 ) result += pi * 2.0;
	if( result <= 0.0 ) return result + pi * 2.0;
	
	return result;
}

float arg( vec2 v ){
	
	if( isnan( v.x ) || isinf( v.x ) || isinf( -v.x )
	||  isnan( v.y ) || isinf( v.y ) || isinf( -v.y ) ){
		
		nan;
		
	}
	
	if( v.x > 0.0 ) return atan( v.y / v.x );
	if( v.x < 0.0 && v.y >= 0.0 ) return atan( v.y / v.x ) + pi;
	if( v.x < 0.0 && v.y < 0.0 ) return atan( v.y / v.x ) - pi;
	if( v.x == 0.0 && v.y > 0.0 ) return pi / 2.0;
	if( v.x == 0.0 && v.y < 0.0 ) return -pi / 2.0;
	
	return nan;
}

int branch( float angle ){
	
	return int( ceil( ( angle + pi ) / ( pi * 2.0 ) ) ) - 1;
	
}

float collapse( float angle ){
	
	return angle - float( branch( angle ) ) * ( pi * 2.0 );
	
}

float rebranch( float a1 , float a2 ){
	
	return collapse( a1 ) + float( branch( a2 ) ) * ( pi * 2.0 );
	
}

//VEC2 MATH

vec2 conj( vec2 z ){
	
	return vec2( z.x , -z.y );

}

vec2 vk( float x ){
	
	return vec2( x , 0.0 );
	
}

vec2 p( vec2 a , vec2 b ){
	
	return vec2( a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x );
	
}

vec2 inverse( vec2 a ){
	
	float b = a.x * a.x + a.y * a.y;
	
	return vec2( a.x / b , -a.y / b );
}

vec2 d( vec2 a , vec2 b ){
	
	return p( a , inverse( b ) );
	
}

vec2 exp( vec2 a ){
	
	float b = exp( a.x );
	
	return vec2( b * cos( a.y ) , b * sin( a.y ) );
}

vec2 log( vec2 a ){
	
	return vec2( log( module( a ) ) , arg( a ) );
	
}

vec2 pow( vec2 a , vec2 b ){
	
	return exp( p( log( a ) , b ) );
	
}

vec2 root( vec2 a , vec2 b ){
	
	return exp( d( log( a ) , b ) );
	
}

vec2 per( vec2 a ){
	
	return vec2( -a.y , a.x );
	
}

vec2 cbrt( vec2 a ){
	
	return root( a , vk( 3.0 ) );
	
}

vec2 cos( vec2 z ){
	
	return d( exp( per( z ) ) + exp( -per( z ) ) , vk( 2.0 ) );
	
}

vec2 sin( vec2 z ){
	
	return d( exp( per( z ) ) - exp( -per( z ) ) , vec2( 0.0 , 2.0 ) );
	
}

vec2 tan( vec2 z ){
	
	return d( sin( z ) , cos( z ) );
	
}

vec2 cot( vec2 z ){
	
	return d( cos( z ) , sin( z ) );
	
}

vec2 sec( vec2 z ){
	
	return inverse( cos( z ) );
	
}

vec2 pow( vec2 z , float x ){
	
	return pow( z , vk( x ) );
	
}

vec2 csc( vec2 z ){
	
	return inverse( sin( z ) );
	
}

vec2 cosh( vec2 z ){
	
	return d( exp( z ) - exp( -z ) , vk( 2.0 ) );
	
}

vec2 sinh( vec2 z ){
	
	return d( exp( z ) - exp( -z ) , vk( 2.0 ) );
	
}

vec2 tanh( vec2 z ){
	
	return d( sinh( z ) , cosh( z ) );
	
}

vec2 coth( vec2 z ){
	
	return d( cosh( z ) , sinh( z ) );
	
}

vec2 sech( vec2 z ){
	
	return inverse( cosh( z ) );
	
}

vec2 csch( vec2 z ){
	
	return inverse( sinh( z ) );
	
}

vec2 square( vec2 a ){
	
	return p( a , a );
	
}

vec2 zexpz( vec2 z ){
	
	return p( z , exp( z ) );
	
}

//The derivative of z * exp(z) = exp(z) + z * exp(z)
vec2 zexpz_d( vec2 z ){
	
	return exp( z ) + zexpz( z );
	
}

//The second derivative of z * exp(z) = 2. * exp(z) + z * exp(z)
vec2 zexpz_dd( vec2 z ){
	
	return exp( z ) * 2.0 + zexpz( z );
	
}

vec2 sqrt( vec2 z ){
	
	float a = module( z );
	
	return vec2( sqrt( ( a + z.x ) / 2.0 ) , sqrt( ( a - z.x ) / 2.0 ) * sign( z.y ) );
}

//Determine the initial point for the root finding
vec2 InitPoint(vec2 z, int t){
	
	const float e = 2.71828182845904523536;
	vec2 two_pi_t_I = vec2( 0.0, 2.0 * pi * t );
	vec2 ip = log(z) + two_pi_t_I - log(log(z) + two_pi_t_I);// initial point coming from the general asymptotic approximation
	vec2 u = sqrt( 2.0 * ( e * z + vk( 1.0 ) ) );// used when we are close to the branch cut around zero and when t=0,-1
	
	//we are close to the branch cut, the initial point must be chosen carefully
	if( ( t == 0 && module( z - vk( exp( -1.0 ) ) ) <= 1.0 ) ){
		
		if( t == 0 ) ip = vk( -1.0 ) + u - ( 1.0 / 3.0 ) * p( u , u ) + ( 11.0 / 72.0 ) * p( u , p( u , u ) );
		if( t == 1 && z.y < 0.0 ) ip = vk( -1.0 ) - u - ( 1.0 / 3.0 ) * p( u , u ) - ( 11.0 / 72.0 ) * p( u , p( u , u ) );
		if( t == -1 && z.y > 0.0 ) ip = vk( -1.0 ) - u - ( 1.0 / 3.0 ) * p( u , u ) - ( 11.0 / 72.0 ) * p( u , p( u , u ) );
		
	}
	
	if( t == 0 && module(z - vk(0.5)) <= 0.5 ){
		
		// (1,1) Pade approximant for W(0,a)
		ip = d( p( vk( 0.35173371 ) , vk( 0.1237166 ) + 7.061302897 * z ) , vk( 2.0 ) + 0.827184 * ( vk( 1.0 ) + 2.0 * z ) );
		
	}
	
	if( t == -1 && module( z - vk(0.5) ) <= 0.5 ){
		
		// (1,1) Pade approximant for W(-1,a)
		ip = -d( p( vec2( 2.2591588985 , 4.22096 ) , 
		p( vec2( -14.073271 , -33.767687754 ) , z ) -
		p( vec2( 12.7127 ,-19.071643 ) , vk( 1.0 ) + 2.0 * z ) ) ,
		( vk( 2.0 ) - p( vec2( 17.23103 , -10.629721 ) , ( vk( 1.0 ) + 2.0 * z ) ) ) );
		
	}
	
	return ip;
}

vec2 wlambert( vec2 z , int t ){
	
	//For some particular z and k W(z,k) has simple value:
	if( z == vk( 0.0 ) ) return ( t == 0 ) ? 0.0 : -INFINITY;
	if( z == vk( -exp( -1.0 ) ) && ( t == 0 || t == -1 ) ) return vk( -1.0 );
	if( z == vk( exp( 1.0 ) ) && t == 0 ) return vk( 1.0 );
	
	//Halley method begins
	vec2 w = InitPoint( z , t ) , wprev; // intermediate values in the Halley method
	const int maxiter = 30; // max number of iterations. This eliminates improbable infinite loops
	int iter = 0; // iteration counter
	float prec = 1.E-30; // difference threshold between the last two iteration results (or the iter number of iterations is taken)
	
	do{
		
		wprev = w;
		w -= 2.0 * d( p( zexpz( w ) - z , zexpz_d( w ) ) ,
		2.0 * square( zexpz_d( w ) ) - p( zexpz( w ) - z , zexpz_dd( w ) ) );
		iter++;
		
	} while( module( w - wprev ) > prec && iter < maxiter );
	
	return w;
}

vec2 wlambert( vec2 z ){
	
	return wlambert( z , 0 );

}

vec2 wave( vec2 z ){
	
	return exp( wlambert( log( z ) ) );

}

vec2 asc( vec2 a , vec2 b ){
	
	return pow( a , pow( a , b ) );

}

vec2 log2( vec2 a , vec2 b ){
	
	return d( log( b ) , log( a ) );

}

vec2 e_tetration_integer( vec2 z , int n ){
	
	if( n < 0 ){
		
		n = -n;
		
		while( n > 0 ){
			
			z = log( z );
			n--;

		}

		return z;
	}

	while( n > 0 ){
		
		z = exp( z );
		n--;

	}

	return z;
}

vec2 tetration_integer( vec2 base , vec2 a , int n ){
	
	if( n < 0 ){
		
		n = -n;
		
		while( n > 0 ){
			
			a = log2( base , a );
			n--;

		}

		return a;
	}

	while( n > 0 ){
		
		a = pow( base , a );
		n--;

	}

	return a;
}

vec2 kproduct( int n , vec2 u , vec2 v ){
	
	if( n < 0 ){
		
		for( int k = 0; k < -n; k++ ){
		
			u = exp( u );
			v = exp( v );

		}

		vec2 result = u + v;

		for( int k = 0; k < -n; k++ ){
		
			result = log( result );

		}

		return result;
	}

	if( n == 0 ) return u + v;

	for( int k = 0; k < n - 1; k++ ){
		
		u = log( u );
		v = log( v );

	}

	vec2 result = u * v;

	for( int k = 0; k < n - 1; k++ ){
		
		result = exp( result );

	}

	return result;
}

vec2 kinverse( int n , vec2 z ){
	
	if( n < 0 ){
		
		for( int k = 0; k < -n; k++ ){
		
			z = exp( z );

		}

		z = -z;

		for( int k = 0; k < -n; k++ ){
		
			z = log( z );

		}

		return z;
	}

	if( n == 0 ) return -z;

	for( int k = 0; k < n - 1; k++ ){
		
		z = log( z );

	}
	
	z = inverse( z );

	for( int k = 0; k < n - 1; k++ ){
		
		z = exp( z );

	}

	return z;
}

//ORTOGONALS 0

struct orto{
	
	vec2 z;
	int branch1;
	int branch2;
	
};

orto conj( orto w ){
	
	orto u;

	u.z = conj( w.z );
	u.branch1 = w.branch1;
	u.branch2 = w.branch2;

	return u;
}

orto k( float x ){
	
	orto r;
	
	r.z = vec2( x , 0.0 );
	r.branch1 = 0;
	r.branch2 = 0;
	
	return r;
}

orto make_orto( float x , float y , int b1 , int b2 ){
	
	orto r;
	
	r.z = vec2( x , y );
	r.branch1 = b1;
	r.branch2 = b2;
	
	return r;
}

orto make_orto( float x , float y , int b1 ){
	
	orto r;
	
	r.z = vec2( x , y );
	r.branch1 = b1;
	r.branch2 = 0;
	
	return r;
}

orto make_orto( float x , float y ){
	
	orto r;
	
	r.z = vec2( x , y );
	r.branch1 = 0;
	r.branch2 = 0;
	
	return r;
}

orto make_orto( vec2 z , int b1 , int b2 ){
	
	orto r;
	
	r.z = z;
	r.branch1 = b1;
	r.branch2 = b2;
	
	return r;
}

orto make_orto( vec2 z , int b1 ){
	
	orto r;
	
	r.z = z;
	r.branch1 = b1;
	r.branch2 = 0;
	
	return r;
}

orto make_orto( vec2 z ){
	
	orto r;
	
	r.z = z;
	r.branch1 = 0;
	r.branch2 = 0;
	
	return r;
}

orto i = make_orto( 0.0 , 1.0 );

orto s( orto a , orto b ){
	
	vec2 r = a.z + b.z;
	float angle1 = arg( a.z );
	float angle2 = arg( b.z );
	
	if( a.z.y >= 0 && r.x < 0 && r.y < 0 && angle2 < angle1 - pi ){
		
		return make_orto( r , a.branch1 + b.branch1 + 1 );
		
	}
	
	if( a.z.y < 0 && r.x < 0 && r.y >= 0 && angle2 > angle1 + pi ){
		
		return make_orto( r , a.branch1 + b.branch1 - 1 );
		
	}
	
	return make_orto( r , a.branch1 + b.branch1 );
}

orto r( orto a , orto b ){
	
	return make_orto( a.z - b.z );
	
}

orto p( orto a , orto b ){
	
	float angle1 = a.branch1 * pi * 2.0 + arg( a.z );
	float angle2 = b.branch1 * pi * 2.0 + arg( b.z );
	
	return make_orto( a.z.x * b.z.x - a.z.y * b.z.y , a.z.x * b.z.y + a.z.y * b.z.x , branch( angle1 + angle2 ) );
}

orto n( orto w ){
	
	return make_orto( -w.z.x , -w.z.y , -w.branch1 );
	
}

orto inverse( orto w ){
	
	float m = w.z.x * w.z.x + w.z.y * w.z.y;
	
	return make_orto( w.z.x / m , -w.z.y / m , -w.branch1 , w.branch2 );
}

orto d( orto a , orto b ){
	
	return p( a , inverse( b ) );
	
}

orto exp( orto w ){
	
	float m = exp( w.z.x );
	
	return make_orto( m * cos( w.z.y ) , m * sin( w.z.y ) , branch( w.z.y ) , w.branch1 );
}

orto log( orto w ){
	
	return make_orto( log( module( w.z ) ) , arg( w.z ) + float( w.branch1 ) * pi * 2.0 , w.branch2 );
	
}

orto pow( orto u , orto v ){
	
	return exp( p( log( u ) , v ) );
	
}

orto root( orto u , orto v ){
	
	return exp( d( log( u ) , v ) );
	
}

orto sqrt( orto w ){
	
	float m = module( w.z );
	int new_branch = branch( float( w.branch1 ) * pi + arg( w.z ) / 2.0 );
	
	if( w.branch1 % 2 == 0 ){
		
		return make_orto( sqrt( ( m + w.z.x ) / 2.0 ) , sqrt( ( m - w.z.x ) / 2.0 ) * sign( w.z.y ) , new_branch , w.branch2 );
		
	}
	
	return make_orto( -sqrt( ( m + w.z.x ) / 2.0 ) , -sqrt( ( m - w.z.x ) / 2.0 ) * sign( w.z.y ) , new_branch , w.branch2 );
}

orto cbrt( orto w ){
	
	return root( w , k( 3.0 ) );
	
}

orto cos( orto w ){
	
	return d( s( exp( p( w , i ) ) , exp( n( p( w , i ) ) ) ) , k( 2.0 ) );
	
}

orto sin( orto w ){
	
	return d( r( exp( p( w , i ) ) , exp( n( p( w , i ) ) ) ) , make_orto( 0.0 , 2.0 ) );
	
}

orto tan( orto w ){
	
	return d( sin( w ) , cos( w ) );
	
}

orto cot( orto w ){
	
	return d( cos( w ) , sin( w ) );
	
}

orto sec( orto w ){
	
	return inverse( cos( w ) );
	
}

orto csc( orto w ){
	
	return inverse( sin( w ) );
	
}

orto cosh( orto w ){
	
	return d( s( exp( w ) , exp( n( w ) ) ) , k( 2.0 ) );
	
}

orto sinh( orto w ){
	
	return d( r( exp( w ) , exp( n( w ) ) ) , k( 2.0 ) );
	
}

orto tanh( orto w ){
	
	return d( sinh( w ) , cosh( w ) );
	
}

orto coth( orto w ){
	
	return d( cosh( w ) , sinh( w ) );
	
}

orto sech( orto w ){
	
	return inverse( cosh( w ) );
	
}

orto csch( orto w ){
	
	return inverse( sinh( w ) );
	
}

orto collapse( orto w ){
	
	return make_orto( w.z );
	
}

orto square( orto w ){
	
	return p( w , w );
	
}

orto cube( orto w ){
	
	return p( p( w , w ) , w );
	
}

orto factor( orto u , orto v ){
	
	return p( s( u , v ) , r( u , v ) );
	
}

orto wlambert( orto w ){
	
	return make_orto( wlambert( w.z , w.branch1 ) );
	
}

orto wave( orto w ){
	
	return exp( wlambert( log( w ) ) );
	
}

orto pow( orto w , float x ){
	
	return pow( w , k( x ) );

}

orto kproduct( int n , orto u , orto v ){
	
	if( n < 0 ){
		
		for( int k = 0; k < -n; k++ ){
		
			u = exp( u );
			v = exp( v );

		}

		orto result = s( u , v );

		for( int k = 0; k < -n; k++ ){
		
			result = log( result );

		}

		return result;
	}

	if( n == 0 ) return s( u , v );

	for( int k = 0; k < n - 1; k++ ){
		
		u = log( u );
		v = log( v );

	}

	orto result = p( u , v );

	for( int k = 0; k < n - 1; k++ ){
		
		result = exp( result );

	}

	return result;
}

orto kinverse( int n , orto w ){
	
	if( n < 0 ){
		
		for( int k = 0; k < -n; k++ ){
		
			w = exp( w );

		}

		w = n( w );

		for( int k = 0; k < -n; k++ ){
		
			w = log( w );

		}

		return w;
	}

	if( n == 0 ) return n( w );

	for( int k = 0; k < n - 1; k++ ){
		
		w = log( w );

	}
	
	w = inverse( w );

	for( int k = 0; k < n - 1; k++ ){
		
		w = exp( w );

	}

	return w;
}

orto asc( orto a , orto b ){
	
	return pow( a , pow( a , b ) );

}

orto log2( orto a , orto b ){
	
	return d( log( b ) , log( a ) );

}

orto e_tetration_integer( orto a , int n ){
	
	if( n < 0 ){
		
		n = -n;
		
		while( n > 0 ){
			
			a = log( a );
			n--;

		}

		return a;
	}

	while( n > 0 ){
		
		a = exp( a );
		n--;

	}

	return a;
}


orto tetration_integer( orto base , orto a , int n ){
	
	if( n < 0 ){
		
		n = -n;
		
		while( n > 0 ){
			
			a = log2( base , a );
			n--;

		}

		return a;
	}

	while( n > 0 ){
		
		a = pow( base , a );
		n--;

	}

	return a;
}

//ORTOGONALS PERSPECTIVE

struct ortoper{
	
	orto w;
	int per;
	
};

ortoper conj( ortoper a ){
	
	ortoper u;

	u.w = conj( a.w );
	u.per = a.per;

	return u;
}

orto tetration_integer( orto w , int n ){
	
	if( n < 0 ){
		
		n = -n;
		
		while( n > 0 ){
			
			w = log( w );
			n--;

		}

		return w;
	}

	while( n > 0 ){
		
		w = exp( w );
		n--;

	}

	return w;
}

ortoper to_ortoper( orto a , int n ){
	
	ortoper result;

	result.w = tetration_integer( a , -n );
	result.per = n;

	return result;
}

ortoper to_ortoper( orto a ){
	
	ortoper result;

	result.w = a;
	result.per = 0;

	return result;
}

ortoper to_ortoper( float a , float b , int n ){
	
	return to_ortoper( make_orto( a , b ) , n );

}

ortoper to_ortoper( float a , float b ){
	
	return to_ortoper( make_orto( a , b ) );

}

orto to_orto( ortoper a ){
	
	return tetration_integer( a.w , a.per );

}

ortoper change( ortoper a , int n ){
	
	a.w = tetration_integer( a.w , a.per - n );
	a.per = n;

	return a;
}

ortoper make_orto_per( orto w , int per ){
	
	ortoper result;

	result.w = w;
	result.per = per;

	return result;
}

ortoper iper = make_orto_per( i , 0 );

ortoper kproduct( int n , ortoper a , ortoper b ){
	
	if( a.per == b.per ){
		
		return make_orto_per( kproduct( n - a.per , a.w , b.w ) , a.per );

	}

	if( abs( a.per - n ) < abs( b.per - n ) ){
		
		b = change( b , a.per );

		return make_orto_per( kproduct( n - a.per , a.w , b.w ) , a.per );
	}

	a = change( a , b.per );

	return make_orto_per( kproduct( n - a.per , a.w , b.w ) , a.per );
}

ortoper kinverse( int n , ortoper a ){
	
	return make_orto_per( kinverse( n - a.per , a.w ) , a.per );
	
}

ortoper s( ortoper a , ortoper b ){
	
	return kproduct( 0 , a , b );

}

ortoper p( ortoper a , ortoper b ){
	
	return kproduct( 1 , a , b );

}

ortoper n( ortoper a ){
	
	return kinverse( 0 , a );
	
}

ortoper inverse( ortoper a ){
	
	return kinverse( 1 , a );
	
}

ortoper r( ortoper a , ortoper b ){
	
	return s( a , n( b ) );
	
}

ortoper d( ortoper a , ortoper b ){
	
	return p( a , inverse( b ) );
	
}

ortoper exp( ortoper a ){
	
	return make_orto_per( exp( a.w ) , a.per );

}

ortoper log( ortoper a ){
	
	return make_orto_per( log( a.w ) , a.per );

}

ortoper pow( ortoper a , ortoper b ){
	
	return exp( p( log( a ) , b ) );

}

ortoper wlambert( ortoper a ){
	
	return to_ortoper( wlambert( a.w ) , a.per );

}

ortoper wave( ortoper a ){
	
	return exp( wlambert( log( a ) ) );

}

ortoper root( ortoper u , ortoper v ){
	
	return exp( d( log( u ) , v ) );
	
}

ortoper kper( float x ){
	
	return make_orto_per( k( x ) , 0 );

}

ortoper sqrt( ortoper w ){
	
	return pow( w , kper( 0.5 ) );

}

ortoper cbrt( ortoper w ){
	
	return root( w , kper( 3.0 ) );
	
}

ortoper cos( ortoper w ){
	
	return d( s( exp( p( w , iper ) ) , exp( n( p( w , iper ) ) ) ) , kper( 2.0 ) );
	
}

ortoper sin( ortoper w ){
	
	return d( r( exp( p( w , iper ) ) , exp( n( p( w , iper ) ) ) ) , to_ortoper( 0.0 , 2.0 ) );
	
}

ortoper tan( ortoper w ){
	
	return d( sin( w ) , cos( w ) );
	
}

ortoper cot( ortoper w ){
	
	return d( cos( w ) , sin( w ) );
	
}

ortoper sec( ortoper w ){
	
	return inverse( cos( w ) );
	
}

ortoper csc( ortoper w ){
	
	return inverse( sin( w ) );
	
}

ortoper cosh( ortoper w ){
	
	return d( s( exp( w ) , exp( n( w ) ) ) , kper( 2.0 ) );
	
}

ortoper sinh( ortoper w ){
	
	return d( r( exp( w ) , exp( n( w ) ) ) , kper( 2.0 ) );
	
}

ortoper tanh( ortoper w ){
	
	return d( sinh( w ) , cosh( w ) );
	
}

ortoper coth( ortoper w ){
	
	return d( cosh( w ) , sinh( w ) );
	
}

ortoper sech( ortoper w ){
	
	return inverse( cosh( w ) );
	
}

ortoper csch( ortoper w ){
	
	return inverse( sinh( w ) );
	
}

ortoper collapse( ortoper a ){
	
	return make_orto_per( collapse( a.w ) , a.per );
	
}

ortoper square( ortoper w ){
	
	return p( w , w );
	
}

ortoper cube( ortoper w ){
	
	return p( p( w , w ) , w );
	
}

ortoper pow( ortoper w , float x ){
	
	return pow( w , kper( x ) );

}

ortoper factor( ortoper u , ortoper v ){
	
	return p( s( u , v ) , r( u , v ) );
	
}

ortoper e_tetration_integer( ortoper w , int n ){
	
	if( n < 0 ){
		
		n = -n;
		
		while( n > 0 ){
			
			w = log( w );
			n--;

		}

		return w;
	}

	while( n > 0 ){
		
		w = exp( w );
		n--;

	}

	return w;
}

ortoper asc( ortoper a , ortoper b ){
	
	return pow( a , pow( a , b ) );

}

ortoper log2( ortoper a , ortoper b ){
	
	return d( log( b ) , log( a ) );

}

ortoper tetration_integer( ortoper base , ortoper a , int n ){
	
	if( n < 0 ){
		
		n = -n;
		
		while( n > 0 ){
			
			a = log2( base , a );
			n--;

		}

		return a;
	}

	while( n > 0 ){
		
		a = pow( base , a );
		n--;

	}

	return a;
}

//GRAPHIC FUNCTIONS

float fmod( float x , float y ){
	
	return x - trunc( x / y ) * y;
	
}

vec2 rotate( vec2 z , float a ){
	
	vec2 w = vec2( cos( a ) , sin( a ) );
	
	return vec2( z.x * w.x - z.y * w.y , z.x * w.y + z.y * w.x );
}

vec4 hsvToRGB( float h , float s , float v , float alpha ){

	s /= 100.0;
	v /= 100.0;
	
    float r,g,b;
    float P, Q, T, fract;

    (h == 360.0)?(h = 0.0):(h /= 60.0);
    fract = h - floor(h);

    P = v*(1.0 - s);
    Q = v*(1.0 - s*fract);
    T = v*(1.0 - s*(1.0 - fract));

    if(0.0 <= h && h < 1.0){
        r = v;
		g = T;
		b = P;
	}
    else if(1.0 <= h && h < 2.0){
        r = Q;
		g = v;
		b = P;
	}
    else if(2.0 <= h && h < 3.0){
        r = P;
		g = v;
		b = T;
 	}
    else if(3.0 <= h && h < 4.0){
        r = P;
		g = Q;
		b = v;
	}
    else if(4.0 <= h && h < 5.0){
        r = T;
		g = P;
		b = v;
 	}
    else if(5.0 <= h && h < 6.0){
        r = v;
		g = P;
		b = Q;
	}
    else{
    	
   		r = 0.0;
		g = 0.0;
		b = 0.0;
    	
	}

    return vec4( r , g , b , alpha );
}

float colorModule( float x ){
	
	return x - floor( x );
	
}

ortoper adjust0( vec2 number ){
	
	orto n = make_orto( number );
	
	if( index != 0.0 ){
		
		n.branch1 = branch( arg( n.z ) + index );
		n.z = rotate( n.z , index );
		
	}
	
	if( index2 != 0.0 ){
		
		vec2 orto_z = vec2( log( module( n.z ) ) , arg( n.z ) + float( n.branch1 ) * pi * 2.0 );
		
		n.branch2 = branch( arg( orto_z ) + index2 );
		
		orto_z = rotate( orto_z , index2 );
		
		n.z = vec2( exp( orto_z.x ) * cos( orto_z.y ) , exp( orto_z.x ) * sin( orto_z.y ) );
		n.branch1 = branch( orto_z.y );
		
	}
	
	return to_ortoper( n , 0 );
}

ortoper adjust1( vec2 number ){
	
	orto n = make_orto( number );

	n.z.y += index;
	n.branch1 = branch( arg( n.z ) + index2 );
	n.z = rotate( n.z , index2 );

	return make_orto_per( n , 1 );
}

ortoper adjust2( vec2 number ){
	
	orto n = make_orto( number );

	n.z = log( exp( n.z ) + vec2( 0.0 , index ) );
	n.z.y += index2;

	return make_orto_per( n , 2 );
}

orto acos( orto w ){
	
	return p( log( s( w , p( sqrt( s( w , k( 1.0 ) ) ) , sqrt( r( w , k( 1.0 ) ) ) ) ) ) , n( i ) );
	
}

orto perp( orto x ){
	
	return p( x , i );
	
}

ortoper adjust( vec2 number ){	
	
	if( ortogonal == 2 ){
		
		return adjust2( number );
		
	}
	
	if( ortogonal == 1 ){
		
		return  adjust1( number );
		
	}
	
	return adjust0( number );
}

void graph( vec2 z ){
	
	float factor = colorModule( module( z ) );

	gl_FragColor = hsvToRGB( colored ? angle( z ) / ( pi * 2.0 ) * 360.0 : 0.0 , colored ? 100.0 : 0.0 , mod ? factor * 100.0 : 100.0 , 1.0 );

}

vec2 getCoords(){
	
	vec2 coord = gl_FragCoord.xy;

	return vec2( coord.x / resolution.x * width + left , coord.y / resolution.y * height + bottom );
}

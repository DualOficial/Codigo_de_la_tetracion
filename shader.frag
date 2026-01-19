#version 330 core
#ADD ORTOGONAL SHADER

vec2 perInteger( vec2 v , int n ){
	
	if( n >= 0 ){
		
		vec2 a = change( v , 1 );
		
		for( int b = 0; b < n; b++ ){
			
			a = pow( a , a );
			
		}
		
		return change( a , v.per );
	}
	
	vec2 w = to_orto( v );
	
	for( int a = 0; a < -n; a++ ){
		
		w = wave( w );
		
	}
	
	return make_orto_per( w , v.per );
}

vec2 per( vec2 u , vec2 w ){
	
	ortoper a = perInteger( u , -value );
	
	return perInteger( pow( a , pow( a , w ) ) , value );
}

vec2 per( vec2 w ){
	
	return per( kper( u ) , w );

}

vec2 perInteger( vec2 v , int n ){
	
	if( n >= 0 ){
		
		ortoper a = change( v , 1 );
		
		for( int b = 0; b < n; b++ ){
			
			a = pow( a , a );
			
		}
		
		return change( a , v.per );
	}
	
	orto w = to_orto( v );
	
	for( int a = 0; a < -n; a++ ){
		
		w = wave( w );
		
	}
	
	return make_orto_per( w , v.per );
}

ortoper per( ortoper u , ortoper w ){
	
	ortoper a = perInteger( u , -value );
	
	return perInteger( pow( a , pow( a , w ) ) , value );
}

ortoper per( ortoper w ){
	
	return per( kper( u ) , w );

}
/*
ortoper F( ortoper w ){
	
	orto w_0 = to_orto( w );
	orto log_w = log( w_0 );
	orto term1 = w_0;
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
	
	return to_ortoper( result , w.per );
}

ortoper gen( ortoper x , ortoper y ){
	
	return r( inverse( log( perInteger( x , -value ) ) ) , inverse( log( perInteger( y , -value ) ) ) );
	
}

ortoper gen( ortoper x ){
	
	return gen( kper( u ) , x );
	
}

vec2 alpha = vec2( 0.318131505204764135312 , -1.33723570143068940890 );

vec2 bin_pow( vec2 v , int n ){
	
	if( n < 0 ){
		
		n = -n;

		vec2 w = bin_k( 1.0 );

		while( n > 0 ){
			
			w = bin_p( w , v );
			n--;

		}

		return bin_inverse( w );
	}

	vec2 w = bin_k( 1.0 );

	while( n > 0 ){
		
		w = bin_p( w , v );
		n--;

	}

	return w;
}

float factorial( float k ){
	
	float r = 1.0;

	for( float i = 1; i <= k; i++ ){
		
		r *= i;

	}
	
	return r;
}

vec2 v0 = vec2(0.318131505204764135313,-1.33723570143068940890);
vec2 v1 = vec2(0.919969704921980491186,-0.726782465920492448674);
vec2 v2 = vec2(0.544436745623274154227,-0.172448234235099917555) / factorial( 2 );
vec2 v3 = vec2(0.106843471264890244043,-0.0156165215582734218103) / factorial( 3 );
vec2 v4 = vec2(0.0785454001185131867047,0.0153719367584226329626) / factorial( 4 );
vec2 v5 = vec2(-0.220080037312433418606,-0.346296329387561829805) / factorial( 5 );
vec2 v6 = vec2(-2.26087751867636743697,2.14984109358415054203) / factorial( 6 );
vec2 v7 = vec2(12.9361965460491710189,15.7373999842638738755) / factorial( 7 );
vec2 v8 = vec2(102.080678895964936714,-66.6069917817762586765) / factorial( 8 );
vec2 v9 = vec2(-332.325483007947923397,-622.346036137187638815) / factorial( 9 );
vec2 v10 = vec2(-3596.49776230101133478,1735.73201108429020678) / factorial( 10 );
vec2 v11 = vec2(10267.5109762286028854,18976.000672947790008) / factorial( 11 );
vec2 v12 = vec2(76508.9548940019594738,-74965.2025989268877311) / factorial( 12 );
vec2 v13 = vec2(-696929.607454764074646,37941.5458657158742426) / factorial( 13 );
vec2 v14 = vec2(6550459.66050149407238,7715864.13740421738476) / factorial( 14 );
vec2 v15 = vec2(92272836.4024868607521,-117377123.745682314038) / factorial( 15 );
vec2 v16 = vec2(-1651062067.99251270294,-1113389060.68487739563) / factorial( 16 );
vec2 v17 = vec2(-12989368634.8804683685,21284867370.19348526) / factorial( 17 );
vec2 v18 = vec2(264179424057.504241943,140322602682.840362549) / factorial( 18 );
vec2 v19 = vec2(1281835054287.16699219,-3228149057210.21630859) / factorial( 19 );
vec2 v20 = vec2(-39123975489921.8359375,-6617169790388.93847656) / factorial( 20 );

vec2 y( vec2 a , vec2 b ){
	
	return bin_p( a , b );

}

vec2 conjugado( vec2 a ){
	
	return vec2( a.x , -a.y );

}

vec2 f( vec2 z ){
	
	z -= alpha;

	return v0 + y( z , v1 ) + y( bin_pow( z , 2 ) , v2 ) + y( bin_pow( z , 3 ) , v3 ) + y( bin_pow( z , 4 ) , v4 )
		+ y( bin_pow( z , 5 ) , v5 ) + y( bin_pow( z , 6 ) , v6 ) + y( bin_pow( z , 7 ) , v7 ) + y( bin_pow( z , 8 ) , v8 )
		+ y( bin_pow( z , 9 ) , v9 ) + y( bin_pow( z , 10 ) , v10 ) + y( bin_pow( z , 11 ) , v11 ) + y( bin_pow( z , 12 ) , v12 )
		+ y( bin_pow( z , 13 ) , v13 ) + y( bin_pow( z , 14 ) , v14 ) + y( bin_pow( z , 15 ) , v15 )
		+ y( bin_pow( z , 16 ) , v16 ) + y( bin_pow( z , 17 ) , v17 ) + y( bin_pow( z , 18 ) , v18 )
		+ y( bin_pow( z , 19 ) , v19 ) + y( bin_pow( z , 20 ) , v20 );
}
*/
ortoper f( ortoper a ){
	
	return per( kper( e ) , a );

}

void main(){
	
	ortoper number = adjust( getCoords() );
	
	graph( to_orto( f( number ) ).z );
	
}
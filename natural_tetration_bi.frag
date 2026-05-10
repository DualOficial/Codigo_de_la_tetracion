#version 330 core
#ADD ORTOGONAL SHADER

//vec2

vec2 ntet_integer( vec2 x , int n ){
	
	return tetration_integer( vk( exp( 1.0 / exp( 1.0 ) ) ) , x , n );

}

vec2 ntet( vec2 x ){
	
	vec2 e = vk( exp( 1.0 ) );
	vec2 a = ntet_integer( vk( 1.0 ) , value );
	vec2 c = vk( 1.0 / ( exp( 1.0 ) * 2.0 ) );

	return ntet_integer( e - inverse( p( x , c ) + inverse( e - a ) ) , -int( value ) );
}

vec2 dn( vec2 x ){
	
	vec2 e = vk( exp( 1.0 ) );
	vec2 a = ntet_integer( vk( 1.0 ) , value );

	return ( inverse( e - ntet_integer( x , value ) ) - inverse( e - a ) ) * exp( 1.0 ) * 2;
}

vec2 f( vec2 x ){
	
	return dn( x );

}

void main(){
	
	ortoper number = adjust( getCoords() );
	
	graph( f( to_orto( number ).z ) );

}
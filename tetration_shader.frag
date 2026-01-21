#version 330 core
#ADD ORTOGONAL SHADER

// Esta tetración casi no tiene precisión

vec2 f( vec2 z ){
	
	vec2 final_exp = vk( 2.0 );
	vec2 height = z;

	vec2 v = vec2( 0.3181315052047641353121 , 1.33723570143068940890 );
	vec2 a = v - vk( 1.0 );
	vec2 b = tetration_integer( final_exp , -value ) - a;
	
	vec2 y = pow( v , height );
	vec2 x = ( d( y - vk( 1.0 ) , v - vk( 1.0 ) ) - y + vk( 1.0 ) ) / 2.0;

	return tetration_integer( pow( b , p( y , pow( b , x ) ) ) + a , value );
}

void main(){
	
	ortoper number = adjust( getCoords() );
	
	graph( f( to_orto( number ).z ) );
	
}

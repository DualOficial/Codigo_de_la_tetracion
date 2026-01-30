#include"definitions.hpp"

bool isnan( const complex_single & z ){
	
	return z.real() == std::numeric_limits< float_single >::quiet_NaN() || z.imag() == std::numeric_limits< float_single >::quiet_NaN();

}

bool isnan( const complex50 & z ){
	
	return z.real() == std::numeric_limits< float50 >::quiet_NaN() || z.imag() == std::numeric_limits< float50 >::quiet_NaN();

}

bool isnan( const complex100 & z ){
	
	return z.real() == std::numeric_limits< float100 >::quiet_NaN() || z.imag() == std::numeric_limits< float100 >::quiet_NaN();

}

template< typename T >
bool isinf( const complex_single & z ){
	
	return z.real() == std::numeric_limits< float_single >::infinity() || z.real() == -std::numeric_limits< float_single >::infinity()
	|| z.imag() == std::numeric_limits< float_single >::infinity() || z.imag() == -std::numeric_limits< float_single >::infinity();

}

bool isinf( const complex50 & z ){
	
	return z.real() == std::numeric_limits< float50 >::infinity() || z.real() == -std::numeric_limits< float50 >::infinity()
	|| z.imag() == std::numeric_limits< float50 >::infinity() || z.imag() == -std::numeric_limits< float50 >::infinity();

}

bool isinf( const complex100 & z ){
	
	return z.real() == std::numeric_limits< float100 >::infinity() || z.real() == -std::numeric_limits< float100 >::infinity()
	|| z.imag() == std::numeric_limits< float100 >::infinity() || z.imag() == -std::numeric_limits< float100 >::infinity();

}

string to_stringl( long double value ){
	
	stringstream ss;
	
	ss<<fixed<<setprecision( 21 )<<value;
	
	return ss.str();
}

string to_stringi( int value ){
	
	stringstream ss;
	
	ss<<fixed<<setprecision( 0 )<<value;
	
	return ss.str();
}

long double atol( const string & text ){
	
	char * extra;
	
	return strtold( text.c_str() , & extra );
}

namespace Colors{
	
	const Color Purple = Color( 128 , 0 , 255 );
	const Color Orange = Color( 255 , 128 , 0 );
	const Color SpringGreen = Color( 0 , 255 , 128 );
	const Color Chartreuse = Color( 128 , 255 , 0 );
	const Color BlueGreen = Color( 0 , 128 , 255 );
	const Color PinkRed = Color( 255 , 0 , 128 );

}

#include"definitions.hpp"

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
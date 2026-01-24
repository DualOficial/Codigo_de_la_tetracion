#include<limits>
#include"math.hpp"
#include<functional>

template< typename T >
const dual< T > dual< T >::e( T( 0 ) , T( 1 ) );

template< typename T >
dual< T > make_dual( const T & x , const T & y ){
	
	return dual< T >( x , y );
	
}

template< typename T >
dual< T > make_dual( const T & x ){
	
	return dual< T >( x );
	
}

template< typename T >
dual< T > inverse( const dual< T > & z ){
	
	if( z.r == T( 0 ) ){
		
		return dual< T >( std::numeric_limits< T >::quiet_NaN() , std::numeric_limits< T >::quiet_NaN() );
		
	}
	
	T inverse_r = T( 1 ) / z.r;
	
	return dual< T >( inverse_r , -z.i * inverse_r * inverse_r );
}

template< typename T >
T arg( const dual< T > & z ){
	
	return z.i / z.r;
	
}

template< typename T >
dual< T > polar( const T & real , const T & argument ){
	
	return dual< T >( real , real * argument );
	
}

template< typename T >
dual< T > exp( const dual< T > & z ){
	
	T exp_r = exp( z.r );
	
	return dual< T >( exp_r , exp_r * z.i );
}

template< typename T >
dual< T > abs( const dual< T > & z ){
	
	return dual< T >( abs( z.r ) , sign( z.r ) * z.i );
	
}

template< typename T >
dual< T > log( const dual< T > & z ){
	
	return dual< T >( log( z.r ) , arg( z ) );
	
}

template< typename T >
dual< T > pow( const dual< T > & z , const dual< T > & w ){
	
	return exp( w * log( z ) );
	
}

template< typename T >
dual< T > cos( const dual< T > & z ){
	
	return dual< T >( cos( z.r ) , -sin( z.r ) * z.i );
	
}

template< typename T >
dual< T > sin( const dual< T > & z ){
	
	return dual< T >( sin( z.r ) , cos( z.r ) * z.i );
	
}

template< typename T >
dual< T > tan( const dual< T > & z ){
	
	T cos_r = cos( z.r );
	
	return dual< T >( sin( z.r ) / cos_r , z.i / ( cos_r * cos_r ) );
}

template< typename T >
dual< T > sec( const dual< T > & z ){
	
	T sec_r = T( 1 ) / cos( z.r );
	
	return dual< T >( sec_r , sin( z.r ) * sec_r * sec_r * z.i );
}

template< typename T >
dual< T > csc( const dual< T > & z ){
	
	T csc_r = T( 1 ) / sin( z.r );
	
	return dual< T >( csc_r , -cos( z.r ) * csc_r * csc_r * z.i );
}

template< typename T >
dual< T > cot( const dual< T > & z ){
	
	T sin_r = sin( z.r );
	
	return dual< T >( cos( z.r ) / sin_r , -z.i / ( sin_r * sin_r ) );
}

template< typename T >
dual< T > sqrt( const dual< T > & z ){
	
	T sqrt_r = sqrt( z.r );
	
	return dual< T >( sqrt_r , z.i / ( T( 2 ) * sqrt_r ) );
}

template< typename T >
dual< T > cbrt( const dual< T > & z ){
	
	T cbrt_r = cbrt( z.r );
	
	return dual< T >( cbrt_r , z.i / ( T( 3 ) * cbrt_r * cbrt_r ) );
}

template< typename T >
dual< T > wlambert( const dual< T > & z ){
	
	if( z.r == T( 0 ) ){
		
		return dual< T >( T( 0 ) , z.i );
		
	}
	
	T wlambert_r = wlambert( z.r );
	
	return dual< T >( wlambert_r , z.i / ( z.r * ( T( 1 ) + T( 1 ) / wlambert_r ) ) );
}

template< typename T >
dual< T > wave( const dual< T > & z ){
	
	T wave_r = wave( z.r );
	
	return dual< T >( wave_r , z.i / ( z.r * ( T( 1 ) + log( wave_r ) ) ) );
}

template< typename T >
dual< T > asc( const dual< T > & z , const dual< T > & w ){
	
	return pow( z , pow( z , w ) );
	
}

template< typename T >
T anader( dual< T > ( * f )( dual< T > ) , const T & x ){
	
	return ( f( dual< T >( x , T( 1 ) ) ) - f( dual< T >( x , T( 0 ) ) ) ).i;
	
}

template< typename T >
dual< T >::dual() : r() , i(){
	
	//nothing
	
}

template< typename T >
dual< T >::dual( T real ) : r( real ) , i(){
	
	//nothing
	
}

template< typename T >
dual< T >::dual( T real , T infinitesimal ) : r( real ) , i( infinitesimal ){
	
	//nothing
	
}

template< typename T >
dual< T >::dual( const dual & other ) : r( other.r ) , i( other.i ){
	
	//nothing
	
}

template< typename T >
dual< T > dual< T >::operator-() const{
	
	return dual( -r , -i );
	
}

template< typename T >
dual< T > dual< T >::operator+( const dual & other ) const{
	
	return dual( r + other.r , i + other.i );
	
}

template< typename T >
dual< T > dual< T >::operator-( const dual & other ) const{
	
	return dual( r - other.r , i - other.i );
	
}

template< typename T >
dual< T > dual< T >::operator*( const dual & other ) const{
	
	return dual( r * other.r , r * other.i + i * other.r );
	
}

template< typename T >
dual< T > dual< T >::operator/( const dual & other ) const{
	
	return *this * inverse( other );
	
}

template< typename T >
dual< T > & dual< T >::operator+=( const dual & other ) const{
	
	return *this = *this + other;
	
}

template< typename T >
dual< T > & dual< T >::operator-=( const dual & other ) const{
	
	return *this = *this - other;
	
}

template< typename T >
dual< T > & dual< T >::operator*=( const dual & other ) const{
	
	return *this = *this * other;
	
}

template< typename T >
dual< T > & dual< T >::operator/=( const dual & other ) const{
	
	return *this = *this / other;

}

template< typename T >
bool dual< T >::operator==( const dual & other ) const{
	
	return r == other.r && i == other.i;

}

template< typename T >
bool dual< T >::operator!=( const dual & other ) const{
	
	return !( *this == other );

}

template< typename T >
dual< T > operator+( const T & first , const dual< T > & second ){
	
	return dual< T >( first + second.r , second.i );
	
}

template< typename T >
dual< T > operator-( const T & first , const dual< T > & second ){
	
	return dual< T >( first - second.r , -second.i );
	
}

template< typename T >
dual< T > operator*( const T & first , const dual< T > & second ){
	
	return dual< T >( first * second.r , first * second.i );
	
}

template< typename T >
dual< T > operator/( const T & first , const dual< T > & second ){
	
	return first * inverse( second );
	
}

template< typename T >
std::ostream & operator<<( std::ostream & o , const dual< T > & other ){
	
	return o<<"( "<<other.r<<" , "<<other.i<<" )";
	
}

template< typename T >
std::istream & operator>>( std::istream & i , dual< T > & other ){
	
	return i>>other.r>>other.i;
	
}

//Dual_Struct

template< typename T >
Dual_Struct< T >::Dual_Struct() : a() , b() , type(){}

template< typename T >
Dual_Struct< T >::Dual_Struct( any x , any y , bool t ) : a( x ) , b( y ) , type( t ){}

template< typename T >
Dual_Struct< T >::Dual_Struct( T x , unsigned int complexity ){
	
	if( complexity ){
		
		*this = dual_intern_value( x , complexity - 1 );

		return;
	}

	a = x;
	b = T();
	type = Value_Element;

}

template< typename T >
const T & Dual_Struct< T >::z() const{
	
	if( type == Value_Element ){
		
		return a;

	}

	return a.z();
}

template< typename T >
bool Dual_Struct< T >::operator==( const T & x ) const{
	
	if( type == Value_Element ){
		
		return any_cast< T >( a ) == x && any_cast< T >( b ) == T( 0 );

	}

	return any_cast< Dual_Struct< T > >( a ) == x && any_cast< Dual_Struct< T > >( b ) == T( 0 );
}

template< typename T >
bool Dual_Struct< T >::operator!=( const T & x ) const{
	
	return !( *this == x );

}

template< typename T >
bool Dual_Struct< T >::operator==( const Dual_Struct & d ) const{
	
	return a == d.a && b == d.b && type == d.type;

}

template< typename T >
bool Dual_Struct< T >::operator!=( const Dual_Struct & d ) const{
	
	return !( *this == d );

}

template< typename T >
Dual_Struct< T > & Dual_Struct< T >::operator=( const Dual_Struct & d ){
	
	a = d.a;
	b = d.b;
	type = d.type;

	return *this;
}

template< typename T >
Dual_Struct< T > Dual_Struct< T >:: operator+( const Dual_Struct & d ) const{
	
	if( type == Value_Element ){
		
		return Dual_Struct( any_cast< T >( a ) + any_cast< T >( d.a ) , any_cast< T >( b ) + any_cast< T >( d.b ) , Value_Element );

	}
	
	return Dual_Struct( any_cast< Dual_Struct >( a ) + any_cast< Dual_Struct >( d.a ) , any_cast< Dual_Struct >( b ) + any_cast< Dual_Struct >( d.b ) , Dual_Element );
}

template< typename T >
Dual_Struct< T > Dual_Struct< T >::operator-( const Dual_Struct & d ) const{
	
	if( type == Value_Element ){
		
		return Dual_Struct( any_cast< T >( a ) - any_cast< T >( d.a ) , any_cast< T >( b ) - any_cast< T >( d.b ) , Value_Element );

	}
	
	return Dual_Struct( any_cast< Dual_Struct >( a ) - any_cast< Dual_Struct >( d.a ) , any_cast< Dual_Struct >( b ) - any_cast< Dual_Struct >( d.b ) , Dual_Element );
}

template< typename T >
Dual_Struct< T > Dual_Struct< T >::operator-() const{
	
	if( type == Value_Element ){
		
		return Dual_Struct( -any_cast< T >( a ) , -any_cast< T >( b ) , Value_Element );

	}

	return Dual_Struct( -any_cast< Dual_Struct >( a ) , -any_cast< Dual_Struct >( b ) , Dual_Element );
}

template< typename T >
Dual_Struct< T > Dual_Struct< T >::operator*( const Dual_Struct & d ) const{
	
	if( type == Value_Element ){
		
		return Dual_Struct( any_cast< T >( a ) * any_cast< T >( d.a ) , any_cast< T >( a ) * any_cast< T >( d.b ) + any_cast< T >( b ) * any_cast< T >( d.a ) , Value_Element );

	}
	
	return Dual_Struct( any_cast< Dual_Struct >( a ) * any_cast< Dual_Struct >( d.a ) , any_cast< Dual_Struct >( a ) * any_cast< Dual_Struct >( d.b ) + any_cast< Dual_Struct >( b ) * any_cast< Dual_Struct >( d.a ) , Dual_Element );
}

template< typename T >
Dual_Struct< T > inverse( const Dual_Struct< T > & d ){
	
	if( d.type ){
		
		return Dual_Struct< T >( T( 1 ) / any_cast< Dual_Struct< T > >( d.a ) , -any_cast< Dual_Struct< T > >( d.b ) / ( any_cast< Dual_Struct< T > >( d.a ) * any_cast< Dual_Struct< T > >( d.a ) ) , d.type );

	}

	return Dual_Struct< T >( T( 1 ) / any_cast< T >( d.a ) , -any_cast< T >( d.b ) / ( any_cast< T >( d.a ) * any_cast< T >( d.a ) ) , d.type );
}

template< typename T >
Dual_Struct< T > Dual_Struct< T >::operator/( const Dual_Struct & d ) const{
	
	return *this * inverse( d );
	
}

template< typename T >
Dual_Struct< T > Dual_Struct< T >::operator*( const T & x ) const{
	
	if( type == Value_Element ){
		
		return Dual_Struct( any_cast< T >( a ) * x , any_cast< T >( b ) * x , Value_Element );

	}
	
	return Dual_Struct( any_cast< Dual_Struct >( a ) * x , any_cast< Dual_Struct >( b ) * x , Dual_Element );
}

template< typename T >
Dual_Struct< T > Dual_Struct< T >::operator/( const T & x ) const{
	
	if( type == Value_Element ){
		
		return Dual_Struct( any_cast< T >( a ) / x , any_cast< T >( b ) / x , Value_Element );

	}
	
	return Dual_Struct( any_cast< Dual_Struct >( a ) / x , any_cast< Dual_Struct >( b ) / x , Dual_Element );
}

template< typename T >
Dual_Struct< T > Dual_Struct< T >::operator+( const T & x ) const{
	
	if( type == Value_Element ){
		
		return Dual_Struct( any_cast< T >( a ) + x , any_cast< T >( b ) , Value_Element );

	}
	
	return Dual_Struct( any_cast< Dual_Struct >( a ) + x , any_cast< Dual_Struct >( b ) , Dual_Element );
}

template< typename T >
Dual_Struct< T > Dual_Struct< T >::operator-( const T & x ) const{
	
	if( type == Value_Element ){
		
		return Dual_Struct( any_cast< T >( a ) - x , any_cast< T >( b ) , Value_Element );

	}
	
	return Dual_Struct( any_cast< Dual_Struct >( a ) - x , any_cast< Dual_Struct >( b ) , Dual_Element );
}

template< typename T >
Dual_Struct< T > operator+( const T & x , const Dual_Struct< T > & d ){
	
	return d + x;

}

template< typename T >
Dual_Struct< T > operator-( const T & x , const Dual_Struct< T > & d ){
	
	return -d + x;

}

template< typename T >
Dual_Struct< T > operator/( const T & x , const Dual_Struct< T > & d ){
	
	return inverse( d ) * x;

}

template< typename T >
Dual_Struct< T > operator*( const T & x , const Dual_Struct< T > & d ){
	
	return d * x;

}

//functions

template< typename T >
Dual_Struct< T > exp( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		Dual_Struct< T > exp_r = exp( any_cast< Dual_Struct< T > >( z.a ) );
		
		return Dual_Struct< T >( exp_r , exp_r * any_cast< Dual_Struct< T > >( z.b ) , z.type );
	}

	T exp_r = exp( any_cast< T >( z.a ) );
	
	return Dual_Struct< T >( exp_r , exp_r * any_cast< T >( z.b ) , z.type );
}

template< typename T >
Dual_Struct< T > abs( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		return Dual_Struct< T >( abs( any_cast< Dual_Struct< T > >( z.a ) ) , sign( any_cast< Dual_Struct< T > >( z.a ) ) * any_cast< Dual_Struct< T > >( z.b ) , z.type );

	}

	return Dual_Struct< T >( abs( any_cast< T >( z.a ) ) , sign( any_cast< T >( z.a ) ) * any_cast< T >( z.b ) , z.type );
}

template< typename T >
Dual_Struct< T > log( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		return Dual_Struct< T >( log( any_cast< Dual_Struct< T > >( z.a ) ) , any_cast< Dual_Struct< T > >( z.b ) / any_cast< Dual_Struct< T > >( z.a ) , z.type );

	}
	
	return Dual_Struct< T >( log( any_cast< T >( z.a ) ) , any_cast< T >( z.b ) / any_cast< T >( z.a ) , z.type );
}

template< typename T >
Dual_Struct< T > pow( const Dual_Struct< T > & z , const Dual_Struct< T > & w ){
	
	return exp( w * log( z ) );
	
}

template< typename T >
Dual_Struct< T > cos( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		return Dual_Struct< T >( cos( any_cast< Dual_Struct< T > >( z.a ) ) , -any_cast< Dual_Struct< T > >( z.b ) * sin( any_cast< Dual_Struct< T > >( z.a ) ) , z.type );

	}

	return Dual_Struct< T >( cos( any_cast< T >( z.a ) ) , -any_cast< T >( z.b ) * sin( any_cast< T >( z.a ) ) , z.type );
}

template< typename T >
Dual_Struct< T > sin( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		return Dual_Struct< T >( sin( any_cast< Dual_Struct< T > >( z.a ) ) , any_cast< Dual_Struct< T > >( z.b ) * cos( any_cast< Dual_Struct< T > >( z.a ) ) , z.type );

	}

	return Dual_Struct< T >( sin( any_cast< T >( z.a ) ) , any_cast< T >( z.b ) * cos( any_cast< T >( z.a ) ) , z.type );
}

template< typename T >
Dual_Struct< T > tan( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		Dual_Struct< T > cos_a = cos( any_cast< Dual_Struct< T > >( z.a ) );

		return Dual_Struct< T >( sin( any_cast< Dual_Struct< T > >( z.a ) ) / cos_a , any_cast< Dual_Struct< T > >( z.b ) / ( cos_a * cos_a ) , z.type );
	}

	T cos_a = cos( any_cast< T >( z.a ) );

	return Dual_Struct< T >( sin( any_cast< T >( z.a ) ) / cos_a , any_cast< T >( z.b ) / ( cos_a * cos_a ) , z.type );
}

template< typename T >
Dual_Struct< T > sec( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		Dual_Struct< T > sec_a = inverse( cos( any_cast< Dual_Struct< T > >( z.a ) ) );
		
		return Dual_Struct< T >( sec_a , sin( any_cast< Dual_Struct< T > >( z.a ) ) * sec_a * sec_a * any_cast< Dual_Struct< T > >( z.b ) , z.type );
	}

	T sec_a = T( 1 ) / cos( any_cast< T >( z.a ) );
	
	return Dual_Struct< T >( sec_a , sin( any_cast< T >( z.a ) ) * sec_a * sec_a * any_cast< T >( z.b ) , z.type );
}

template< typename T >
Dual_Struct< T > csc( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		Dual_Struct< T > csc_a = inverse( sin( any_cast< Dual_Struct< T > >( z.a ) ) );
	
		return Dual_Struct< T >( csc_a , -cos( any_cast< Dual_Struct< T > >( z.a ) ) * csc_a * csc_a * any_cast< Dual_Struct< T > >( z.b ) , z.type );
	}

	T csc_a = T( 1 ) / sin( any_cast< T >( z.a ) );
	
	return Dual_Struct< T >( csc_a , -cos( any_cast< T >( z.a ) ) * csc_a * csc_a * any_cast< T >( z.b ) , z.type );
}

template< typename T >
Dual_Struct< T > cot( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		Dual_Struct< T > sin_a = sin( any_cast< Dual_Struct< T > >( z.a ) );
		
		return Dual_Struct< T >( cos( any_cast< Dual_Struct< T > >( z.a ) ) / sin_a , -any_cast< Dual_Struct< T > >( z.b ) / ( sin_a * sin_a ) , z.type );
	}

	T sin_a = sin( any_cast< T >( z.a ) );
	
	return Dual_Struct< T >( cos( any_cast< T >( z.a ) ) / sin_a , -any_cast< T >( z.b ) / ( sin_a * sin_a ) , z.type );
}

template< typename T >
Dual_Struct< T > sqrt( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		Dual_Struct< T > sqrt_a = sqrt( any_cast< Dual_Struct< T > >( z.a ) );
		
		return Dual_Struct< T >( sqrt_a , any_cast< Dual_Struct< T > >( z.b ) / ( sqrt_a * T( 2 ) ) , z.type );
	}

	T sqrt_a = sqrt( any_cast< T >( z.a ) );
	
	return Dual_Struct< T >( sqrt_a , any_cast< T >( z.b ) / ( sqrt_a * T( 2 ) ) , z.type );
}

template< typename T >
Dual_Struct< T > cbrt( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		Dual_Struct< T > cbrt_a = cbrt( any_cast< Dual_Struct< T > >( z.a ) );
		
		return Dual_Struct< T >( cbrt_a , any_cast< Dual_Struct< T > >( z.b ) / ( cbrt_a * cbrt_a * T( 3 ) ) , z.type );
	}

	Dual_Struct< T > cbrt_a = cbrt( any_cast< T >( z.a ) );
	
	return Dual_Struct< T >( cbrt_a , any_cast< T >( z.b ) / ( cbrt_a * cbrt_a * T( 3 ) ) , z.type );
}

template< typename T >
Dual_Struct< T > wlambert( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		if( any_cast< Dual_Struct< T > >( z.a ) == T( 0 ) ){
		
			return z;
		
		}
	
		Dual_Struct< T > wlambert_a = wlambert( any_cast< Dual_Struct< T > >( z.a ) );
	
		return Dual_Struct< T >( wlambert_a , any_cast< Dual_Struct< T > >( z.b ) / ( any_cast< Dual_Struct< T > >( z.a ) * ( T( 1 ) / wlambert_a + T( 1 ) ) ) , z.type );
	}

	if( any_cast< T >( z.a ) == T( 0 ) ){
		
		return z;
		
	}
	
	T wlambert_a = wlambert( any_cast< T >( z.a ) );
	
	return Dual_Struct< T >( wlambert_a , any_cast< T >( z.b ) / ( any_cast< T >( z.a ) * ( T( 1 ) / wlambert_a + T( 1 ) ) ) , z.type );
}

template< typename T >
Dual_Struct< T > wave( const Dual_Struct< T > & z ){
	
	if( z.type ){
		
		Dual_Struct< T > wave_a = wave( any_cast< Dual_Struct< T > >( z.a ) );
		
		return Dual_Struct< T >( wave_a , any_cast< Dual_Struct< T > >( z.b ) / ( any_cast< Dual_Struct< T > >( z.a ) * ( T( 1 ) + log( wave_a ) ) ) , z.type );
	}

	T wave_a = wave( any_cast< T >( z.a ) );
	
	return Dual_Struct< T >( wave_a , any_cast< T >( z.b ) / ( any_cast< T >( z.a ) * ( T( 1 ) + log( wave_a ) ) ) , z.type );
}

template< typename T >
Dual_Struct< T > asc( const Dual_Struct< T > & z , const Dual_Struct< T > & w ){
	
	return pow( z , pow( z , w ) );

}

template< typename T >
Dual_Struct< T > dual_intern_value( const T & x , unsigned int index ){
	
	if( index == 0 ){
		
		return Dual_Struct< T >( x , T() , false );

	}

	return Dual_Struct< T >( dual_intern_value( x , index - 1 ) , dual_intern_value( T() , index - 1 ) , true );
}

template< typename T >
function< Dual_Struct< T >( Dual_Struct< T > ) > derivate( function< Dual_Struct< T >( Dual_Struct< T > ) > f , unsigned int size ){
	
	if( size == 0 ){
		
		function< Dual_Struct< T >( Dual_Struct< T > ) > g = [ f ]( Dual_Struct< T > x ){
			
			return f( x );
			
		};

		return g;
	}

	if( size == 1 ){
		
		function< Dual_Struct< T >( Dual_Struct< T > ) > g = [ f ]( Dual_Struct< T > x ){
			
			return Dual_Struct< T >( ( f( Dual_Struct< T >( x.a , T( 1 ) , false ) ) - f( Dual_Struct< T >( x.a , T( 0 ) , false ) ) ).b , T( 0 ) , false );
			
		};

		return g;
	}

	function< Dual_Struct< T >( Dual_Struct< T > ) > g = [ f , size ]( Dual_Struct< T > x ){
		
		return any_cast< Dual_Struct< T > >(
		( f( Dual_Struct< T >( x , dual_intern_value( T( 1 ) , size - 2 ) , true ) ) -
		f( Dual_Struct< T >( x , dual_intern_value( T( 0 ) , size - 2 ) , true ) ) ).b );
		
	};

	return derivate( g , size - 1 );
}

template< typename T >
T derivate( function< Dual_Struct< T >( Dual_Struct< T > ) > f , const T & x , unsigned int index ){
	
	return any_cast< T >( derivate( f , index )( Dual_Struct< T >( x , T( 0 ) , false ) ).a );

}

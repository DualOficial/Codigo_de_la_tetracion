#include<limits>
#include"math.hpp"
#include<functional>

template< typename T >
const dual< T > dual< T >::e( T( 0 ) , T( 1 ) );

template< number_dual T >
real_type< T > Real( const T & z ){
	
	return z.intern_real();

}

template< number_dual T >
real_type< T > Imag( const T & z ){
	
	return z.intern_imag();

}

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
real_type< dual< T > > abs( const dual< T > & z ){
	
	return abs( z.intern_value() );
	
}

template< typename T >
dual< T > abs_d( const dual< T > & z ){
	
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
dual< T >::dual( const numeric_same< T > auto & a ) : r( a ) , i(){
	
	//nothing
	
}

template< typename T >
auto dual< T >::intern_value() const{
	
	if constexpr( is_dual< T > ) return r.intern_dual();

	return r;
}

template< typename T >
auto dual< T >::intern_real() const{
	
	return Real( intern_value() );

}

template< typename T >
auto dual< T >::intern_imag() const{
	
	return Imag( intern_value() );

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

template< unsigned int N , typename F >
auto derivate( F && f ) {
	
	if constexpr( N == 0 ){
		
		return std::forward< F >( f );

	}
	else{
		
		auto deriv = [ f = std::forward< F >( f ) ]( auto && v ) -> decltype( auto ){
			
			using T = std::decay_t< decltype( v ) >;

			return ( f( make_dual( v , T( 1 ) ) ) - f( make_dual( v , T( 0 ) ) ) ).i;
		};

		return derivate< N - 1 >( std::move( deriv ) );
	}
}

template< typename F >
auto derivate( F && f ){
	
	return derivate< 1 >( f );

}

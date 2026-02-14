#include<limits>
#include"math.hpp"
#include<functional>
#include "dual.hpp"

//complex type

template< typename T >
const dual_complex< T > dual_complex< T >::e( T( 0 ) , T( 1 ) );

template< typename T >
real_type< T > dual_complex< T >::real() const{
	
	return intern_value( *this ).real();

}

template< typename T >
real_type< T > dual_complex< T >::imag() const{
	
	return intern_value( *this ).imag();

}

template< no_dual_number T >
T intern_value( const T & d ){
	
	return d;

}

template< dual_number T >
auto intern_value( const T & d ){
	
	return intern_value( d.r );

}

template< typename T , bool is_complex >
dual< T , is_complex > make_dual( const T & x , const T & y ){
	
	return dual< T , is_complex >( x , y );
	
}

template< typename T , bool is_complex >
dual< T , is_complex > make_dual( const T & x ){
	
	return dual< T , is_complex >( x );
	
}

template< dual_number T >
T inverse( const T & z ){
	
	auto inverse_r = T::value_type( 1 ) / z.r;
	
	return T( inverse_r , -z.i * inverse_r * inverse_r );
}

template< dual_number T >
T::value_type arg( const T & z ){
	
	return z.i / z.r;
	
}

template< typename T >
dual_complex< T > polar( const T & real , const T & argument ){
	
	return dual_complex< T >( real , real * argument );
	
}

template< dual_number T >
T exp( const T & z ){
	
	auto exp_r = exp( z.r );
	
	return T( exp_r , exp_r * z.i );
}

template< dual_number T >
real_type< T > abs( const T & z ){
	
	return abs( intern_value( z ) );
	
}

template< dual_number T >
T abs_d( const T & z ){
	
	return T( abs( z.r ) , sign( z.r ) * z.i );
	
}

template< dual_number T >
T log( const T & z ){
	
	return T( log( z.r ) , arg( z ) );
	
}

template< dual_number T >
T pow( const T & z , const T & w ){
	
	return exp( w * log( z ) );
	
}

template< dual_number T >
T cos( const T & z ){
	
	return T( cos( z.r ) , -sin( z.r ) * z.i );
	
}

template< dual_number T >
T sin( const T & z ){
	
	return T( sin( z.r ) , cos( z.r ) * z.i );
	
}

template< dual_number T >
T tan( const T & z ){
	
	auto cos_r = cos( z.r );
	
	return T( sin( z.r ) / cos_r , z.i / ( cos_r * cos_r ) );
}

template< dual_number T >
T sec( const T & z ){
	
	auto sec_r = T::value_type( 1 ) / cos( z.r );
	
	return T( sec_r , sin( z.r ) * sec_r * sec_r * z.i );
}

template< dual_number T >
T csc( const T & z ){
	
	auto csc_r = T::value_type( 1 ) / sin( z.r );
	
	return T( csc_r , -cos( z.r ) * csc_r * csc_r * z.i );
}

template< dual_number T >
T cot( const T & z ){
	
	auto sin_r = sin( z.r );
	
	return T( cos( z.r ) / sin_r , -z.i / ( sin_r * sin_r ) );
}

template< dual_number T >
T sqrt( const T & z ){
	
	auto sqrt_r = sqrt( z.r );
	
	return T( sqrt_r , z.i / ( T::value_type( 2 ) * sqrt_r ) );
}

template< dual_number T >
T cbrt( const T & z ){
	
	auto cbrt_r = cbrt( z.r );
	
	return T( cbrt_r , z.i / ( T::value_type( 3 ) * cbrt_r * cbrt_r ) );
}

template< dual_number T >
T wlambert( const T & z ){
	
	if( z.r == T::value_type( 0 ) ){
		
		return T( T::value_type( 0 ) , z.i );
		
	}
	
	auto wlambert_r = wlambert( z.r );
	
	return T( wlambert_r , z.i / ( z.r * ( T::value_type( 1 ) + T::value_type( 1 ) / wlambert_r ) ) );
}

template< dual_number T >
T wave( const T & z ){
	
	auto wave_r = wave( z.r );
	
	return T( wave_r , z.i / ( z.r * ( T::value_type( 1 ) + log( wave_r ) ) ) );
}

template< typename T , typename F >
T anader( F f , const T & x ){
	
	return ( f( dual< T >( x , T( 1 ) ) ) - f( dual< T >( x , T( 0 ) ) ) ).i;
	
}

template< typename T >
dual_complex< T >::dual_complex() : r() , i(){
	
	//nothing
	
}

template< typename T >
dual_complex< T >::dual_complex( T real ) : r( real ) , i(){
	
	//nothing
	
}

template< typename T >
dual_complex< T >::dual_complex( T real , T infinitesimal ) : r( real ) , i( infinitesimal ){
	
	//nothing
	
}

template< typename T >
dual_complex< T >::dual_complex( const dual_complex & other ) : r( other.r ) , i( other.i ){
	
	//nothing
	
}

template< typename T >
dual_complex< T >::dual_complex( const math_number auto & a ) : r( a ) , i(){
	
	//nothing
	
}

template< typename T >
dual_complex< T > dual_complex< T >::operator-() const{
	
	return dual_complex( -r , -i );
	
}

template< typename T >
dual_complex< T > dual_complex< T >::operator+( const dual_complex & other ) const{
	
	return dual_complex( r + other.r , i + other.i );
	
}

template< typename T >
dual_complex< T > dual_complex< T >::operator-( const dual_complex & other ) const{
	
	return dual_complex( r - other.r , i - other.i );
	
}

template< typename T >
dual_complex< T > dual_complex< T >::operator*( const dual_complex & other ) const{
	
	return dual_complex( r * other.r , r * other.i + i * other.r );
	
}

template< typename T >
dual_complex< T > dual_complex< T >::operator/( const dual_complex & other ) const{
	
	return *this * inverse( other );
	
}

template< typename T >
dual_complex< T > & dual_complex< T >::operator+=( const dual_complex & other ) const{
	
	return *this = *this + other;
	
}

template< typename T >
dual_complex< T > & dual_complex< T >::operator-=( const dual_complex & other ) const{
	
	return *this = *this - other;
	
}

template< typename T >
dual_complex< T > & dual_complex< T >::operator*=( const dual_complex & other ) const{
	
	return *this = *this * other;
	
}

template< typename T >
dual_complex< T > & dual_complex< T >::operator/=( const dual_complex & other ) const{
	
	return *this = *this / other;

}

template< typename T >
bool dual_complex< T >::operator==( const dual_complex & other ) const{
	
	return r == other.r && i == other.i;

}

template< typename T >
bool dual_complex< T >::operator!=( const dual_complex & other ) const{
	
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
std::ostream & operator<<( std::ostream & o , const dual_complex< T > & other ){
	
	return o<<"( "<<other.r<<" , "<<other.i<<" )";
	
}

//no complex type

template< typename T >
const dual_real< T > dual_real< T >::e( T( 0 ) , T( 1 ) );

template< typename T >
dual_real< T > polar( const T & real , const T & argument ){
	
	return dual_real< T >( real , real * argument );
	
}

template< typename T >
dual_real< T >::dual_real() : r() , i(){
	
	//nothing
	
}

template< typename T >
dual_real< T >::dual_real( T real ) : r( real ) , i(){
	
	//nothing
	
}

template< typename T >
dual_real< T >::dual_real( T real , T infinitesimal ) : r( real ) , i( infinitesimal ){
	
	//nothing
	
}

template< typename T >
dual_real< T >::dual_real( const dual_real & other ) : r( other.r ) , i( other.i ){
	
	//nothing
	
}

template< typename T >
dual_real< T >::dual_real( const real_number auto & a ) : r( a ) , i(){
	
	//nothing
	
}

template< typename T >
dual_real< T > dual_real< T >::operator-() const{
	
	return dual_real( -r , -i );
	
}

template< typename T >
dual_real< T > dual_real< T >::operator+( const dual_real & other ) const{
	
	return dual_real( r + other.r , i + other.i );
	
}

template< typename T >
dual_real< T > dual_real< T >::operator-( const dual_real & other ) const{
	
	return dual_real( r - other.r , i - other.i );
	
}

template< typename T >
dual_real< T > dual_real< T >::operator*( const dual_real & other ) const{
	
	return dual_real( r * other.r , r * other.i + i * other.r );
	
}

template< typename T >
dual_real< T > dual_real< T >::operator/( const dual_real & other ) const{
	
	return *this * inverse( other );
	
}

template< typename T >
dual_real< T > & dual_real< T >::operator+=( const dual_real & other ) const{
	
	return *this = *this + other;
	
}

template< typename T >
dual_real< T > & dual_real< T >::operator-=( const dual_real & other ) const{
	
	return *this = *this - other;
	
}

template< typename T >
dual_real< T > & dual_real< T >::operator*=( const dual_real & other ) const{
	
	return *this = *this * other;
	
}

template< typename T >
dual_real< T > & dual_real< T >::operator/=( const dual_real & other ) const{
	
	return *this = *this / other;

}

template< typename T >
bool dual_real< T >::operator==( const dual_real & other ) const{
	
	return r == other.r && i == other.i;

}

template< typename T >
bool dual_real< T >::operator!=( const dual_real & other ) const{
	
	return !( *this == other );

}

template< typename T >
inline dual_real< T >::operator real_type< T >() const{
	
	return intern_value( *this );

}

template< typename T >
std::ostream & operator<<( std::ostream & o , const dual_real< T > & other ){
	
	return o<<"( "<<other.r<<" , "<<other.i<<" )";
	
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
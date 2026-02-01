#include<limits>
#include"math.hpp"
#include<functional>

template< typename T >
const dual< T > dual< T >::e( T( 0 ) , T( 1 ) );

template< no_number_dual T >
dual_intern_type< T > intern_value( const dual< T > & d ){
	
	return d.r;

}

template< number_dual T >
dual_intern_type< T > intern_value( const dual< T > & d ){
	
	return intern_value( d.r );

}

template< number_dual T >
real_type< T > Real( const T & z ){
	
	return Real( intern_value( z ) );

}

template< number_dual T >
real_type< T > Imag( const T & z ){
	
	return Imag( intern_value( z ) );

}

template< typename T >
dual< T > make_dual( const T & x , const T & y ){
	
	return dual< T >( x , y );
	
}

template< typename T >
dual< T > make_dual( const T & x ){
	
	return dual< T >( x );
	
}

template< number_dual T >
T inverse( const T & z ){
	
	if( z.r == T( 0 ) ){
		
		return T( std::numeric_limits< real_type< T > >::quiet_NaN() );
		
	}
	
	auto inverse_r = T::value_type( 1 ) / z.r;
	
	return T( inverse_r , -z.i * inverse_r * inverse_r );
}

template< number_dual T >
T::value_type arg( const T & z ){
	
	return z.i / z.r;
	
}

template< typename T >
dual< T > polar( const T & real , const T & argument ){
	
	return dual< T >( real , real * argument );
	
}

template< number_dual T >
T exp( const T & z ){
	
	auto exp_r = exp( z.r );
	
	return T( exp_r , exp_r * z.i );
}

template< number_dual T >
real_type< T > abs( const T & z ){
	
	return abs( intern_value( z ) );
	
}

template< number_dual T >
T abs_d( const T & z ){
	
	return T( abs( z.r ) , sign( z.r ) * z.i );
	
}

template< number_dual T >
T log( const T & z ){
	
	return T( log( z.r ) , arg( z ) );
	
}

template< number_dual T >
T pow( const T & z , const T & w ){
	
	return exp( w * log( z ) );
	
}

template< number_dual T >
T cos( const T & z ){
	
	return T( cos( z.r ) , -sin( z.r ) * z.i );
	
}

template< number_dual T >
T sin( const T & z ){
	
	return T( sin( z.r ) , cos( z.r ) * z.i );
	
}

template< number_dual T >
T tan( const T & z ){
	
	auto cos_r = cos( z.r );
	
	return T( sin( z.r ) / cos_r , z.i / ( cos_r * cos_r ) );
}

template< number_dual T >
T sec( const T & z ){
	
	auto sec_r = T( 1 ) / cos( z.r );
	
	return T( sec_r , sin( z.r ) * sec_r * sec_r * z.i );
}

template< number_dual T >
T csc( const T & z ){
	
	auto csc_r = T( 1 ) / sin( z.r );
	
	return T( csc_r , -cos( z.r ) * csc_r * csc_r * z.i );
}

template< number_dual T >
T cot( const T & z ){
	
	auto sin_r = sin( z.r );
	
	return T( cos( z.r ) / sin_r , -z.i / ( sin_r * sin_r ) );
}

template< number_dual T >
T sqrt( const T & z ){
	
	auto sqrt_r = sqrt( z.r );
	
	return T( sqrt_r , z.i / ( T( 2 ) * sqrt_r ) );
}

template< number_dual T >
T cbrt( const T & z ){
	
	auto cbrt_r = cbrt( z.r );
	
	return T( cbrt_r , z.i / ( T( 3 ) * cbrt_r * cbrt_r ) );
}

template< number_dual T >
T wlambert( const T & z ){
	
	if( z.r == T( 0 ) ){
		
		return T( T( 0 ) , z.i );
		
	}
	
	auto wlambert_r = wlambert( z.r );
	
	return T( wlambert_r , z.i / ( z.r * ( T( 1 ) + T( 1 ) / wlambert_r ) ) );
}

template< number_dual T >
T wave( const T & z ){
	
	auto wave_r = wave( z.r );
	
	return T( wave_r , z.i / ( z.r * ( T( 1 ) + log( wave_r ) ) ) );
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
template< typename U >
requires numeric_same< T , U >
dual< T >::dual( const U & a ) : r( a ) , i(){
	
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
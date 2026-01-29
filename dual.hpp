#pragma once

#include<iostream>
#include"definitions.hpp"
#include<concepts>

template< typename T >
class dual;

template< typename T >
inline constexpr bool is_dual_real = false;

template< typename T >
inline constexpr bool is_dual_real< dual< T > > = is_dual_real< T > || is_numeric< T >;

template< typename T >
inline constexpr bool is_dual = false;

template< typename T >
inline constexpr bool is_dual< dual< T > > = true;

template< typename T , typename U >
concept numeric_same = ( is_dual_real< T > && is_numeric< U > ) || ( !is_dual_real< T > && ( is_complex< U > || is_numeric< U > ) );

template< typename T >
concept number_dual = is_dual< T >;

template< typename T >
class dual{
public:
	
	using value_type = T;

	dual();
	dual( T real );
	dual( T real , T infinitesimal );
	dual( const dual & other );
	dual( const numeric_same< T > auto & a );
	
	dual operator-() const;
	dual operator+( const dual & other ) const;
	dual operator-( const dual & other ) const;
	dual operator*( const dual & other ) const;
	dual operator/( const dual & other ) const;
	dual & operator+=( const dual & other ) const;
	dual & operator-=( const dual & other ) const;
	dual & operator*=( const dual & other ) const;
	dual & operator/=( const dual & other ) const;
	
	bool operator==( const dual & other ) const;
	bool operator!=( const dual & other ) const;

	auto intern_value() const;
	auto intern_real() const;
	auto intern_imag() const;

	static const dual e;

	T r;
	T i;
	
};

template< typename T >
struct dual_intern_type_impl{
	
	using type = T;

};

template< typename T >
struct dual_intern_type_impl< dual< T > > {
	 using type = std::conditional_t< is_dual< typename dual< T >::value_type >,
		typename dual_intern_type_impl< typename dual< T >::value_type >::type,
		typename dual< T >::value_type >;
};

template< typename T >
using dual_intern_type = typename dual_intern_type_impl< T >::type;

template< typename T >
struct value_traits< dual< T > >{
	
	using real = typename real_type< typename dual_intern_type< dual< T > > >;
	
};

template< number_dual T >
real_type< T > Real( const T & z );

template< number_dual T >
real_type< T > Imag( const T & z );

template< typename T >
dual< T > operator+( const T & first , const dual< T > & second );

template< typename T >
dual< T > operator-( const T & first , const dual< T > & second );

template< typename T >
dual< T > operator*( const T & first , const dual< T > & second );

template< typename T >
dual< T > operator/( const T & first , const dual< T > & second );

typedef dual< float > fdual;
typedef dual< double > ddual;
typedef dual< long double > ldual;
typedef dual< fcomplex > fcdual;
typedef dual< dcomplex > dcdual;
typedef dual< lcomplex > lcdual;

//funciones

template< typename T >
dual< T > make_dual( const T & x , const T & y );

template< typename T >
dual< T > make_dual( const T & x );

template< typename T >
dual< T > inverse( const dual< T > & z );

template< typename T >
T arg( const dual< T > & z );

template< typename T >
dual< T > polar( const T & real , const T & argument );

template< typename T >
dual< T > exp( const dual< T > & z );

template< typename T >
real_type< dual< T > > abs( const dual< T > & z );

template< typename T >
dual< T > abs_d( const dual< T > & z );

template< typename T >
dual< T > log( const dual< T > & z );

template< typename T >
dual< T > pow( const dual< T > & z , const dual< T > & w );

template< typename T >
dual< T > cos( const dual< T > & z );

template< typename T >
dual< T > sin( const dual< T > & z );

template< typename T >
dual< T > tan( const dual< T > & z );

template< typename T >
dual< T > sec( const dual< T > & z );

template< typename T >
dual< T > csc( const dual< T > & z );

template< typename T >
dual< T > cot( const dual< T > & z );

template< typename T >
dual< T > sqrt( const dual< T > & z );

template< typename T >
dual< T > cbrt( const dual< T > & z );

template< typename T >
dual< T > wlambert( const dual< T > & z );

template< typename T >
dual< T > wave( const dual< T > & z );

template< typename T >
dual< T > asc( const dual< T > & z , const dual< T > & w );

template< typename T >
T anader( dual< T > ( * f )( dual< T > ) , const T & x );

//extra

template< typename T >
std::ostream & operator<<( std::ostream & o , const dual< T > & other );
template< typename T >
std::istream & operator>>( std::istream & i , dual< T > & other );

typedef dual< float > dualf;
typedef dual< double > duald;
typedef dual< long double > duall;

//Dual_Struct

template< unsigned int N , typename F >
auto derivate( F && f );

template< typename F >
auto derivate( F && f );

#include"dual.inl"

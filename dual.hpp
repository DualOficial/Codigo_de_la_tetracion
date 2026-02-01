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
concept no_number_dual = !is_dual< T >;

template< typename T >
class dual{
public:
	
	using value_type = T;

	dual();
	dual( T real );
	dual( T real , T infinitesimal );
	dual( const dual & other );

	template< typename U >
	requires numeric_same< T , U >
	dual( const U & a );
	
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

template< no_number_dual T >
dual_intern_type< T > intern_value( const dual< T > & d );

template< number_dual T >
dual_intern_type< T > intern_value( const dual< T > & d );

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

template< number_dual T >
T inverse( const T & z );

template< number_dual T >
T::value_type arg( const T & z );

template< typename T >
dual< T > polar( const T & real , const T & argument );

template< number_dual T >
T exp( const T & z );

template< number_dual T >
real_type< T > abs( const T & z );

template< number_dual T >
T abs_d( const T & z );

template< number_dual T >
T log( const T & z );

template< number_dual T >
T pow( const T & z , const T & w );

template< number_dual T >
T cos( const T & z );

template< number_dual T >
T sin( const T & z );

template< number_dual T >
T tan( const T & z );

template< number_dual T >
T sec( const T & z );

template< number_dual T >
T csc( const T & z );

template< number_dual T >
T cot( const T & z );

template< number_dual T >
T sqrt( const T & z );

template< number_dual T >
T cbrt( const T & z );

template< number_dual T >
T wlambert( const T & z );

template< number_dual T >
T wave( const T & z );

template< typename T >
T anader( dual< T > ( * f )( dual< T > ) , const T & x );

//extra

template< number_dual T >
std::ostream & operator<<( std::ostream & o , const T & other );

typedef dual< float > dualf;
typedef dual< double > duald;
typedef dual< long double > duall;

//Dual_Struct

template< unsigned int N , typename F >
auto derivate( F && f );

template< typename F >
auto derivate( F && f );

#include"dual.inl"
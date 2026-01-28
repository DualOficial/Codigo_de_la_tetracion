#pragma once

#include<iostream>
#include"definitions.hpp"
#include<concepts>

template< typename T >
class dual;

template< typename T >
inline constexpr bool is_boost_number = false;

template< unsigned Digits , backends::digit_base_type DigitBase , class Allocator , class Exponent , Exponent MinExponent , Exponent MaxExponent , expression_template_option ExpressionTemplates >
inline constexpr bool is_boost_number< number< cpp_bin_float< Digits , DigitBase , Allocator , Exponent , MinExponent , MaxExponent > , ExpressionTemplates > > = true;

template< typename T >
concept is_numeric = std::integral< T > || std::floating_point< T > || is_boost_number< T >;

template< typename T >
inline constexpr bool is_std_complex = false;

template< typename T >
inline constexpr bool is_std_complex< std::complex< T > > = true;

template< typename T >
inline constexpr bool is_boost_complex = false;

template< typename T , expression_template_option U >
inline constexpr bool is_boost_complex< number< complex_adaptor< T > , U > > = false;

template< typename T >
concept is_complex = is_std_complex< T > || is_boost_complex< T >;

template< typename T >
inline constexpr bool is_dual_real = false;

template< typename T >
inline constexpr bool is_dual_real< dual< T > > = is_dual_real< T > || is_numeric< T >;

template< typename T , typename U >
concept numeric_same = ( is_dual_real< T > && is_numeric< U > ) || ( !is_dual_real< T > && ( is_complex< U > || is_numeric< U > ) );

template< typename T >
class dual{
public:

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

	static const dual e;

	T r;
	T i;
	
};

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
dual< T > abs( const dual< T > & z );

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

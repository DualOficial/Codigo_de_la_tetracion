#pragma once

#include<iostream>
#include"definitions.hpp"

template< typename T >
class dual{
public:
	
	dual();
	dual( T real );
	dual( T real , T infinitesimal );
	dual( const dual & other );
	
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

#include"dual.inl"

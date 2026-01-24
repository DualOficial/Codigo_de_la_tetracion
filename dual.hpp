#pragma once

#include<iostream>
#include"definitions.hpp"
#include<any>

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

//Dual_Struct

//Si notan mucho any, es porque se me dificulto este metodo, puede que no sea el mas optimizado.

template< typename T >
struct Dual_Struct{
	
	enum Type{
		
		Value_Element,
		Dual_Element

	};

	Dual_Struct();
	Dual_Struct( any x , any y , bool t );
	Dual_Struct( T x , unsigned int complexity );

	const T & z() const;

	bool operator==( const T & x ) const;
	bool operator!=( const T & x ) const;
	bool operator==( const Dual_Struct & d ) const;
	bool operator!=( const Dual_Struct & d ) const;

	Dual_Struct & operator=( const Dual_Struct & d );
	Dual_Struct operator+( const Dual_Struct & d ) const;
	Dual_Struct operator-( const Dual_Struct & d ) const;
	Dual_Struct operator-() const;
	Dual_Struct operator*( const Dual_Struct & d ) const;

	Dual_Struct operator/( const Dual_Struct & d ) const;
	Dual_Struct operator*( const T & x ) const;
	Dual_Struct operator/( const T & x ) const;
	Dual_Struct operator+( const T & x ) const;
	Dual_Struct operator-( const T & x ) const;
	
	any a , b;
	bool type;

};

typedef Dual_Struct< float > fDual_Struct;
typedef Dual_Struct< double > dDual_Struct;
typedef Dual_Struct< long double > lDual_Struct;
typedef Dual_Struct< fcomplex > fcDual_Struct;
typedef Dual_Struct< dcomplex > dcDual_Struct;
typedef Dual_Struct< lcomplex > lcDual_Struct;

template< typename T >
Dual_Struct< T > operator+( const T & x , const Dual_Struct< T > & d );

template< typename T >
Dual_Struct< T > operator-( const T & x , const Dual_Struct< T > & d );

template< typename T >
Dual_Struct< T > operator/( const T & x , const Dual_Struct< T > & d );

template< typename T >
Dual_Struct< T > operator*( const T & x , const Dual_Struct< T > & d );

//functions

template< typename T >
Dual_Struct< T > inverse( const Dual_Struct< T > & d );

template< typename T >
Dual_Struct< T > exp( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > abs( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > log( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > pow( const Dual_Struct< T > & z , const Dual_Struct< T > & w );

template< typename T >
Dual_Struct< T > cos( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > sin( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > tan( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > sec( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > csc( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > cot( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > sqrt( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > cbrt( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > wlambert( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > wave( const Dual_Struct< T > & z );

template< typename T >
Dual_Struct< T > asc( const Dual_Struct< T > & z , const Dual_Struct< T > & w );

template< typename T >
Dual_Struct< T > dual_intern_value( const T & x , unsigned int index );

template< typename T >
function< Dual_Struct< T >( Dual_Struct< T > ) > derivate( function< Dual_Struct< T >( Dual_Struct< T > ) > f , unsigned int size );

template< typename T >
T derivate( function< Dual_Struct< T >( Dual_Struct< T > ) > f , const T & x , unsigned int index );

#include"dual.inl"

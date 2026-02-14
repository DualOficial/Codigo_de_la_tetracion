#pragma once

#include<iostream>
#include"definitions.hpp"
#include<concepts>

template< typename T >
class dual_real{
public:
	
	using value_type = T;

	dual_real();
	dual_real( T real );
	dual_real( T real , T infinitesimal );
	dual_real( const dual_real & other );
	dual_real( const real_number auto & a );
	
	dual_real operator-() const;
	dual_real operator+( const dual_real & other ) const;
	dual_real operator-( const dual_real & other ) const;
	dual_real operator*( const dual_real & other ) const;
	dual_real operator/( const dual_real & other ) const;
	dual_real & operator+=( const dual_real & other ) const;
	dual_real & operator-=( const dual_real & other ) const;
	dual_real & operator*=( const dual_real & other ) const;
	dual_real & operator/=( const dual_real & other ) const;
	
	bool operator==( const dual_real & other ) const;
	bool operator!=( const dual_real & other ) const;

	static const dual_real e;

	inline explicit operator real_type< T >() const;

	T r;
	T i;
	
};

template< typename T >
class dual_complex{
public:
	
	using value_type = T;

	dual_complex();
	dual_complex( T real );
	dual_complex( T real , T infinitesimal );
	dual_complex( const dual_complex & other );
	dual_complex( const math_number auto & a );

	real_type< T > real() const;
	real_type< T > imag() const;
	
	dual_complex operator-() const;
	dual_complex operator+( const dual_complex & other ) const;
	dual_complex operator-( const dual_complex & other ) const;
	dual_complex operator*( const dual_complex & other ) const;
	dual_complex operator/( const dual_complex & other ) const;
	dual_complex & operator+=( const dual_complex & other ) const;
	dual_complex & operator-=( const dual_complex & other ) const;
	dual_complex & operator*=( const dual_complex & other ) const;
	dual_complex & operator/=( const dual_complex & other ) const;
	
	bool operator==( const dual_complex & other ) const;
	bool operator!=( const dual_complex & other ) const;

	static const dual_complex e;

	T r;
	T i;
	
};

template< no_dual_number T >
T intern_value( const T & d );

template< dual_number T >
auto intern_value( const T & d );

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

template< typename T , bool is_complex = complex_type< T > >
dual< T , is_complex > make_dual( const T & x , const T & y );

template< typename T , bool is_complex = complex_type< T > >
dual< T , is_complex > make_dual( const T & x );

template< dual_number T >
T inverse( const T & z );

template< dual_number T >
T::value_type arg( const T & z );

template< typename T >
dual< T > polar( const T & real , const T & argument );

template< dual_number T >
T exp( const T & z );

template< dual_number T >
real_type< T > abs( const T & z );

template< dual_number T >
T abs_d( const T & z );

template< dual_number T >
T log( const T & z );

template< dual_number T >
T pow( const T & z , const T & w );

template< dual_number T >
T cos( const T & z );

template< dual_number T >
T sin( const T & z );

template< dual_number T >
T tan( const T & z );

template< dual_number T >
T sec( const T & z );

template< dual_number T >
T csc( const T & z );

template< dual_number T >
T cot( const T & z );

template< dual_number T >
T sqrt( const T & z );

template< dual_number T >
T cbrt( const T & z );

template< dual_number T >
T wlambert( const T & z );

template< dual_number T >
T wave( const T & z );

template< typename T , typename F >
T anader( F f , const T & x );

//extra

template< dual_number T >
std::ostream & operator<<( std::ostream & o , const T & other );

//Dual_Struct

template< unsigned int N , typename F >
auto derivate( F && f );

template< typename F >
auto derivate( F && f );

#include"dual.inl"
#pragma once

#include<cmath>
#include<limits>
#include<complex>

namespace math{
	
	template< typename T >
	class dual;
	
	template< typename T >
	T square( const T & x );
	
	template< typename T >
	T cube( const T & x );
	
	float sign( float x );
	float cos( float x );
	float sin( float x );
	float tan( float x );
	float sec( float x );
	float csc( float x );
	float cot( float x );
	float log( float x );
	float exp( float x );
	float sqrt( float x );
	float cbrt( float x );
	float abs( float x );
	float base_quiet_NaN( float x );
	
	double sign( double x );
	double cos( double x );
	double sin( double x );
	double tan( double x );
	double sec( double x );
	double csc( double x );
	double cot( double x );
	double log( double x );
	double exp( double x );
	double sqrt( double x );
	double cbrt( double x );
	double abs( double x );
	double base_quiet_NaN( double x );
	
	long double sign( long double x );
	long double cos( long double x );
	long double sin( long double x );
	long double tan( long double x );
	long double sec( long double x );
	long double csc( long double x );
	long double cot( long double x );
	long double log( long double x );
	long double exp( long double x );
	long double sqrt( long double x );
	long double cbrt( long double x );
	long double abs( long double x );
	long double base_quiet_NaN( long double x );
	
	template< typename T >
	std::complex< T > base_quiet_NaN( const std::complex< T > & x );
	
	template< typename T >
	dual< T > base_quiet_NaN( const dual< T > & x );
	
	template< typename T >
	T quiet_NaN();
	
}

#include"math.inl"

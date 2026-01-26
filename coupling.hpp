#pragma once

#include"dual.hpp"

template< typename T >
T coupling( const function< Dual_Struct< T >( Dual_Struct< T > , unsigned int index ) > & f , const T & x );

template< typename T >
T ascendant( const function< Dual_Struct< T >( Dual_Struct< T > , unsigned int index ) > & f , const T & x );

template< typename T >
function< T( T , unsigned int ) > to_recursive( const function< T( T ) > & f );

template< typename T >
function< T( T , int ) > to_recursive( const function< T( T ) > & f , const function< T( T ) > & inverse_f );

template< typename T >
class Permuted_Function{
public:
	
	template< typename F1 , typename F2 >
	Permuted_Function( const F1 & g , const F2 & inverse_g , const T & attractor , const T & d , const T & a , unsigned int iterations = 1000 );
	
	function< T( T , T ) > f;
	function< T( T ) > generator;
	function< T( T ) > generator_inverse;
	unsigned int complexity;
	T derivate1;
	T acceleration;
	T attract_point;
	
};

typedef Permuted_Function< float > fPermuted_Function;
typedef Permuted_Function< double > dPermuted_Function;
typedef Permuted_Function< long double > lPermuted_Function;
typedef Permuted_Function< fcomplex > fcPermuted_Function;
typedef Permuted_Function< dcomplex > dcPermuted_Function;
typedef Permuted_Function< lcomplex > lcPermuted_Function;

#include"coupling.inl"

#pragma once

#include"dual.hpp"
#include<optional>

template< typename F >
auto coupling( F && f );

template< typename F >
auto ascendant( F && f );

template< typename T >
function< T( T , unsigned int ) > to_recursive( const function< T( T ) > & f );

template< typename T >
function< T( T , int ) > to_recursive( const function< T( T ) > & f , const function< T( T ) > & inverse_f );

template< typename T , typename F >
T get_attractor( F && f , T test );

template< typename T , typename F >
T get_attractor( F && f , T test , unsigned int max_iteration );

//get_attractor limited

template< typename T , typename F >
T get_attractor_l( F && f , T test , real_type< T > epsilon );

template< typename T , typename F >
T get_attractor_l( F && f , T test , real_type< T > epsilon , unsigned int max_iteration );

template< typename U , typename V , typename T >
class Permuted_Function{
public:
	
	Permuted_Function( U g , V inverse_g , const T & attractor , const T & d , const T & a , unsigned int iterations = 1000 );
	Permuted_Function( U g , V inverse_g , const T & attractor , unsigned int iterations = 1000 );
	
	template< typename S >
	S operator()( S x , const S & y ) const;

	U generator;
	V generator_inverse;
	unsigned int complexity;
	T derivate1;
	T acceleration;
	T attract_point;
	
};

#include"coupling.inl"

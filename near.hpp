#pragma once

#include"definitions.hpp"
#include"successions.hpp"

//los polinomios de uribe, cumplen que m{ Us(x,n) } = k^s

template< typename T >
T delta_poly( T n , unsigned int k , unsigned int s );

template< typename T >
T delta_poly_div_factorial( T n , unsigned int k , unsigned int s );

template< typename T >
T sum_delta_stirling( T n , unsigned int k , unsigned int s );

template< typename T >
T uribe_coefficient( unsigned int k , unsigned int m , unsigned int s );

template< typename T >
T uribe( T x , T n , unsigned int k );

template< typename T >
T uribe( T x , unsigned int n , unsigned int k );

template< typename T >
T uribe2( T x , T n , unsigned int k );

template< typename T >
T uribe2( T x , unsigned int n , unsigned int k );

template< typename T >
T phi( T x , unsigned int n );

template< typename F >
auto phi_operator( F && f , unsigned int complexity = 150 );

template< typename F >
auto extensión( F && f , unsigned int complexity = 150 );

template< typename F >
auto Near( F && f , unsigned int complexity = 1000 );

template< typename F , typename T >
auto mello( F && f , unsigned int complexity = 1000 );

template< typename F , typename G , typename T >
T PolyTransform( F && f , G && t , T a , T b , unsigned int complexity = 150 );

#include"near.inl"
#pragma once

#include"definitions.hpp"

inline int perfact_complexity = 1000; //no soporta mucha presición

template< typename T >
T perfact_integer( T x , int n );

//permutación factorial

template< typename T >
T perfact( const T & x , const T & y );

template< typename T , typename F >
T sum( F f , T a , T b );

template< typename T , typename F >
T product( F f , T a , T b );

template< typename T , typename F >
T epsilon( F f , T x , T a , T b );

template< no_complex_type T , typename F >
T sum_integral( F f , const T & a , const T & b );

template< complex_type T , typename F >
T sum_integral( F f , const T & a , const T & b );

template< typename T , typename F >
T product_integral( F f , const T & a , const T & b );

template< typename T , typename F >
T epsilon_integral( F f , T x , const T & a , const T & b );

template< typename F >
auto product_derivate( F f );

template< typename F >
auto epsilon_derivate( F f );

#include"epsilon.inl"
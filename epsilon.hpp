#pragma once

extern int perfact_complexity; //no soporta mucha presición

template< typename T >
T perfact_integer( T x , int n );

//permutación factorial

template< typename T >
T perfact( const T & x , const T & y );

template< typename T , typename F >
T epsilon( F f , T x , T a , T b );

template< typename T , typename F >
T epsilon_integral( F f , T x , const T & a , const T & b , int complexity = 1000 );

#include"epsilon.inl"
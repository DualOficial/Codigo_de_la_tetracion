#pragma once

#include"definitions.hpp"

//Aqui casi todas las funciones son para reales o complejos, o sea( no duales, no ortogonales, etc. )

//wlambert

template< typename T >
T zexpz( T z );

template< typename T >
T zexpz_d( T z );

template< typename T >
T zexpz_dd( T z );

template< typename T >
T InitPoint( T z, int k );

extern int wlambert_complexity; //con 30 iteraciones ya es suficiente precisión

template< complex_number T >
T wlambert( const T & z , int k = 0 );

template< real_number T >
T wlambert( const T & z );

//gamma

template< real_number T >
T log_gamma( const T & x );

template< complex_number T >
T log_gamma( const T & z );

template< real_number T >
T gamma( const T & x );

template< complex_number T >
T gamma( const T & z );

//harmonic

template< real_number T >
T harmonic( const T & x );

template< complex_number T >
T harmonic( const T & z );

#include"complex_functions.inl"
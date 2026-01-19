#pragma once

#include"ortogonals.hpp"
#include"ortogonalper.hpp"

extern int permutation_complexity;

#define MIN_WAVE 0.692200627555346353865l
#define INVERSE_E 0.367879441171442321595l
#define ALPHA lcomplex( 0.318131505204764135313l , 1.337235701430689408901l )
#define M_U 4.91l
#define M_E 2.71828182845904523536l

//Funciones Reales o complejos

template< typename T >
T wave( const T & x );

template< typename T >
T asc( const T & x , const T & y );

float wlambert( float z );
double wlambert( double z );
long double wlambert( long double z );
float50 wlambert( float50 z );
float100 wlambert( float100 z );
float_single wlambert( float_single z );

//Funciones Ortogonales

template< typename T >
T riz( const T & a , const T & b );

template< typename T >
T asc( const T & a , const T & b );

template< typename T >
T perInteger( T x , int n );

template< typename T >
T per( T u , T v );

template< typename T >
T beta_tetration( T u , T v );

template< typename T >
T beta_tetration( T w );

template< typename T >
T F( T x );

template< typename T >
T riz( T x , T y );

template< typename T >
T riz( T x );

template< typename T >
T gen( T x , T y );

template< typename T >
T aproxF( T x );

template< typename T >
T aprox_per( T x );

template< typename T >
T F_derivate( T x );

//mala calidad
//Utiliza lagrange

long double lag_per( long double x );

/*En este comentario use tetración beta, por lo que no es realista:
e^e^...1/2 veces aproximadamente 2.08787135335467079851
e^e^...1/2 veces...^e aproximadamente 8.06772354070021379714
e^e^...1/2 veces...^2 aproximadamente 3.11005265674281204061
11/10/2025 por la noche*/

#include"permutation.inl"
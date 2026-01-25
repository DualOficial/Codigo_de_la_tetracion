#pragma once

#include<functional>
#include"ortogonals.hpp"

//tetración mas y menos

extern int plus_tetration_complexity;
extern int minus_tetration_complexity;

template< typename T >
T expm( T x );

template< typename T >
T logm( T x );

template< typename T >
T expp( T x );

template< typename T >
T logp( T x );

template< typename T >
T mtetration_integer( T x , int n );

template< typename T >
T ptetration_integer( T x , int n );

template< typename T >
T mtetration( T x , T y );

template< typename T >
T ptetration( T x , T y );

//permutación special square

extern int hyper_square_complexity;

template< typename T >
T special_square( T x );

template< typename T >
T invert_square( T x );

template< typename T >
T hypersquare_integer( T x , int n );

template< typename T >
T hypersquare( T x , T y );

//tetración base e^1/e

extern int natural_tetration_complexity;

template< typename T >
T tetration_integer( T base , T final_exp , int height );

template< typename T >
T natural_tetration_integer( T final_exp , int height );

template< typename T >
T natural_tet( T x , T y );

template< typename T >
T natural_gen( T x , T y );

#include"other_permutations.inl"

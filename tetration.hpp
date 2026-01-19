#pragma once

#include"other_permutations.hpp"

template< typename T >
std::complex< T > alpha_tet( const std::complex< T > & base );

complex_single alpha_tet( const complex_single & base );
complex50 alpha_tet( const complex50 & base );
complex100 alpha_tet( const complex100 & base );

extern int tetration_complexity;
extern bool tetration_recursive;

template< typename T >
T tet( const T & base , const T & final_exp , T height , const T & v );

template< typename T >
T tet( const T & base , const T & final_exp , T height );

#include"tetration.inl"

#pragma once

#include"definitions.hpp"

template< typename T >
T stirling( unsigned int n , unsigned int k );

template< typename T >
T stirling2( unsigned int n , unsigned int k );

template< typename T >
T stirlinng_sign( unsigned int n , unsigned int k );

template< typename T >
T bernoulli( unsigned int n );

template< typename T >
T bell( unsigned int n );

template< typename T >
T bernoulli( unsigned int n , T x );

template< typename T >
T touchard( unsigned int n , T x );

//extension x^n = Sn(x), Sn es un polinomio de grado n

template< typename T >
T S( unsigned int n , T x );

#include"successions.inl"
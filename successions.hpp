#pragma once

#include"definitions.hpp"
#include"stieltjes.hpp"

int powm1( int k );

template< typename T >
T dpow( T x , T n );

template< typename T >
T dpow( T x , unsigned int n );

template< typename T >
T apow( T x , T n );

template< typename T >
T apow( T x , unsigned int n );

template< typename T >
T stieltjes( unsigned int n );

template< typename T >
T stirling( unsigned int n , unsigned int k );

template< typename T >
T stirling2( unsigned int n , unsigned int k );

template< typename T >
T stirling_sign( unsigned int n , unsigned int k );

template< typename T >
T bernoulli( unsigned int n );

template< typename T >
T bernoulli2( unsigned int n );

template< typename T >
T bell( unsigned int n );

template< typename T >
T bernoulli( unsigned int n , T x );

template< typename T >
T touchard( unsigned int n , T x );

template< typename T >
T bernoulli( T x );

//extension x^n = Sn(x), Sn es un polinomio de grado n

template< typename T >
T S( unsigned int n , T x );

#include"successions.inl"
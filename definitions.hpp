#pragma once

#include<iostream>
#include<iomanip>
#include<limits>
#include<boost/multiprecision/cpp_dec_float.hpp>
#include<boost/multiprecision/cpp_complex.hpp>
#include<boost/multiprecision/number.hpp>
#include<boost/math/constants/constants.hpp>

using namespace std;
using namespace boost::multiprecision;
using namespace boost::math;

typedef std::complex< float > fcomplex;
typedef std::complex< double > dcomplex;
typedef std::complex< long double > lcomplex;
typedef boost::multiprecision::cpp_complex_50 complex50;
typedef boost::multiprecision::cpp_bin_float_50 float50;
typedef boost::multiprecision::cpp_bin_float_single float_single;
typedef boost::multiprecision::cpp_complex_100 complex100;
typedef boost::multiprecision::cpp_bin_float_100 float100;
typedef boost::multiprecision::cpp_complex_single complex_single;

template< typename T >
T log( T base , T x );

template< typename T >
void adjust_precision();

string to_stringl( long double value );
string to_stringi( int value );
long double atol( const string & text );

#include"definitions.inl"
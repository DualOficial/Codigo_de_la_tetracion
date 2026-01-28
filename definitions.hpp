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
struct value_traits{
	
	using type = T;

};

template<>
struct value_traits< float >{
	
	using real = float;

};

template<>
struct value_traits< double >{
	
	using real = double;

};

template<>
struct value_traits< long double >{
	
	using real = long double;

};

template< typename T >
struct value_traits< std::complex< T > >{
	
	using real = T;

};

template< typename T , expression_template_option ExpressionTemplates >
struct value_traits< number< complex_adaptor< T > , ExpressionTemplates > >{
	
	using real = T;

};

template< unsigned Digits , backends::digit_base_type DigitBase , class Allocator , class Exponent , Exponent MinExponent , Exponent MaxExponent , expression_template_option ExpressionTemplates >
struct value_traits< number< cpp_bin_float< Digits , DigitBase , Allocator , Exponent , MinExponent , MaxExponent > , ExpressionTemplates > >{
	
	using real = cpp_bin_float< Digits , DigitBase , Allocator , Exponent , MinExponent , MaxExponent >;

};

template< typename T >
using real_type = value_traits< T >::real;

template< typename T >
T csc( const T & z );

template< typename T >
T sec( const T & z );

template< typename T >
T cot( const T & z );

template< typename T >
T sign( T z );

template< typename T >
T infinity_proj( T z );

template< typename T >
T inverse_proj( T z );

template< typename T >
bool isnan( const std::complex< T > & z );

template< typename T >
bool isnan( const complex100 & z );

template< typename T >
bool isinf( const std::complex< T > & z );

bool isinf( const complex_single & z );
bool isinf( const complex50 & z );
bool isinf( const complex100 & z );

template< typename T >
T log( T base , T x );

template< typename T >
void adjust_precision();

string to_stringl( long double value );
string to_stringi( int value );
long double atol( const string & text );

#include"definitions.inl"

#pragma once

#include<iostream>
#include<iomanip>
#include<limits>
#include<boost/multiprecision/cpp_dec_float.hpp>
#include<boost/multiprecision/cpp_complex.hpp>
#include<boost/multiprecision/number.hpp>
#include<boost/math/constants/constants.hpp>
#include<SFML/Graphics/Color.hpp>

using namespace std;
using namespace sf;
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
struct real_traits{
	
	using type = T;

};

template<>
struct real_traits< float >{
	
	using type = float;

};

template<>
struct real_traits< double >{
	
	using type = double;

};

template<>
struct real_traits< long double >{
	
	using type = long double;

};

template< typename T >
struct real_traits< std::complex< T > >{
	
	using type = T;

};

template< typename T , expression_template_option ExpressionTemplates >
struct real_traits< number< complex_adaptor< T > , ExpressionTemplates > >{
	
	using type = T;

};

template< unsigned Digits , backends::digit_base_type DigitBase , class Allocator , class Exponent , Exponent MinExponent , Exponent MaxExponent , expression_template_option ExpressionTemplates >
struct real_traits< number< cpp_bin_float< Digits , DigitBase , Allocator , Exponent , MinExponent , MaxExponent > , ExpressionTemplates > >{
	
	using type = cpp_bin_float< Digits , DigitBase , Allocator , Exponent , MinExponent , MaxExponent >;

};

template< typename T >
using real_type = real_traits< T >::type;

//init traits

//real numbers

template< typename T >
inline constexpr bool boost_real_impl = false;

template< unsigned Digits , backends::digit_base_type DigitBase , class Allocator , class Exponent , Exponent MinExponent , Exponent MaxExponent , expression_template_option ExpressionTemplates >
inline constexpr bool boost_real_impl< number< cpp_bin_float< Digits , DigitBase , Allocator , Exponent , MinExponent , MaxExponent > , ExpressionTemplates > > = true;

template< typename T >
concept boost_real = boost_real_impl< T >;

template< typename T >
concept basic_real = std::integral< T > || std::floating_point< T >;

template< typename T >
concept real_number = boost_real< T > || basic_real< T >;

//complex numbers

template< typename T >
inline constexpr bool basic_complex_impl = false;

template< typename T >
inline constexpr bool basic_complex_impl< std::complex< T > > = true;

template< typename T >
concept basic_complex = basic_complex_impl< T >;

template< typename T >
inline constexpr bool boost_complex_impl = false;

template< typename T , expression_template_option U >
inline constexpr bool boost_complex_impl< number< complex_adaptor< T > , U > > = false;

template< typename T >
concept boost_complex = boost_complex_impl< T >;

template< typename T >
concept complex_number = basic_complex< T > || boost_complex< T >;

template< typename T >
concept math_number = real_number< T > || complex_number< T >;

//types

template< typename T >
concept complex_type = requires( T t ){
	
	{ t.real() } -> std::convertible_to< real_type< T > >;
	{ t.imag() } -> std::convertible_to< real_type< T > >;

};

template< typename T >
concept no_complex_type = !complex_type< T >;

//ortogonal traits

template< typename Complex >
class ortogonal;

template< typename Complex >
inline constexpr bool is_ortogonal = false;

template< typename Complex >
inline constexpr bool is_ortogonal< ortogonal< Complex > > = true;

template< typename T >
concept number_ortogonal = is_ortogonal< T >;

template< typename T >
concept no_ortogonal = !is_ortogonal< T >;

template< typename T >
struct real_traits< ortogonal< T > >{
	
	using type = real_type< T >;

};

//ortogonal per traits

template< typename Complex >
class ortogonalper;

template< typename T >
struct real_traits< ortogonalper< T > >{
	
	using type = real_type< T >;

};

template< typename Complex >
inline constexpr bool is_ortogonalper = false;

template< typename Complex >
inline constexpr bool is_ortogonalper< ortogonalper< Complex > > = true;

template< typename T >
concept number_ortoper = is_ortogonalper< T >;

template< typename T >
concept no_ortoper = !is_ortogonalper< T >;

//dual traits

template< typename T >
class dual_real;

template< typename T >
class dual_complex;

template< typename T , bool is_complex = complex_type< T > >
using dual = std::conditional_t< is_complex , dual_complex< T > , dual_real< T > >;

template< typename T >
inline constexpr bool dual_real_number_impl = false;

template< typename T >
inline constexpr bool dual_real_number_impl< dual_real< T > > = true;

template< typename T >
inline constexpr bool dual_complex_number_impl = false;

template< typename T >
inline constexpr bool dual_complex_number_impl< dual_complex< T > > = true;

template< typename T >
concept dual_real_number = dual_real_number_impl< T >;

template< typename T >
concept dual_complex_number = dual_complex_number_impl< T >;

template< typename T >
concept dual_number = dual_real_number< T > || dual_complex_number< T >;

template< typename T >
concept no_dual_number = !dual_number< T >;

//dual intern types

template< typename T >
struct dual_real_intern_type_impl{
	
	using type = T;

};

template< typename T >
struct dual_real_intern_type_impl< dual_real< T > > {
	
	using type = std::conditional_t< dual_real_number< typename dual_real< T >::value_type >,
		typename dual_real_intern_type_impl< typename dual_real< T >::value_type >::type,
		typename dual_real< T >::value_type >;

};

template< typename T >
using dual_real_intern_type = typename dual_real_intern_type_impl< T >::type;

template< typename T >
struct dual_complex_intern_type_impl{
	
	using type = T;

};

template< typename T >
struct dual_complex_intern_type_impl< dual_complex< T > > {
	
	using type = std::conditional_t< dual_complex_number< typename dual_complex< T >::value_type >,
		typename dual_complex_intern_type_impl< typename dual_complex< T >::value_type >::type,
		typename dual_complex< T >::value_type >;

};

template< typename T >
using dual_complex_intern_type = typename dual_complex_intern_type_impl< T >::type;

template< typename T >
using dual_intern_type = conditional< complex_type< T > , dual_complex_intern_type< T > ,
dual_real_intern_type< T > >;

template< typename T >
struct real_traits< dual_real< T > >{
	
	using type = typename dual_real_intern_type< dual_real< T > >;
	
};

template< typename T >
struct real_traits< dual_complex< T > >{
	
	using type = typename real_type< typename dual_complex_intern_type< dual_complex< T > > >;
	
};

//end traits

template< typename T >
real_type< T > Real( const T & z );

template< complex_type T >
real_type< T > Real( const T & z );

template< typename T >
real_type< T > Imag( const T & z );

template< complex_type T >
real_type< T > Imag( const T & z );

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

template< complex_number T >
bool isnan( const T & z );

template< complex_number T >
bool isinf( const T & z );

template< typename T >
T log( T base , T x );

template< typename T >
void adjust_precision();

string to_stringl( long double value );
string to_stringi( int value );
long double atold( const string & text );

namespace Colors{
	
	constexpr Color Purple = Color( 128 , 0 , 255 );
	constexpr Color Orange = Color( 255 , 128 , 0 );
	constexpr Color SpringGreen = Color( 0 , 255 , 128 );
	constexpr Color Chartreuse = Color( 128 , 255 , 0 );
	constexpr Color BlueGreen = Color( 0 , 128 , 255 );
	constexpr Color PinkRed = Color( 255 , 0 , 128 );

}

#include"definitions.inl"

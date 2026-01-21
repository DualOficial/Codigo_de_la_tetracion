#pragma once

#include"other_permutations.hpp"
#include<vector>
#include<map>

//Alpha Derivates Algorithm

struct Product{
	
	Product();

	void insert( unsigned int index , unsigned int power );

	map< unsigned int , unsigned int > elements;
	unsigned int constant;
};

struct Sum{
	
	Sum();
	
	void insert( const Product & product );

	vector< Product > products;
};

Sum Derivate( const Sum & sum );

template< typename T >
struct Formula{
	
	Formula();

	Formula< T > & operator=( const Formula< T > & other );

	void insert( unsigned int n , const T & constant );

	map< unsigned int , T > monomials;

};

template< typename T >
Formula< T > operator+( Formula< T > first , const Formula< T > & second );

template< typename T >
Formula< T > & operator+=( Formula< T > & first , const Formula< T > & second );

template< typename T >
Formula< T > operator*( const Formula< T > first , const Formula< T > & second );

template< typename T >
Formula< T > & operator*=( Formula< T > & first , const Formula< T > & second );

template< typename T >
Formula< T > pow( const Formula< T > & f , unsigned int n );

template< typename T >
Formula< T > Simplify( const Formula< T > & formula );

template< typename T >
T Compute( const Formula< T > & formula , const T & accelo , const T & base , const T & alpha_value );

template< typename T >
T Compute( const Formula< T > & formula , const T & accelo , const T & alpha_value );

template< typename T >
Formula< T > Extension( Formula< T > formula , const T & base , const T & alpha_value );

template< typename T >
Formula< T > Resolve( const Sum & sum , const vector< Formula< T > > & prev_formulas , const T & base , const T & alpha_value );

template< typename T >
Formula< T > Extension( Formula< T > formula , const T & alpha_value );

template< typename T >
Formula< T > Resolve( const Sum & sum , const vector< Formula< T > > & prev_formulas , const T & alpha_value );

void Print( const Sum & sum );

typedef Formula< fcomplex > fFormula;
typedef Formula< dcomplex > dFormula;
typedef Formula< lcomplex > lFormula;
typedef Formula< complex_single > Formula_single;
typedef Formula< complex50 > Formula50;
typedef Formula< complex100 > Formula100;

//functions

template< typename T >
T alpha_tet( const T & base );

extern int tetration_complexity;
extern bool tetration_recursive;

template< typename T >
T tet( const T & base , const T & final_exp , T height , const T & v );

template< typename T >
T tet( const T & base , const T & final_exp , const T & height );

template< typename T >
T tet_e( const T & final_exp , T height , const T & v );

template< typename T >
T tet_e( const T & final_exp , const T & height );

template< typename T >
T tet_gen( const T & base , const T & final_exp , T result , const T & v );

template< typename T >
T tet_gen( const T & base , const T & final_exp , T result );

template< typename T >
T tet_gen_e( const T & final_exp , const T & result , const T & v );

template< typename T >
T tet_gen_e( const T & final_exp , const T & result );

//solo funciona con valores cercanos a alpha, donde e^alpha = alpha

template< typename T >
T exphalf( T z , const T & alpha_value );

template< typename T >
T exphalf( const T & z );

#include"tetration.inl"

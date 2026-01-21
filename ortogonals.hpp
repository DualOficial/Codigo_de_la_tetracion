#pragma once

#include"definitions.hpp"
#include<boost/math/special_functions.hpp>
#include<iostream>
#include<map>

#define M_PI 3.14159265358979323846l
#define M_TAU 6.28318530717958647692l
#define M_HALF_PI 1.57079632679489661923l

template< typename Real , typename Complex >
class ortogonal;

template< typename Real , typename Complex >
class ortogonalper;

template< typename Real , typename Complex , typename T >
void make_orto_base( ortogonal< Real , Complex > & w , unsigned int index , const T & t );

template< typename Real , typename Complex , typename T , typename... Args >
void make_orto_base( ortogonal< Real , Complex > & w , unsigned int index , const T & t , Args... args );

template< typename Real , typename Complex >
class ortogonal{
public:
	
	enum Type{
		
		Normal,
		Tetration,
		Sing
		
	};
	
	union Info{
		
		Info() : sing( -1 ){}
		Info( const Info & other ){
			
			*this = other;

		}

		Info & operator=( const Info & other ){
			
			memcpy( this , & other , sizeof( Info ) );

			return *this;
		}

		Complex z;
		int sing;
		
	};
	
	ortogonal();
	ortogonal( const Complex & z );
	ortogonal( Real r );
	ortogonal( Real r , Real i );
	ortogonal( const ortogonal & other );
	~ortogonal();
	
	ortogonal operator-() const;
	ortogonal operator+( const ortogonal & other ) const;
	ortogonal operator-( const ortogonal & other ) const;
	ortogonal operator*( const ortogonal & other ) const;
	ortogonal operator/( const ortogonal & other ) const;
	ortogonal & operator=( const ortogonal & other );
	ortogonal & operator+=( const ortogonal & other );
	ortogonal & operator-=( const ortogonal & other );
	ortogonal & operator*=( const ortogonal & other );
	ortogonal & operator/=( const ortogonal & other );
	
	bool operator==( const ortogonal & other ) const;
	bool operator!=( const ortogonal & other ) const;

	void add_branch( unsigned int index , int value );
	int branch( unsigned int index ) const;
	int complexity() const;
	
	int sing() const;
	const Type & getType() const;
	Real real() const;
	Real imag() const;
	Complex z() const;

	explicit operator Complex() const;

	static const ortogonal I;
	static const ortogonal NaN;
	
	static ortogonal make_sing( int k );
	bool overpased_sing() const;

	//No se pudo poner protected, por que cuando uso friends hay problemas de linkers

	Info info;
	Type type;
	map< unsigned int , int > branchs;
	
};

typedef ortogonal< float , fcomplex > fortogonal;
typedef ortogonal< double , dcomplex > dortogonal;
typedef ortogonal< long double , lcomplex > lortogonal;
typedef ortogonal< float50 , complex50 > ortogonal50;
typedef ortogonal< float100 , complex100 > ortogonal100;

template< typename Real , typename Complex , typename T >
void make_orto_base( ortogonal< Real , Complex > & w , unsigned int index , const T & t ){
	
	w.add_branch( index , t );
	index++;
	
}

template< typename Real , typename Complex , typename T , typename... Args >
void make_orto_base( ortogonal< Real , Complex > & w , unsigned int index , const T & t , Args... args ){
	
	w.add_branch( index , t );
	index++;
	
	make_orto_base( w , index , args... );
	
}

template< typename T , typename... Args >
ortogonal< T , std::complex< T > > make_orto( T x , T y , Args... args ){
	
	ortogonal< T , std::complex< T > > result( x , y );
	
	unsigned int index = 0;
	
	make_orto_base( result , index , args... );
	
	return result;
}

template< typename T , typename... Args >
ortogonal< T , std::complex< T > > make_orto( const std::complex< T > & z , Args... args ){
	
	ortogonal< T , std::complex< T > > result( z );
	
	unsigned int index = 0;
	
	make_orto_base( result , index , args... );
	
	return result;
}

template< typename... Args >
ortogonal50 make_orto( float50 x , float50 y , Args... args ){
	
	ortogonal50 result( x , y );
	
	unsigned int index = 0;
	
	make_orto_base( result , index , args... );
	
	return result;
}

template< typename... Args >
ortogonal100 make_orto( float100 x , float50 y , Args... args ){
	
	ortogonal100 result( x , y );
	
	unsigned int index = 0;
	
	make_orto_base( result , index , args... );
	
	return result;
}

template< typename... Args >
ortogonal50 make_orto( const complex50 & z , Args... args ){
	
	ortogonal50 result( z );
	
	unsigned int index = 0;
	
	make_orto_base( result , index , args... );
	
	return result;
}

template< typename... Args >
complex100 make_orto( const complex100 & z , Args... args ){
	
	ortogonal100 result( z );
	
	unsigned int index = 0;
	
	make_orto_base( result , index , args... );
	
	return result;
}

template< typename T >
T value_tetration( int k );

template<>
float value_tetration( int k );

template<>
double value_tetration( int k );

template<>
long double value_tetration( int k );

template< typename T >
int is_sing( T z );

template<>
int is_sing( fcomplex z );

template<>
int is_sing( dcomplex z );

template<>
int is_sing( lcomplex z );

template< typename Real , typename Complex >
ortogonal< Real , Complex > kproduct( int n , ortogonal< Real , Complex > z , ortogonal< Real , Complex > w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > kinverse( int n , ortogonal< Real , Complex > w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > inverse( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > exp( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > log( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > pow( const ortogonal< Real , Complex > & u , const ortogonal< Real , Complex > & v );

template< typename Real , typename Complex >
ortogonal< Real , Complex > root( const ortogonal< Real , Complex > & u , const ortogonal< Real , Complex > & v );

template< typename Real , typename Complex >
ortogonal< Real , Complex > cos( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > sin( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > tan( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > sec( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > csc( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > cot( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > cosh( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > sinh( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > tanh( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > sech( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > csch( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > coth( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > sqrt( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > cbrt( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > collapse( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > collapse( const ortogonal< Real , Complex > & w , int level );

template< typename Real , typename Complex >
Real arg( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
Real abs( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > wlambert( const ortogonal< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonal< Real , Complex > wave( const ortogonal< Real , Complex > & w );

template< typename T >
T e_tetration_positive( T z , unsigned int n );

template< typename T >
T e_tetration_negative( T z , unsigned int n );

template< typename T >
T e_tetration_integer( T w , int n );

template< typename Real , typename Complex >
ortogonal< Real , Complex > e_tetration_positive( ortogonal< Real , Complex > w , unsigned int n );

template< typename Real , typename Complex >
ortogonal< Real , Complex > e_tetration_negative( ortogonal< Real , Complex > w , unsigned int n );

template< typename Real , typename Complex >
ortogonal< Real , Complex > e_tetration_integer( ortogonal< Real , Complex > w , int n );

template<>
float e_tetration_negative( float z , unsigned int n );

template<>
float e_tetration_positive( float z , unsigned int n );

template<>
long double e_tetration_negative( long double z , unsigned int n );

template<>
long double e_tetration_positive( long double z , unsigned int n );

template< typename T >
T branch( T angle );

template< typename T >
T collapse( T angle );

template< typename T >
T rebranch( T z1 , T z2 );

template< typename T >
T value_tetration( int k );

template< typename T >
int is_sing( T z );

template< typename T >
T zexpz( T z );

template< typename T >
T zexpz_d( T z );

template< typename T >
T zexpz_dd( T z );

template< typename T >
T InitPoint( T z, int k);

template< typename T >
T wlambert( T z , int k = 0 );

template< typename Real , typename Complex >
ostream & operator<<( ostream & o , const ortogonal< Real , Complex > & w );

ortogonal< long double , lcomplex > operator"" ol( long double x );
ortogonal< long double , lcomplex > operator"" oil( long double x );

#include"ortogonals.inl"

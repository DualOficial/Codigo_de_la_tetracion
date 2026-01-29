#pragma once

#include"definitions.hpp"
#include<boost/math/special_functions.hpp>
#include<iostream>
#include<map>

template< typename Complex >
class ortogonal;

template< typename Complex >
class ortogonalper;

template< typename Complex , typename T >
void make_orto_base( ortogonal< Complex > & w , unsigned int index , const T & t );

template< typename Complex , typename T , typename... Args >
void make_orto_base( ortogonal< Complex > & w , unsigned int index , const T & t , Args... args );

template< typename Complex >
class ortogonal{
public:
	
	using Real = typename real_type< Complex >;
	
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

template< typename T >
struct value_traits< ortogonal< T > >{
	
	using real = real_type< T >;

};

typedef ortogonal< fcomplex > fortogonal;
typedef ortogonal< dcomplex > dortogonal;
typedef ortogonal< lcomplex > lortogonal;
typedef ortogonal< complex50 > ortogonal50;
typedef ortogonal< complex100 > ortogonal100;

template< typename Complex , typename T >
void make_orto_base( ortogonal< Complex > & w , unsigned int index , const T & t ){
	
	w.add_branch( index , t );
	index++;
	
}

template< typename Complex , typename T , typename... Args >
void make_orto_base( ortogonal< Complex > & w , unsigned int index , const T & t , Args... args ){
	
	w.add_branch( index , t );
	index++;
	
	make_orto_base( w , index , args... );
	
}

template< typename T , typename... Args >
ortogonal< std::complex< T > > make_orto( T x , T y , Args... args ){
	
	ortogonal< std::complex< T > > result( x , y );
	
	unsigned int index = 0;
	
	make_orto_base( result , index , args... );
	
	return result;
}

template< typename T , typename... Args >
ortogonal< std::complex< T > > make_orto( const std::complex< T > & z , Args... args ){
	
	ortogonal< std::complex< T > > result( z );
	
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

template< typename Complex >
ortogonal< Complex > kproduct( int n , ortogonal< Complex > z , ortogonal< Complex > w );

template< typename Complex >
ortogonal< Complex > kinverse( int n , ortogonal< Complex > w );

template< typename Complex >
ortogonal< Complex > inverse( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > exp( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > log( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > pow( const ortogonal< Complex > & u , const ortogonal< Complex > & v );

template< typename Complex >
ortogonal< Complex > root( const ortogonal< Complex > & u , const ortogonal< Complex > & v );

template< typename Complex >
ortogonal< Complex > cos( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > sin( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > tan( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > sec( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > csc( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > cot( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > cosh( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > sinh( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > tanh( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > sech( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > csch( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > coth( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > sqrt( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > cbrt( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > collapse( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > collapse( const ortogonal< Complex > & w , int level );

template< typename Complex >
real_type< Complex > arg( const ortogonal< Complex > & w );

template< typename Complex >
real_type< Complex > abs( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > wlambert( const ortogonal< Complex > & w );

template< typename Complex >
ortogonal< Complex > wave( const ortogonal< Complex > & w );

template< typename T >
T e_tetration_positive( T z , unsigned int n );

template< typename T >
T e_tetration_negative( T z , unsigned int n );

template< typename T >
T e_tetration_integer( T w , int n );

template< typename Complex >
ortogonal< Complex > e_tetration_positive( ortogonal< Complex > w , unsigned int n );

template< typename Complex >
ortogonal< Complex > e_tetration_negative( ortogonal< Complex > w , unsigned int n );

template< typename Complex >
ortogonal< Complex > e_tetration_integer( ortogonal< Complex > w , int n );

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

extern int wlambert_complexity; //con 30 iteraciones ya es suficiente precisión

template< typename T >
T wlambert( T z , int k = 0 );

template< typename Complex >
ostream & operator<<( ostream & o , const ortogonal< Complex > & w );

ortogonal< lcomplex > operator"" ol( long double x );
ortogonal< lcomplex > operator"" oil( long double x );

#include"ortogonals.inl"

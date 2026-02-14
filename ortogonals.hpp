#pragma once

#include"definitions.hpp"
#include<boost/math/special_functions.hpp>
#include<iostream>
#include<map>

template< typename Complex , typename T >
void make_orto_base( ortogonal< Complex > & w , unsigned int index , const T & t );

template< typename Complex , typename T , typename... Args >
void make_orto_base( ortogonal< Complex > & w , unsigned int index , const T & t , Args... args );

template< typename Complex >
class ortogonal{
public:
	
	using ComplexType = Complex;
	using RealType = typename real_type< Complex >;
	
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
	ortogonal( RealType r );
	ortogonal( RealType r , RealType i );
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
	RealType real() const;
	RealType imag() const;
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

template< number_ortogonal T >
T kproduct( int n , T z , T w );

template< number_ortogonal T >
T kinverse( int n , T w );

template< number_ortogonal T >
T inverse( const T & w );

template< number_ortogonal T >
T exp( const T & w );

template< number_ortogonal T >
T log( const T & w );

template< number_ortogonal T >
T pow( const T & u , const T & v );

template< number_ortogonal T >
T root( const T & u , const T & v );

template< number_ortogonal T >
T cos( const T & w );

template< number_ortogonal T >
T sin( const T & w );

template< number_ortogonal T >
T tan( const T & w );

template< number_ortogonal T >
T sec( const T & w );

template< number_ortogonal T >
T csc( const T & w );

template< number_ortogonal T >
T cot( const T & w );

template< number_ortogonal T >
T cosh( const T & w );

template< number_ortogonal T >
T sinh( const T & w );

template< number_ortogonal T >
T tanh( const T & w );

template< number_ortogonal T >
T sech( const T & w );

template< number_ortogonal T >
T csch( const T & w );

template< number_ortogonal T >
T coth( const T & w );

template< number_ortogonal T >
T sqrt( const T & w );

template< number_ortogonal T >
T cbrt( const T & w );

template< number_ortogonal T >
T collapse( const T & w );

template< number_ortogonal T >
T collapse( const T & w , int level );

template< number_ortogonal T >
real_type< T > arg( const T & w );

template< number_ortogonal T >
real_type< T > abs( const T & w );

template< number_ortogonal T >
T wlambert( const T & w );

template< typename T >
T e_tetration_positive( T z , unsigned int n );

template< typename T >
T e_tetration_negative( T z , unsigned int n );

template< typename T >
T e_tetration_integer( T w , int n );

template< number_ortogonal T >
T e_tetration_positive( T w , unsigned int n );

template< number_ortogonal T >
T e_tetration_negative( T w , unsigned int n );

template< number_ortogonal T >
T e_tetration_integer( T w , int n );

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

template< number_ortogonal T >
ostream & operator<<( ostream & o , const T & w );

ortogonal< lcomplex > operator"" ol( long double x );
ortogonal< lcomplex > operator"" oil( long double x );

#include"ortogonals.inl"

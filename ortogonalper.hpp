#pragma once

#include"ortogonals.hpp"

template< typename Complex >
class ortogonalper;

template< typename Complex >
ortogonalper< Complex > make_orto_per( const ortogonal< Complex > & data , int perspective );

template< typename Complex >
class ortogonalper{
public:
	
	using Real = typename real_type< Complex >;
	using ortogonal = ortogonal< Complex >;
	
	ortogonalper();
	explicit ortogonalper( ortogonal u , int n = 0 );
	explicit ortogonalper( const Complex & z , int n = 0 );
	explicit ortogonalper( Real r , int n = 0 );
	~ortogonalper();

	ortogonalper & operator=( const ortogonalper & other );
	ortogonalper operator-() const;
	ortogonalper operator+( const ortogonalper & other ) const;
	ortogonalper operator-( const ortogonalper & other ) const;
	ortogonalper operator*( const ortogonalper & other ) const;
	ortogonalper operator/( const ortogonalper & other ) const;
	ortogonalper & operator+=( const ortogonalper & other );
	ortogonalper & operator-=( const ortogonalper & other );
	ortogonalper & operator*=( const ortogonalper & other );
	ortogonalper & operator/=( const ortogonalper & other );

	static const ortogonalper I;
	static const ortogonalper NaN;

	void set_perspective( int n );
	int get_perspective() const;

	ortogonalper change( int n ) const;
	const ortogonal & w() const;
	const ortogonal & w_relative() const;
	Complex z() const;
	Complex z_relative() const;
	int sing() const;
	int sing_relative() const;

	Real real() const;
	Real imag() const;
	Real real_relative() const;
	Real imag_relative() const;

	explicit operator Complex() const;
	explicit operator ortogonal() const{
		
		return w();

	}

	ortogonal data;
	int perspective;

};

template< typename T >
struct value_traits< ortogonalper< T > >{
	
	using real = real_type< T >;

};

template< typename Complex >
ortogonalper< Complex > kproduct( int n , ortogonalper< Complex > u , ortogonalper< Complex > v );

template< typename Complex >
ortogonalper< Complex > kinverse( int n , ortogonalper< Complex > w );

template< typename Complex >
ortogonalper< Complex > make_orto_per( const ortogonal< Complex > & data , int perspective );

typedef ortogonalper< fcomplex > fortogonalper;
typedef ortogonalper< dcomplex > dortogonalper;
typedef ortogonalper< lcomplex > lortogonalper;
typedef ortogonalper< complex50 > ortogonalper50;
typedef ortogonalper< complex100 > ortogonalper100;
typedef ortogonalper< complex_single > ortogonalper_single;

template< typename Complex >
ortogonalper< Complex > operator+( const Complex & z , const ortogonalper< Complex > & other );

template< typename Complex >
ortogonalper< Complex > operator-( const Complex & z , const ortogonalper< Complex > & other );

template< typename Complex >
ortogonalper< Complex > operator*( const Complex & z , const ortogonalper< Complex > & other );

template< typename Complex >
ortogonalper< Complex > operator/( const Complex & z , const ortogonalper< Complex > & other );

template< typename Complex >
ortogonalper< Complex > inverse( const ortogonalper< Complex > & w );

template< typename Complex >
ostream & operator<<( ostream & o , const ortogonalper< Complex > & a );

template< typename Complex >
ortogonalper< Complex > root( const ortogonalper< Complex > & u , const ortogonalper< Complex > & v );

template< typename Complex >
ortogonalper< Complex > cos( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > sin( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > tan( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > sec( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > csc( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > cot( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > cosh( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > sinh( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > tanh( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > sech( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > csch( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > coth( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > sqrt( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > cbrt( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > exp( const ortogonalper< Complex > & a );

template< typename Complex >
ortogonalper< Complex > log( const ortogonalper< Complex > & a );

template< typename Complex >
ortogonalper< Complex > pow( const ortogonalper< Complex > & a , const ortogonalper< Complex > & b );

template< typename Complex >
ortogonalper< Complex > wlambert( const ortogonalper< Complex > & w );

template< typename Complex >
ortogonalper< Complex > wave( const ortogonalper< Complex > & w );

template< typename Complex >
real_type< Complex > arg( const ortogonalper< Complex > & a );

template< typename Complex >
real_type< Complex > abs( const ortogonalper< Complex > & a );

#include"ortogonalper.inl"

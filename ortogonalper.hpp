#pragma once

#include"ortogonals.hpp"

template< typename Real , typename Complex >
class ortogonalper;

template< typename Real , typename Complex >
ortogonalper< Real , Complex > make_orto_per( const ortogonal< Real , Complex > & data , int perspective );

template< typename Real , typename Complex >
class ortogonalper{
public:
	
	typedef ortogonal< Real , Complex > ortogonal;
	
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

template< typename Real , typename Complex >
ortogonalper< Real , Complex > kproduct( int n , ortogonalper< Real , Complex > u , ortogonalper< Real , Complex > v );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > kinverse( int n , ortogonalper< Real , Complex > w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > make_orto_per( const ortogonal< Real , Complex > & data , int perspective );

typedef ortogonalper< float , fcomplex > fortogonalper;
typedef ortogonalper< double , dcomplex > dortogonalper;
typedef ortogonalper< long double , lcomplex > lortogonalper;
typedef ortogonalper< float50 , complex50 > ortogonalper50;
typedef ortogonalper< float100 , complex100 > ortogonalper100;
typedef ortogonalper< float_single , complex_single > ortogonalper_single;

template< typename Real , typename Complex >
ortogonalper< Real , Complex > operator+( const Complex & z , const ortogonalper< Real , Complex > & other );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > operator-( const Complex & z , const ortogonalper< Real , Complex > & other );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > operator*( const Complex & z , const ortogonalper< Real , Complex > & other );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > operator/( const Complex & z , const ortogonalper< Real , Complex > & other );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > inverse( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ostream & operator<<( ostream & o , const ortogonalper< Real , Complex > & a );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > root( const ortogonalper< Real , Complex > & u , const ortogonalper< Real , Complex > & v );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > cos( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > sin( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > tan( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > sec( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > csc( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > cot( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > cosh( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > sinh( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > tanh( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > sech( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > csch( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > coth( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > sqrt( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > cbrt( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > exp( const ortogonalper< Real , Complex > & a );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > log( const ortogonalper< Real , Complex > & a );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > pow( const ortogonalper< Real , Complex > & a , const ortogonalper< Real , Complex > & b );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > wlambert( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
ortogonalper< Real , Complex > wave( const ortogonalper< Real , Complex > & w );

template< typename Real , typename Complex >
Real arg( const ortogonalper< Real , Complex > & a );

template< typename Real , typename Complex >
Real abs( const ortogonalper< Real , Complex > & a );

#include"ortogonalper.inl"
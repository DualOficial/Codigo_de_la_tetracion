#pragma once

#include"ortogonals.hpp"

template< typename Complex >
class ortogonalper;

template< typename Complex >
ortogonalper< Complex > make_orto_per( const ortogonal< Complex > & data , int perspective );

template< typename Complex >
inline constexpr bool is_ortogonalper = false;

template< typename Complex >
inline constexpr bool is_ortogonalper< ortogonalper< Complex > > = true;

template< typename T >
concept number_ortoper = is_ortogonalper< T >;

template< typename T >
concept no_ortoper = !is_ortogonalper< T >;

template< typename Complex >
class ortogonalper{
public:
	
	using RealType = typename real_type< Complex >;
	using ComplexType = Complex;
	using OrtoType = ortogonal< Complex >;
	
	ortogonalper();
	explicit ortogonalper( OrtoType u , int n = 0 );
	explicit ortogonalper( const Complex & z , int n = 0 );
	explicit ortogonalper( RealType r , int n = 0 );
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
	const OrtoType & w() const;
	const OrtoType & w_relative() const;
	Complex z() const;
	Complex z_relative() const;
	int sing() const;
	int sing_relative() const;

	RealType real() const;
	RealType imag() const;
	RealType real_relative() const;
	RealType imag_relative() const;

	explicit operator Complex() const;
	explicit operator OrtoType() const{
		
		return w();

	}

	OrtoType data;
	int perspective;

};

template< typename T >
struct value_traits< ortogonalper< T > >{
	
	using real = real_type< T >;

};

template< number_ortoper T >
T kproduct( int n , T u , T v );

template< number_ortoper T >
T kinverse( int n , T w );

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

template< number_ortoper T >
T inverse( const T & w );

template< number_ortoper T >
ostream & operator<<( ostream & o , const T & a );

template< number_ortoper T >
T root( const T & u , const T & v );

template< number_ortoper T >
T cos( const T & w );

template< number_ortoper T >
T sin( const T & w );

template< number_ortoper T >
T tan( const T & w );

template< number_ortoper T >
T sec( const T & w );

template< number_ortoper T >
T csc( const T & w );

template< number_ortoper T >
T cot( const T & w );

template< number_ortoper T >
T cosh( const T & w );

template< number_ortoper T >
T sinh( const T & w );

template< number_ortoper T >
T tanh( const T & w );

template< number_ortoper T >
T sech( const T & w );

template< number_ortoper T >
T csch( const T & w );

template< number_ortoper T >
T coth( const T & w );

template< number_ortoper T >
T sqrt( const T & w );

template< number_ortoper T >
T cbrt( const T & w );

template< number_ortoper T >
T exp( const T & a );

template< number_ortoper T >
T log( const T & a );

template< number_ortoper T >
T pow( const T & a , const T & b );

template< number_ortoper T >
T wlambert( const T & w );

template< number_ortoper T >
T wave( const T & w );

template< number_ortoper T >
real_type< T > arg( const T & a );

template< number_ortoper T >
real_type< T > abs( const T & a );

#include"ortogonalper.inl"
#include"ortogonalper.hpp"

template< typename Real , typename Complex >
ortogonalper< Real , Complex > make_orto_per( const ortogonal< Real , Complex > & data , int perspective ){
	
	ortogonalper< Real , Complex > result;

	result.data = data;
	result.perspective = perspective;

	return result;
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex >::operator Complex() const{
	
	return z();

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex >::ortogonalper() : data() , perspective(){
	
	//nothing

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex >::ortogonalper( ortogonal u , int n ) : data( e_tetrationInteger< Real , Complex >( u , -n ) ) , perspective( n ){
	
	//nothing

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex >::ortogonalper( const Complex & u , int n ) : data( e_tetrationInteger< Real , Complex >( u , -n ) ) , perspective( n ){
	
	//nothing

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex >::ortogonalper( Real r , int n ) : data( e_tetrationInteger< Real , Complex >( r , -n ) ) , perspective( n ){
	
	//nothing

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex >::~ortogonalper(){
	
	//nothing

}

template< typename Real , typename Complex >
const ortogonalper< Real , Complex > ortogonalper< Real , Complex >::I = Complex( 0 , 1 );

template< typename Real , typename Complex >
const ortogonalper< Real , Complex > ortogonalper< Real , Complex >::NaN = Complex( std::numeric_limits< Real >::quiet_NaN() , std::numeric_limits< Real >::quiet_NaN() );

template< typename Real , typename Complex >
void ortogonalper< Real , Complex >::set_perspective( int n ){
	
	data = e_tetrationInteger< Real , Complex >( data , perspective - n );
	perspective = n;

}

template< typename Real , typename Complex >
int ortogonalper< Real , Complex >::get_perspective() const{
	
	return perspective;

}

template< typename Real , typename Complex >
const ortogonal< Real , Complex > & ortogonalper< Real , Complex >::w() const{
	
	return e_tetrationInteger< Real , Complex >( data , perspective );

}

template< typename Real , typename Complex >
const ortogonal< Real , Complex > & ortogonalper< Real , Complex >::w_relative() const{
	
	return data;

}

template< typename Real , typename Complex >
Complex ortogonalper< Real , Complex >::z() const{
	
	return e_tetrationInteger< Real , Complex >( data , perspective ).z();

}

template< typename Real , typename Complex >
Complex ortogonalper< Real , Complex >::z_relative() const{
	
	return data.z();

}

template< typename Real , typename Complex >
int ortogonalper< Real , Complex >::sing() const{
	
	return data.sing();

}

template< typename Real , typename Complex >
int ortogonalper< Real , Complex >::sing_relative() const{
	
	return data.sing() - perspective;

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > kproduct( int n , ortogonalper< Real , Complex > u , ortogonalper< Real , Complex > v ){
	
	if( u.perspective == v.perspective ){
		
		return make_orto_per( kproduct( n - u.perspective , u.data , v.data ) , u.perspective );
		
	}

	if( abs( u.perspective - n ) < abs( v.perspective - n ) ){
		
		v.set_perspective( u.perspective );

		return kproduct( n , u , v );
	}

	u.set_perspective( v.perspective );

	return kproduct< Real , Complex >( n , u , v );
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > kinverse( int n , ortogonalper< Real , Complex > w ){
	
	return make_orto_per( kinverse< Real , Complex >( n - w.perspective , w.data ) , w.perspective );

}

template< typename Real , typename Complex >
Real ortogonalper< Real , Complex >::real() const{
	
	return z().real();

}

template< typename Real , typename Complex >
Real ortogonalper< Real , Complex >::imag() const{
	
	return z().imag();

}

template< typename Real , typename Complex >
Real ortogonalper< Real , Complex >::real_relative() const{
	
	return data.real();

}

template< typename Real , typename Complex >
Real ortogonalper< Real , Complex >::imag_relative() const{
	
	return data.imag();

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > & ortogonalper< Real , Complex >::operator=( const ortogonalper & other ){
	
	perspective = other.perspective;
	data = other.data;

	return *this;
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > ortogonalper< Real , Complex >::operator+( const ortogonalper & other ) const{
	
	return kproduct< Real , Complex >( 0 , *this , other );

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > ortogonalper< Real , Complex >::operator-() const{
	
	return kinverse< Real , Complex >( 0 , *this );

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > inverse( const ortogonalper< Real , Complex > & w ){
	
	return kinverse< Real , Complex >( 1 , w );

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > ortogonalper< Real , Complex >::operator-( const ortogonalper & other ) const{
	
	return *this + -other;

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > ortogonalper< Real , Complex >::operator*( const ortogonalper & other ) const{
	
	return kproduct< Real , Complex >( 1 , *this , other );

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > ortogonalper< Real , Complex >::operator/( const ortogonalper & other ) const{
	
	return *this * inverse< Real , Complex >( other );

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > & ortogonalper< Real , Complex >::operator+=( const ortogonalper & other ){
	
	return *this = *this + other;

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > & ortogonalper< Real , Complex >::operator-=( const ortogonalper & other ){
	
	return *this = *this - other;

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > & ortogonalper< Real , Complex >::operator*=( const ortogonalper & other ){
	
	return *this = *this * other;

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > & ortogonalper< Real , Complex >::operator/=( const ortogonalper & other ){
	
	return *this = *this / other;

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > ortogonalper< Real , Complex >::change( int n ) const{
	
	ortogonalper result( *this );

	result.set_perspective( n );

	return result;
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > operator+( const Complex & z , const ortogonalper< Real , Complex > & other ){
	
	return ortogonalper( z ) + other;

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > operator-( const Complex & z , const ortogonalper< Real , Complex > & other ){
	
	return ortogonalper( z ) - other;

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > operator*( const Complex & z , const ortogonalper< Real , Complex > & other ){
	
	return ortogonalper( z ) * other;

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > operator/( const Complex & z , const ortogonalper< Real , Complex > & other ){
	
	return ortogonalper( z ) / other;
	
}

template< typename Real , typename Complex >
ostream & operator<<( ostream & o , const ortogonalper< Real , Complex > & a ){
	
	return o<<a.data<<" , perspective : "<<a.perspective;

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > exp( const ortogonalper< Real , Complex > & a ){
	
	return make_orto_per( exp< Real , Complex >( a.w_relative() ) , a.get_perspective() );

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > log( const ortogonalper< Real , Complex > & a ){
	
	return make_orto_per( log< Real , Complex >( a.w_relative() ) , a.get_perspective() );

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > pow( const ortogonalper< Real , Complex > & a , const ortogonalper< Real , Complex > & b ){
	
	if( a.get_perspective() == 1 && b.get_perspective() == 1 ){
		
		return make_orto_per( a.w_relative() * b.w() , 1 );

	}

	if( a.get_perspective() == 2 && b.get_perspective() == 2 ){
		
		return make_orto_per( a.w_relative() + exp( b.w_relative() ) , 2 );

	}

	return exp< Real , Complex >( log< Real , Complex >( b ) * a );
}

template< typename Real , typename Complex >
long double arg( const ortogonalper< Real , Complex > & a ){
	
	return arg< Real , Complex >( a.w() );

}

template< typename Real , typename Complex >
long double abs( const ortogonalper< Real , Complex > & a ){
	
	return abs< Real , Complex >( a.w() );

}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > cos( const ortogonalper< Real , Complex > & w ){
	
	return ( exp< Real , Complex >( w * ortogonalper< Real , Complex >::I ) + exp< Real , Complex >( -w * ortogonalper< Real , Complex >::I ) ) / Real( 2 );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > sin( const ortogonalper< Real , Complex > & w ){
	
	return ( exp< Real , Complex >( w * ortogonalper< Real , Complex >::I ) - exp< Real , Complex >( -w * ortogonalper< Real , Complex >::I ) ) / Complex( 0 , 2 );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > tan( const ortogonalper< Real , Complex > & w ){
	
	return sin< Real , Complex >( w ) / cos< Real , Complex >( w );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > sec( const ortogonalper< Real , Complex > & w ){
	
	return inverse< Real , Complex >( cos< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > csc( const ortogonalper< Real , Complex > & w ){
	
	return inverse< Real , Complex >( sin< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > cot( const ortogonalper< Real , Complex > & w ){
	
	return cos< Real , Complex >( w ) / sin< Real , Complex >( w );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > cosh( const ortogonalper< Real , Complex > & w ){
	
	return ( exp< Real , Complex >( w ) + exp< Real , Complex >( -w ) ) / Real( 2 );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > sinh( const ortogonalper< Real , Complex > & w ){
	
	return ( exp< Real , Complex >( w ) - exp< Real , Complex >( -w ) ) / Real( 2 );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > tanh( const ortogonalper< Real , Complex > & w ){
	
	return sinh< Real , Complex >( w ) / cosh< Real , Complex >( w );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > sech( const ortogonalper< Real , Complex > & w ){
	
	return inverse< Real , Complex >( cosh< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > csch( const ortogonalper< Real , Complex > & w ){
	
	return inverse< Real , Complex >( sinh< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > coth( const ortogonalper< Real , Complex > & w ){
	
	return inverse< Real , Complex >( tanh< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > sqrt( const ortogonalper< Real , Complex > & w ){
	
	return pow< Real , Complex >( w , Real( 0.5 ) );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > cbrt( const ortogonalper< Real , Complex > & w ){
	
	return pow< Real , Complex >( w , Real( 1 ) / 3 );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > root( const ortogonalper< Real , Complex > & u ,const ortogonalper< Real , Complex > & v ){
	
	return pow< Real , Complex >( u , inverse< Real , Complex >( v ) );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > wlambert( const ortogonalper< Real , Complex > & a ){
	
	return ortogonalper( wlambert( a.w() ) , a.get_perspective() );
	
}

template< typename Real , typename Complex >
ortogonalper< Real , Complex > wave( const ortogonalper< Real , Complex > & a ){
	
	return exp< Real , Complex >( wlambert< Real , Complex >( log< Real , Complex >( a ) ) );
	
}
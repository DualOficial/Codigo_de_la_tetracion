#include"ortogonalper.hpp"

template< typename Complex >
ortogonalper< Complex > make_orto_per( const ortogonal< Complex > & data , int perspective ){
	
	ortogonalper result;

	result.data = data;
	result.perspective = perspective;

	return result;
}

template< typename Complex >
ortogonalper< Complex >::operator Complex() const{
	
	return z();

}

template< typename Complex >
ortogonalper< Complex >::ortogonalper() : data() , perspective(){
	
	//nothing

}

template< typename Complex >
ortogonalper< Complex >::ortogonalper( ortogonalper< Complex >::ortogonal u , int n ) : data( e_tetration_integer< ortogonal >( u , -n ) ) , perspective( n ){
	
	//nothing

}

template< typename Complex >
ortogonalper< Complex >::ortogonalper( const Complex & u , int n ) : data( e_tetration_integer< ortogonal >( u , -n ) ) , perspective( n ){
	
	//nothing

}

template< typename Complex >
ortogonalper< Complex >::ortogonalper( Real r , int n ) : data( e_tetration_integer< ortogonal >( r , -n ) ) , perspective( n ){
	
	//nothing

}

template< typename Complex >
ortogonalper< Complex >::~ortogonalper(){
	
	//nothing

}

template< typename Complex >
const ortogonalper< Complex > ortogonalper< Complex >::I = Complex( 0 , 1 );

template< typename Complex >
const ortogonalper< Complex > ortogonalper< Complex >::NaN = Complex( std::numeric_limits< Real >::quiet_NaN() , std::numeric_limits< Real >::quiet_NaN() );

template< typename Complex >
void ortogonalper< Complex >::set_perspective( int n ){
	
	data = e_tetration_integer( data , perspective - n );
	perspective = n;

}

template< typename Complex >
int ortogonalper< Complex >::get_perspective() const{
	
	return perspective;

}

template< typename Complex >
const ortogonal< Complex > & ortogonalper< Complex >::w() const{
	
	return e_tetration_integer< ortogonal >( data , perspective );

}

template< typename Complex >
const ortogonal< Complex > & ortogonalper< Complex >::w_relative() const{
	
	return data;

}

template< typename Complex >
Complex ortogonalper< Complex >::z() const{
	
	return e_tetration_integer< ortogonal >( data , perspective ).z();

}

template< typename Complex >
Complex ortogonalper< Complex >::z_relative() const{
	
	return data.z();

}

template< typename Complex >
int ortogonalper< Complex >::sing() const{
	
	return data.sing();

}

template< typename Complex >
int ortogonalper< Complex >::sing_relative() const{
	
	return data.sing() - perspective;

}

template< typename Complex >
ortogonalper< Complex > kproduct( int n , ortogonalper< Complex > u , ortogonalper< Complex > v ){
	
	if( u.perspective == v.perspective ){
		
		return make_orto_per( kproduct( n - u.perspective , u.data , v.data ) , u.perspective );
		
	}

	if( abs( u.perspective - n ) < abs( v.perspective - n ) ){
		
		v.set_perspective( u.perspective );

		return kproduct( n , u , v );
	}

	u.set_perspective( v.perspective );

	return kproduct( n , u , v );
}

template< typename Complex >
ortogonalper< Complex > kinverse( int n , ortogonalper< Complex > w ){
	
	return make_orto_per( kinverse( n - w.perspective , w.data ) , w.perspective );

}

template< typename Complex >
ortogonalper< Complex >::Real ortogonalper< Complex >::real() const{
	
	return z().real();

}

template< typename Complex >
ortogonalper< Complex >::Real ortogonalper< Complex >::imag() const{
	
	return z().imag();

}

template< typename Complex >
ortogonalper< Complex >::Real ortogonalper< Complex >::real_relative() const{
	
	return data.real();

}

template< typename Complex >
ortogonalper< Complex >::Real ortogonalper< Complex >::imag_relative() const{
	
	return data.imag();

}

template< typename Complex >
ortogonalper< Complex > & ortogonalper< Complex >::operator=( const ortogonalper & other ){
	
	perspective = other.perspective;
	data = other.data;

	return *this;
}

template< typename Complex >
ortogonalper< Complex > ortogonalper< Complex >::operator+( const ortogonalper & other ) const{
	
	return kproduct( 0 , *this , other );

}

template< typename Complex >
ortogonalper< Complex > ortogonalper< Complex >::operator-() const{
	
	return kinverse( 0 , *this );

}

template< typename Complex >
ortogonalper< Complex > inverse( const ortogonalper< Complex > & w ){
	
	return kinverse( 1 , w );

}

template< typename Complex >
ortogonalper< Complex > ortogonalper< Complex >::operator-( const ortogonalper & other ) const{
	
	return *this + -other;

}

template< typename Complex >
ortogonalper< Complex > ortogonalper< Complex >::operator*( const ortogonalper & other ) const{
	
	return kproduct( 1 , *this , other );

}

template< typename Complex >
ortogonalper< Complex > ortogonalper< Complex >::operator/( const ortogonalper & other ) const{
	
	return *this * inverse( other );

}

template< typename Complex >
ortogonalper< Complex > & ortogonalper< Complex >::operator+=( const ortogonalper & other ){
	
	return *this = *this + other;

}

template< typename Complex >
ortogonalper< Complex > & ortogonalper< Complex >::operator-=( const ortogonalper & other ){
	
	return *this = *this - other;

}

template< typename Complex >
ortogonalper< Complex > & ortogonalper< Complex >::operator*=( const ortogonalper & other ){
	
	return *this = *this * other;

}

template< typename Complex >
ortogonalper< Complex > & ortogonalper< Complex >::operator/=( const ortogonalper & other ){
	
	return *this = *this / other;

}

template< typename Complex >
ortogonalper< Complex > ortogonalper< Complex >::change( int n ) const{
	
	ortogonalper result( *this );

	result.set_perspective( n );

	return result;
}

template< typename Complex >
ortogonalper< Complex > operator+( const Complex & z , const ortogonalper< Complex > & other ){
	
	return ortogonalper( z ) + other;

}

template< typename Complex >
ortogonalper< Complex > operator-( const Complex & z , const ortogonalper< Complex > & other ){
	
	return ortogonalper( z ) - other;

}

template< typename Complex >
ortogonalper< Complex > operator*( const Complex & z , const ortogonalper< Complex > & other ){
	
	return ortogonalper( z ) * other;

}

template< typename Complex >
ortogonalper< Complex > operator/( const Complex & z , const ortogonalper< Complex > & other ){
	
	return ortogonalper( z ) / other;
	
}

template< typename Complex >
ostream & operator<<( ostream & o , const ortogonalper< Complex > & a ){
	
	return o<<a.data<<" , perspective : "<<a.perspective;

}

template< typename Complex >
ortogonalper< Complex > exp( const ortogonalper< Complex > & a ){
	
	return make_orto_per( exp( a.w_relative() ) , a.get_perspective() );

}

template< typename Complex >
ortogonalper< Complex > log( const ortogonalper< Complex > & a ){
	
	return make_orto_per( log( a.w_relative() ) , a.get_perspective() );

}

template< typename Complex >
ortogonalper< Complex > pow( const ortogonalper< Complex > & a , const ortogonalper< Complex > & b ){
	
	if( a.get_perspective() == 1 && b.get_perspective() == 1 ){
		
		return make_orto_per( a.w_relative() * b.w() , 1 );

	}

	if( a.get_perspective() == 2 && b.get_perspective() == 2 ){
		
		return make_orto_per( a.w_relative() + exp( b.w_relative() ) , 2 );

	}

	return exp( log( b ) * a );
}

template< typename Complex >
long double arg( const ortogonalper< Complex > & a ){
	
	return arg( a.w() );

}

template< typename Complex >
long double abs( const ortogonalper< Complex > & a ){
	
	return abs( a.w() );

}

template< typename Complex >
ortogonalper< Complex > cos( const ortogonalper< Complex > & w ){
	
	return ( exp( w * ortogonalper< Complex >::I ) + exp( -w * ortogonalper< Complex >::I ) ) / real_type< Complex >( 2 );
	
}

template< typename Complex >
ortogonalper< Complex > sin( const ortogonalper< Complex > & w ){
	
	return ( exp( w * ortogonalper< Complex >::I ) - exp( -w * ortogonalper< Complex >::I ) ) / Complex( 0 , 2 );
	
}

template< typename Complex >
ortogonalper< Complex > tan( const ortogonalper< Complex > & w ){
	
	return sin( w ) / cos( w );
	
}

template< typename Complex >
ortogonalper< Complex > sec( const ortogonalper< Complex > & w ){
	
	return inverse( cos( w ) );
	
}

template< typename Complex >
ortogonalper< Complex > csc( const ortogonalper< Complex > & w ){
	
	return inverse( sin( w ) );
	
}

template< typename Complex >
ortogonalper< Complex > cot( const ortogonalper< Complex > & w ){
	
	return cos( w ) / sin( w );
	
}

template< typename Complex >
ortogonalper< Complex > cosh( const ortogonalper< Complex > & w ){
	
	return ( exp( w ) + exp( -w ) ) / real_type< Complex >( 2 );
	
}

template< typename Complex >
ortogonalper< Complex > sinh( const ortogonalper< Complex > & w ){
	
	return ( exp( w ) - exp( -w ) ) / real_type< Complex >( 2 );
	
}

template< typename Complex >
ortogonalper< Complex > tanh( const ortogonalper< Complex > & w ){
	
	return sinh( w ) / cosh( w );
	
}

template< typename Complex >
ortogonalper< Complex > sech( const ortogonalper< Complex > & w ){
	
	return inverse( cosh( w ) );
	
}

template< typename Complex >
ortogonalper< Complex > csch( const ortogonalper< Complex > & w ){
	
	return inverse( sinh( w ) );
	
}

template< typename Complex >
ortogonalper< Complex > coth( const ortogonalper< Complex > & w ){
	
	return inverse( tanh( w ) );
	
}

template< typename Complex >
ortogonalper< Complex > sqrt( const ortogonalper< Complex > & w ){
	
	return pow( w , real_type< Complex >( 0.5 ) );
	
}

template< typename Complex >
ortogonalper< Complex > cbrt( const ortogonalper< Complex > & w ){
	
	return pow( w , real_type< Complex >( 1 ) / 3 );
	
}

template< typename Complex >
ortogonalper< Complex > root( const ortogonalper< Complex > & u ,const ortogonalper< Complex > & v ){
	
	return pow( u , inverse( v ) );
	
}

template< typename Complex >
ortogonalper< Complex > wlambert( const ortogonalper< Complex > & a ){
	
	return ortogonalper< Complex >( wlambert( a.w() ) , a.get_perspective() );
	
}

template< typename Complex >
ortogonalper< Complex > wave( const ortogonalper< Complex > & a ){
	
	return exp( wlambert( log( a ) ) );
	
}

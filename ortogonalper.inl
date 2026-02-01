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
ortogonalper< Complex >::ortogonalper( OrtoType u , int n ) : data( e_tetration_integer< ortogonal >( u , -n ) ) , perspective( n ){
	
	//nothing

}

template< typename Complex >
ortogonalper< Complex >::ortogonalper( const Complex & u , int n ) : data( e_tetration_integer< ortogonal >( u , -n ) ) , perspective( n ){
	
	//nothing

}

template< typename Complex >
ortogonalper< Complex >::ortogonalper( RealType r , int n ) : data( e_tetration_integer< ortogonal >( r , -n ) ) , perspective( n ){
	
	//nothing

}

template< typename Complex >
ortogonalper< Complex >::~ortogonalper(){
	
	//nothing

}

template< typename Complex >
const ortogonalper< Complex > ortogonalper< Complex >::I = Complex( 0 , 1 );

template< typename Complex >
const ortogonalper< Complex > ortogonalper< Complex >::NaN = Complex( std::numeric_limits< RealType >::quiet_NaN() , std::numeric_limits< RealType >::quiet_NaN() );

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

template< number_ortoper T >
T kproduct( int n , T u , T v ){
	
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

template< number_ortoper T >
T kinverse( int n , T w ){
	
	return make_orto_per( kinverse( n - w.perspective , w.data ) , w.perspective );

}

template< typename Complex >
ortogonalper< Complex >::RealType ortogonalper< Complex >::real() const{
	
	return z().real();

}

template< typename Complex >
ortogonalper< Complex >::RealType ortogonalper< Complex >::imag() const{
	
	return z().imag();

}

template< typename Complex >
ortogonalper< Complex >::RealType ortogonalper< Complex >::real_relative() const{
	
	return data.real();

}

template< typename Complex >
ortogonalper< Complex >::RealType ortogonalper< Complex >::imag_relative() const{
	
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

template< number_ortoper T >
T inverse( const T & w ){
	
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

template< number_ortoper T >
ostream & operator<<( ostream & o , const T & a ){
	
	return o<<a.data<<" , perspective : "<<a.perspective;

}

template< number_ortoper T >
T exp( const T & a ){
	
	return make_orto_per( exp( a.w_relative() ) , a.get_perspective() );

}

template< number_ortoper T >
T log( const T & a ){
	
	return make_orto_per( log( a.w_relative() ) , a.get_perspective() );

}

template< number_ortoper T >
T pow( const T & a , const T & b ){
	
	if( a.get_perspective() == 1 && b.get_perspective() == 1 ){
		
		return make_orto_per( a.w_relative() * b.w() , 1 );

	}

	if( a.get_perspective() == 2 && b.get_perspective() == 2 ){
		
		return make_orto_per( a.w_relative() + exp( b.w_relative() ) , 2 );

	}

	return exp( log( b ) * a );
}

template< number_ortoper T >
long double arg( const T & a ){
	
	return arg( a.w() );

}

template< number_ortoper T >
long double abs( const T & a ){
	
	return abs( a.w() );

}

template< number_ortoper T >
T cos( const T & w ){
	
	return ( exp( w * T::I ) + exp( -w * T::I ) ) / real_type< T >( 2 );
	
}

template< number_ortoper T >
T sin( const T & w ){
	
	return ( exp( w * T::I ) - exp( -w * T::I ) ) / T::ComplexType( 0 , 2 );
	
}

template< number_ortoper T >
T tan( const T & w ){
	
	return sin( w ) / cos( w );
	
}

template< number_ortoper T >
T sec( const T & w ){
	
	return inverse( cos( w ) );
	
}

template< number_ortoper T >
T csc( const T & w ){
	
	return inverse( sin( w ) );
	
}

template< number_ortoper T >
T cot( const T & w ){
	
	return cos( w ) / sin( w );
	
}

template< number_ortoper T >
T cosh( const T & w ){
	
	return ( exp( w ) + exp( -w ) ) / real_type< T >( 2 );
	
}

template< number_ortoper T >
T sinh( const T & w ){
	
	return ( exp( w ) - exp( -w ) ) / real_type< T >( 2 );
	
}

template< number_ortoper T >
T tanh( const T & w ){
	
	return sinh( w ) / cosh( w );
	
}

template< number_ortoper T >
T sech( const T & w ){
	
	return inverse( cosh( w ) );
	
}

template< number_ortoper T >
T csch( const T & w ){
	
	return inverse( sinh( w ) );
	
}

template< number_ortoper T >
T coth( const T & w ){
	
	return inverse( tanh( w ) );
	
}

template< number_ortoper T >
T sqrt( const T & w ){
	
	return pow( w , real_type< T >( 0.5 ) );
	
}

template< number_ortoper T >
T cbrt( const T & w ){
	
	return pow( w , real_type< T >( 1 ) / 3 );
	
}

template< number_ortoper T >
T root( const T & u ,const T & v ){
	
	return pow( u , inverse( v ) );
	
}

template< number_ortoper T >
T wlambert( const T & a ){
	
	return T( wlambert( a.w() ) , a.get_perspective() );
	
}

template< number_ortoper T >
T wave( const T & a ){
	
	return exp( wlambert( log( a ) ) );
	
}

#include"ortogonals.hpp"
#include<algorithm>

template< typename T >
T branch( T angle ){
	
	T x = ceil( ( angle + constants::pi< T >() ) / constants::tau< T >() ) - T( 1 );
	
	return x;
}

template< typename T >
T collapse( T angle ){
	
	return angle - branch( angle ) * constants::tau< T >();
	
}

template< typename T >
T rebranch( T z1 , T z2 ){
	
	return collapse( z1 ) + branch( z2 ) * constants::tau< T >();
	
}

template< typename T >
int is_sing( T z ){
	
	if( z == T( 0 ) ) return -1;
	if( z == T( 1 ) ) return 0;
	if( z == exp( T( 1 ) ) ) return 1;
	if( z == exp( exp( T( 1 ) ) ) ) return 2;
	if( z == exp( exp( exp( T( 1 ) ) ) ) ) return 3;
	
	return 4;
}

template< typename T >
T value_tetration( int k ){
	
	if( k == -1 ) return T( 0 );
	if( k == 0 ) return T( 1 );
	if( k == 1 ) return exp( T( 1 ) );
	if( k == 2 ) return exp( exp( T( 1 ) ) );
	if( k == 3 ) return exp( exp( exp( T( 1 ) ) ) );
	if( k > 3 ) return std::numeric_limits< T >::infinity();
	
	return -1.l;
}

template< typename Complex >
bool ortogonal< Complex >::overpased_sing() const{
	
	return type == Tetration ? info.sing > 3 : false;
	
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::make_sing( int k ){
	
	ortogonal< Complex > w;
	
	w.info.sing = k;
	
	if( k >= 0 ){
		
		w.type = ortogonal< Complex >::Tetration;
		
	}
	else{
		
		w.type = ortogonal< Complex >::Sing;
		
	}
	
	return w;
}

template< typename Complex >
ortogonal< Complex >::operator Complex() const{
	
	if( type ){
		
		return type == Tetration ? value_tetration< Real >( info.sing ) : Complex( std::numeric_limits< Real >::quiet_NaN() , std::numeric_limits< Real >::quiet_NaN() );
		
	}
	
	return info.z;
}

template< typename Complex >
int ortogonal< Complex >::sing() const{
	
	if( !type ){
		
		cerr<<"class ortogonal -> Erorr sing: a normal ortogonal can't be a singularity"<<endl;
		
		return 0;
	}

	return info.sing;
}

template< typename Complex >
ortogonal< Complex > collapse( const ortogonal< Complex > & w ){
	
	return ortogonal< Complex >( w.z() );

}

template< typename T >
T e_tetration_positive( T z , unsigned int n ){
	
	while( n ){
		
		z = exp( z );
		n--;

	}

	return z;
}

template< typename T >
T e_tetration_negative( T z , unsigned int n ){
	
	while( n ){
		
		z = log( z );
		n--;

	}

	return z;
}

template< typename Complex >
ortogonal< Complex > e_tetration_positive( ortogonal< Complex > w , unsigned int n ){
	
	if( w.getType() ){
		
		return ortogonal< Real ,  Complex >::make_sing( w.sing() + n );

	}

	while( n ){
		
		w = exp( w );
		n--;

	}

	return w;
}

template< typename Complex >
ortogonal< Complex > e_tetration_negative( ortogonal< Complex >  w , unsigned int n ){
	
	if( w.getType() ){
		
		return ortogonal< Real ,  Complex >::make_sing( w.sing() - n );

	}

	while( n ){
		
		w = log( w );
		n--;

	}

	return w;
}

template< typename T >
T e_tetration_integer( T w , int n ){
	
	return n < 0 ? e_tetration_negative< T >( w , -n ) : e_tetration_positive< T >( w , n );

}

template< typename Complex >
ortogonal< Complex > e_tetration_integer( ortogonal< Complex > w , int n ){
	
	return n < 0 ? e_tetration_negative< Complex >( w , -n ) : e_tetration_positive< Complex >( w , n );

}

template< typename Complex >
ortogonal< Complex > collapse( const ortogonal< Complex > & w , int level ){
	
	if( w.getType() == ortogonal::Sing ){
		
		cerr<<"class ortogonal -> collapse : Invalid collapse in singularities"<<endl;

		return ortogonal::NaN;
	}
	
	if( level < 0 ){
		
		return ortogonal( e_tetration_positive( e_tetration_negative( w.z() , -level ) , -level ) );

	}

	ortogonal result( w.z() );
	
	for( int i = 0; i < level; i++ ){
		
		result.add_branch( i , w.branch( i ) );

	}

	return result;
}

template< typename Complex >
ortogonal< Complex > kproduct( int n , ortogonal< Complex > z , ortogonal< Complex > w ){
	
	if( n < 0 ){
		
		for( unsigned int i = 0; i < -n; i++ ){
		
			z = exp( z );
			w = exp( w );
		
		}
	
		ortogonal< Complex > result = z + w;
	
		for( unsigned int i = 0; i < -n; i++ ){
		
			result = log( result );
		
		}

		return result;
	}

	if( n == 0 ) return z + w;

	for( unsigned int i = 0; i < n - 1; i++ ){
		
		z = log( z );
		w = log( w );
		
	}
	
	ortogonal< Complex > result = z * w;
	
	for( unsigned int i = 0; i < n - 1; i++ ){
		
		result = exp( result );
		
	}
	
	return result;
}

template< typename Complex >
ortogonal< Complex > kinverse( int n , ortogonal< Complex > w ){
	
	if( n < 0 ){
		
		for( unsigned int i = 0; i < -n; i++ ){
		
			w = exp( w );
		
		}
	
		ortogonal< Complex > result = -w;
	
		for( unsigned int i = 0; i < -n; i++ ){
		
			result = log( result );
		
		}
	
		return result;
	}

	if( n == 0 ) return -w;
	if( n == 1 ) return inverse( w );

	for( unsigned int i = 0; i < n - 1; i++ ){
		
		w = log( w );
		
	}
	
	ortogonal< Complex > result = inverse( w );
	
	for( unsigned int i = 0; i < n - 1; i++ ){
		
		result = exp( result );
		
	}
	
	return result;
}

template< typename Complex >
ortogonal< Complex > inverse( const ortogonal< Complex > & w ){
	
	return exp( -log( w ) );
	
}

template< typename Complex >
ortogonal< Complex > operator+( real_type< Complex > x , const ortogonal< Complex > & w ){
	
	return w + x;
	
}

template< typename Complex >
ortogonal< Complex > operator-( real_type< Complex > x , const ortogonal< Complex > & w ){
	
	return -w + x;
	
}

template< typename Complex >
ortogonal< Complex > operator*( real_type< Complex > x , const ortogonal< Complex > & w ){
	
	return w * x;
	
}

template< typename Complex >
ortogonal< Complex > operator/( real_type< Complex > x , const ortogonal< Complex > & w ){
	
	return inverse( w ) * x;
	
}

template< typename Complex >
ortogonal< Complex > exp( const ortogonal< Complex > & w ){
	
	using Real = real_type< Complex >;

	if( w.type ){
		
		if( w.type == ortogonal< Complex >::Sing ) return ortogonal< Complex >::make_sing( w.info.sing + 1 );
		
		ortogonal< Complex > result = ortogonal< Complex >::make_sing( w.info.sing + 1 );
		
		for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
			
			result.branchs.insert( make_pair( i->first + 1 , i->second ) );
			
		}
		
		return result;
	}
	
	Real angle = w.info.z.imag();
	int new_branch = branch( angle );
	
	ortogonal< Complex > result( exp( w.info.z ) );
	
	if( ( ( Real )( new_branch ) * constants::tau< Real >() < angle && result.info.z.imag() < 0 )
	||  ( ( Real )( new_branch ) * constants::tau< Real >() >= angle && result.info.z.imag() > 0 ) ){
		
		result.info.z = Complex( result.info.z.real() , 0 );
		
	}
	
	if( new_branch != 0 ){
		
		result.branchs.insert( make_pair( 0 , new_branch ) );
		
	}
	
	for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
		
		result.branchs.insert( make_pair( i->first + 1 , i->second ) );
		
	}
	
	return result;
}

template< typename Complex >
ortogonal< Complex > log( const ortogonal< Complex > & w ){
	
	if( w.type ){
		
		if( w.type == ortogonal< Complex >::Sing ) return ortogonal< Complex >::make_sing( w.info.sing - 1 );
		if( w.info.sing == 0 ) return ortogonal< Complex >::make_sing( -1 );
		
		if( w.branch( 0 ) == 0 ){
			
			ortogonal< Complex > result = ortogonal< Complex >::make_sing( w.info.sing - 1 );
			
			for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
				
				if( i->first != 0 ){
					
					result.branchs.insert( make_pair( i->first - 1 , i->second ) );
					
				}
				
			}
			
			return result;
		}
		
		real_type< Complex > angle = arg( w );
		
		ortogonal< Complex > result( log( abs( value_tetration< real_type< Complex > >( w.info.sing ) ) ) , angle );
		
		for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
			
			if( i->first != 0 ){
				
				result.branchs.insert( make_pair( i->first - 1 , i->second ) );
				
			}
			
		}
		
		return result;
	}
	
	ortogonal< Complex > result( log( abs( w ) ) , arg( w ) );
	
	for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
		
		if( i->first != 0 ){
			
			result.branchs.insert( make_pair( i->first - 1 , i->second ) );
			
		}
		
	}
	
	return result;
}

template< typename Complex >
ortogonal< Complex > pow( const ortogonal< Complex > & u , const ortogonal< Complex > & v ){
	
	return exp( v * log( u ) );
	
}

template< typename Complex >
ortogonal< Complex > cos( const ortogonal< Complex > & w ){
	
	return ( exp( w * ortogonal< Complex >::I ) + exp( -w * ortogonal< Complex >::I ) ) / real_type< Complex >( 2 );
	
}

template< typename Complex >
ortogonal< Complex > sin( const ortogonal< Complex > & w ){
	
	return ( exp( w * ortogonal< Complex >::I ) - exp( -w * ortogonal< Complex >::I ) ) / Complex( 0 , 2 );
	
}

template< typename Complex >
ortogonal< Complex > tan( const ortogonal< Complex > & w ){
	
	return sin( w ) / cos( w );
	
}

template< typename Complex >
ortogonal< Complex > sec( const ortogonal< Complex > & w ){
	
	return inverse( cos( w ) );
	
}

template< typename Complex >
ortogonal< Complex > csc( const ortogonal< Complex > & w ){
	
	return inverse( sin( w ) );
	
}

template< typename Complex >
ortogonal< Complex > cot( const ortogonal< Complex > & w ){
	
	return cos( w ) / sin( w );
	
}

template< typename Complex >
ortogonal< Complex > cosh( const ortogonal< Complex > & w ){
	
	return ( exp( w ) + exp( -w ) ) / real_type< Complex >( 2 );
	
}

template< typename Complex >
ortogonal< Complex > sinh( const ortogonal< Complex > & w ){
	
	return ( exp( w ) - exp( -w ) ) / real_type< Complex >( 2 );
	
}

template< typename Complex >
ortogonal< Complex > tanh( const ortogonal< Complex > & w ){
	
	return sinh( w ) / cosh( w );
	
}

template< typename Complex >
ortogonal< Complex > sech( const ortogonal< Complex > & w ){
	
	return inverse( cosh( w ) );
	
}

template< typename Complex >
ortogonal< Complex > csch( const ortogonal< Complex > & w ){
	
	return inverse( sinh( w ) );
	
}

template< typename Complex >
ortogonal< Complex > coth( const ortogonal< Complex > & w ){
	
	return inverse( tanh< Complex >( w ) );
	
}

template< typename Complex >
ortogonal< Complex > sqrt( const ortogonal< Complex > & w ){
	
	return pow( w , ortogonal< Complex >( 0.5 ) );
	
}

template< typename Complex >
ortogonal< Complex > cbrt( const ortogonal< Complex > & w ){
	
	return pow( w , real_type< Complex >( 1 ) / real_type< Complex >( 3 ) );
	
}

template< typename Complex >
ortogonal< Complex > root( const ortogonal< Complex > & u ,const ortogonal< Complex > & v ){
	
	return pow( u , inverse( v ) );
	
}

template< typename Complex >
real_type< Complex > arg( const ortogonal< Complex > & w ){
	
	return arg( w.z() ) + w.branch( 0 ) * constants::tau< real_type< Complex > >();
	
}

template< typename Complex >
real_type< Complex > abs( const ortogonal< Complex > & w ){
	
	return abs( w.z() );
	
}

template< typename Complex >
ortogonal< Complex > wlambert( const ortogonal< Complex > & w ){
	
	return wlambert( Complex( w ) , w.branch( 0 ) );
	
}

template< typename Complex >
ortogonal< Complex > wave( const ortogonal< Complex > & w ){
	
	return exp( wlambert( log( w ) ) );
	
}

template< typename Complex >
ortogonal< Complex >::ortogonal() : type( Sing ) , branchs(){
	
	info.sing = -1;
	
}

template< typename Complex >
ortogonal< Complex >::ortogonal( const Complex & z ) : branchs(){
	
	int k = is_sing( z );
	
	if( k == 4 ){
		
		info.z = z;
		type = Normal;
		
	}
	else if( k == -1 ){
		
		info.sing = -1;
		type = Sing;
		
	}
	else{
		
		info.sing = k;
		type = Tetration;
		
	}
	
}

template< typename Complex >
ortogonal< Complex >::ortogonal( Real r ) : branchs(){
	
	int k = is_sing( r );
	
	if( k == 4 ){
		
		info.z = r;
		type = Normal;
		
	}
	else if( k == -1 ){
		
		info.sing = -1;
		type = Sing;
		
	}
	else{
		
		info.sing = k;
		type = Tetration;
		
	}
	
}

template< typename Complex >
ortogonal< Complex >::ortogonal( Real r , Real i ) : ortogonal( Complex( r , i ) ){
	
	//nothing
	
}

template< typename Complex >
ortogonal< Complex >::ortogonal( const ortogonal & other ) : info( other.info ) , type( other.type ) , branchs( other.branchs ){
	
	//nothing
	
}

template< typename Complex >
ortogonal< Complex >::~ortogonal(){
	
	//nothing
	
}

template< typename Complex >
const ortogonal< Complex > ortogonal< Complex >::I = ortogonal( Real( 1 ) , Real( 0 ) );

template< typename Complex >
const ortogonal< Complex > ortogonal< Complex >::NaN = ortogonal( std::numeric_limits< Real >::quiet_NaN() , std::numeric_limits< Real >::quiet_NaN() );

template< typename Complex >
ortogonal< Complex > & ortogonal< Complex >::operator=( const ortogonal & other ){
	
	type = other.type;
	info = other.info;
	branchs = other.branchs;

	return *this;
}

template< typename Complex >
void ortogonal< Complex >::add_branch( unsigned int index , int value ){
	
	if( value == 0 || type == Sing ) return;
	
	if( type == Tetration ){
		
		if( index <= info.sing ){
			
			branchs.insert( make_pair( index , branch( index ) + value ) );
			
			return;
		}
		
		cout<<"class ortogonal : Error in add_branch -> Index exceeded in the tetration type."<<endl;
		
		return;
	}
	
	branchs.insert( make_pair( index , branch( index ) + value ) );
	
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::operator-() const{
	
	if( type ){
		
		if( type == Sing ){
			
			return ( info.sing == -1 ) ? *this : ortogonal::NaN;
			
		}
		
		return make_orto( Complex( -value_tetration< Real >( info.sing ) ) , 0 , -branch( 0 ) );
	}

	if( info.z.imag() == Real( 0 ) ) return make_orto( Complex( -info.z.real() ) , -branch( 0 ) );
	
	return make_orto( -info.z , -branch( 0 ) );
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::operator+( const ortogonal & other ) const{
	
	if( !type && !other.type ){
		
		Complex r = info.z + other.info.z;
		
		if( info.z.imag() > 0 && arg( other.info.z ) < arg( info.z ) - constants::pi< Real >() && r.imag() < 0 && r.real() < 0 ){
			
			return make_orto( r , branch( 0 ) + other.branch( 0 ) + 1 );
			
		}
		
		if( info.z.imag() < 0 && arg( other.info.z ) > arg( info.z ) + constants::pi< Real >() && r.imag() > 0 && r.real() < 0 ){
			
			return make_orto( r , branch( 0 ) + other.branch( 0 ) - 1 );
			
		}
		
		return make_orto( r , branch( 0 ) + other.branch( 0 ) );
	}
	
	if( type == Sing ) return info.sing + 1 ? ( info.sing + 2 ? ortogonal::NaN : *this ) : other;
	if( other.type == Sing ) return other.info.sing + 1 ? ( other.info.sing + 2 ? ortogonal::NaN : other ) : *this;
	if( overpased_sing() && !other.overpased_sing() ) return *this;
	if( !overpased_sing() && other.overpased_sing() ) return other;
	if( overpased_sing() && other.overpased_sing() ) return info.sing > other.info.sing ? *this : other;
	
	Complex a = type ? value_tetration< Real >( info.sing ) : info.z;
	Complex b = other.type ? value_tetration< Real >( other.info.sing ) : other.info.z;
	
	return make_orto( a + b , branch( 0 ) + other.branch( 0 ) );
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::operator*( const ortogonal & other ) const{
	
	if( !type && !other.type ){
		
		Real angle1 = arg( info.z ) + ( Real )( branch( 0 ) ) * constants::tau< Real >();
		Real angle2 = arg( other.info.z ) + ( Real )( other.branch( 0 ) ) * constants::tau< Real >();
		int new_branch = ::branch< Real >( angle1 + angle2 );
		
		Complex product = info.z * other.info.z;
		Complex orto_z( log( abs( info.z ) ) , angle1 );
		Complex orto_z2( log( abs( other.info.z ) ) , angle2 );
		Complex orto_r = log( product );
		
		if( orto_z.imag() > 0 && arg( orto_z2 ) < arg( orto_z ) - constants::pi< Real >() && orto_r.imag() < 0 && orto_r.real() < 0 ){
			
			return make_orto( product , new_branch , branch( 1 ) + other.branch( 1 ) + 1 );
			
		}
		
		if( orto_z.imag() < 0 && arg( orto_z2 ) > arg( orto_z ) + constants::pi< Real >() && orto_r.imag() > 0 && orto_r.real() < 0 ){
			
			return make_orto( product , new_branch , branch( 1 ) + other.branch( 1 ) - 1 );
			
		}
		
		return make_orto( product , new_branch );
	}
	
	if( type == Sing ) return info.sing == -1 ? *this : ortogonal::NaN;
	if( other.type == Sing ) return other.info.sing == -1 ? other : ortogonal::NaN;
	
	if( overpased_sing() && !other.overpased_sing() ) return *this;
	if( !overpased_sing() && other.overpased_sing() ) return other;
	if( overpased_sing() && other.overpased_sing() ) return info.sing > other.info.sing ? *this : other;
	
	if( type ) if( info.sing == 0 ) return other;
	if( other.type ) if( other.info.sing == 0 ) return *this;
	
	Complex a = type ? value_tetration< Real >( info.sing ) : info.z;
	Complex b = other.type ? value_tetration< Real >( other.info.sing ) : other.info.z;
	
	Real angle1 = arg( a ) + ( Real )( branch( 0 ) ) * constants::tau< Real >();
	Real angle2 = arg( b ) + ( Real )( other.branch( 0 ) ) * constants::tau< Real >();
	int new_branch = ::branch< Real >( angle1 + angle2 );
	
	return make_orto( a * b , new_branch , branch( 1 ) + other.branch( 1 ) );
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::operator-( const ortogonal & other ) const{
	
	return *this + -other;
	
}

template< typename Complex >
ortogonal< Complex > ortogonal< Complex >::operator/( const ortogonal & other ) const{
	
	return *this * inverse( other );
	
}

template< typename Complex >
ortogonal< Complex > operator+( const Complex & z , const ortogonal< Complex > & other ){
	
	return other + z;
	
}

template< typename Complex >
ortogonal< Complex > operator-( const Complex & z , const ortogonal< Complex > & other ){
	
	return -other + z;
	
}

template< typename Complex >
ortogonal< Complex > operator*( const Complex & z , const ortogonal< Complex > & other ){
	
	return other * z;
	
}

template< typename Complex >
ortogonal< Complex > operator/( const Complex & z , const ortogonal< Complex > & other ){
	
	return inverse( other ) * z;
	
}

template< typename Complex >
int ortogonal< Complex >::branch( unsigned int index ) const{
	
	if( type == Sing ){
		
		return -1;
		
	}
	
	if( branchs.find( index ) != branchs.end() ){
		
		return branchs.at( index );
		
	}
	
	return 0;
}

template< typename Complex >
int ortogonal< Complex >::complexity() const{
	
	if( type == Sing ){
		
		return -1;
		
	}
	
	if( type == Tetration ){
		
		if( branchs.empty() ){
			
			return 0;
			
		}
		
		map< unsigned int , int >::const_iterator i = max_element( branchs.begin() , branchs.end() );
		
		return i->second + 1;
	}
	
	if( branchs.empty() ){
		
		return 0;
		
	}
	
	map< unsigned int , int >::const_iterator i = max_element( branchs.begin() , branchs.end() );
	
	return i->second + 1;
}

template< typename Complex >
ortogonal< Complex > & ortogonal< Complex >::operator+=( const ortogonal & other ){
	
	return *this = *this + other;
	
}

template< typename Complex >
ortogonal< Complex > & ortogonal< Complex >::operator-=( const ortogonal & other ){
	
	return *this = *this - other;
	
}
template< typename Complex >
ortogonal< Complex > & ortogonal< Complex >::operator*=( const ortogonal & other ){
	
	return *this = *this * other;
	
}

template< typename Complex >
ortogonal< Complex > & ortogonal< Complex >::operator/=( const ortogonal & other ){
	
	return *this = *this / other;
	
}

template< typename Complex >
bool ortogonal< Complex >::operator==( const ortogonal & other ) const{
	
	return ( type ? info.sing == other.info.sing : info.z == other.info.z ) && type == other.type && branchs == other.branchs;

}

template< typename Complex >
bool ortogonal< Complex >::operator!=( const ortogonal & other ) const{
	
	return !( *this == other );

}

template< typename Complex >
const ortogonal< Complex >::Type & ortogonal< Complex >::getType() const{
	
	return type;
	
}

template< typename Complex >
Complex ortogonal< Complex >::z() const{
	
	if( type == Sing ){
		
		if( info.sing == -1 ) return 0;
		
		cout<<"class ortogonal -> Error in z part : Can't exists the z part of a singularity minor that -1"<<endl;
		
		return Complex( std::numeric_limits< Real >::quiet_NaN() , std::numeric_limits< Real >::quiet_NaN() );
	}
	
	return type == Tetration ? value_tetration< Real >( info.sing ) : info.z;
}

template< typename Complex >
ortogonal< Complex >::Real ortogonal< Complex >::real() const{
	
	if( type == Sing ){
		
		if( info.sing == -1 ) return 0;
		
		cout<<"class ortogonal -> Error in real part : Can't exists the real part of a singularity minor that -1"<<endl;
		
		return std::numeric_limits< Real >::quiet_NaN();
	}
	
	return type == Tetration ? value_tetration< Real >( info.sing ) : info.z.real();
}

template< typename Complex >
ortogonal< Complex >::Real ortogonal< Complex >::imag() const{
	
	if( type == Sing ){
		
		if( info.sing == -1 ) return 0;
		
		cout<<"class ortogonal -> Error in imaginary part : Can't exists the imaginary part of a singularity minor that -1"<<endl;
		
		return std::numeric_limits< Real >::quiet_NaN();
	}
	
	return type == Tetration ? 0 : info.z.imag();
}

template< typename Complex >
std::ostream & operator<<( std::ostream & o , const ortogonal< Complex > & w ){
	
	if( w.type == ortogonal< Complex >::Sing ){
		
		if( w.info.sing == -1 ) return o<<Complex( 0 )<<endl;

		o<<"singularity("<<w.info.sing<<")";
		
		return o;
	}
	
	if( w.type == ortogonal< Complex >::Tetration ){
		
		if( w.info.sing > 3 ){
			
			o<<"singularity("<<w.info.sing<<")";
			
		}
		else{
			
			o<<Complex( value_tetration< Real >( w.info.sing ) );
			
		}
		
		for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
			
			o<<" , o"<<i->first<<" : "<<i->second;
			
		}
		
		return o;
	}
	
	o<<w.info.z;
	
	for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
		
		o<<" , o"<<i->first<<" : "<<i->second;
		
	}
	
	return o;
}

template< typename T >
T zexpz( T z ){
	
	return z * exp( z );
	
}

template< typename T >
T zexpz_d( T z ){
	
	return exp( z ) + z * exp( z );
	
}

template< typename T >
T zexpz_dd( T z ){
	
	return exp( z ) * T( 2 ) + z * exp( z );
	
}

template< typename T >
T InitPoint(T z, int k){
	
	T I( 0 , 1 );
	T two_pi_k_I = T( k ) * T( 3.141592653589793238462643383279502884l * 2.l ) * I;
	T ip( log(z) + two_pi_k_I - log(log(z) + two_pi_k_I) );// initial point coming from the general asymptotic approximation
	T p( sqrt( T( 2 ) * ( exp( T( 1 ) ) * z + T( 1 ) ) ) );// used when we are close to the branch cut around zero and when k=0,-1
	
	//we are close to the branch cut, the initial point must be chosen carefully
	if( k == 0 && abs( z - exp( -T( 1 ) ) ) <= T( 1 ).real() ){
		
		if( k == 0 ) ip = -T( 1 ) + p - T( 1 ) / T( 3 ) * ( p * p ) + T( 11 ) / T( 72 ) * ( p * p * p );
		if( k == 1 && z.imag() < T( 0 ).real() ) ip = -T( 1 ) - p - T( 1 ) / T( 3 ) * ( p * p ) - T( 11 ) / T( 72 ) * ( p * p * p );
		if( k == -1 && z.imag() > T( 0 ).real() ) ip = -T( 1 ) - p - T( 1 ) / T( 3 ) * ( p * p ) - T( 11 ) / T( 72 ) * ( p * p * p );
		
	}
	
	if( k == 0 && abs(z - T( 0.5 )) <= T( 0.5 ).real() ){
		
		// (1,1) Pade approximant for W(0,a)
		ip = ( T( 0.35173371l ) * ( T( 0.1237166l ) + T( 7.061302897l ) * z ) ) / ( T( 2 ) + T( 0.827184l ) * ( T( 1 ) + T( 2 ) * z ) );
		
	}
	
	if( k == -1 && abs( z - T( 0.5 ) ) <= T( 0.5 ).real() ){
		
		// (1,1) Pade approximant for W(-1,a)
		ip = -( ( ( T( 2.2591588985l ) +
		T( 4.22096l ) * I ) * ( ( -T( 14.073271l ) - T( 33.767687754l ) * I ) * z - ( T( 12.7127l ) -
		T( 19.071643l ) * I ) * ( T( 1 ) + T( 2 ) * z ) ) ) / ( T( 2 ) - ( T( 17.23103l ) - T( 10.629721l ) * I ) * ( T( 1 ) + T( 2 ) * z ) ) );
		
	}

	return ip;
}

//Creditos por W de Lambert a https://github.com/IstvanMezo/LambertW-function

template< typename T >
T wlambert( T z , int k ){
	
	//For some particular z and k W(z,k) has simple value:
	if( z == T( 0 ) ) return ( k == 0 ) ? 0.l : -std::numeric_limits< decltype( z.real() ) >::infinity();
	if( z == -exp( -T( 1 ) ) && ( k == 0 || k == -1 ) ) return -T( 1 );
	if( z == exp( T( 1 ) ) && k == 0 ) return T( 1 );
	
	//Halley method begins
	T w( InitPoint( z , k ) ) , wprev; // intermediate values in the Halley method
	const unsigned int maxiter = wlambert_complexity; // max number of iterations. This eliminates improbable infinite loops
	unsigned int iter = 0; // iteration counter
	
	do{
		
		wprev = w;
		w -= T( 2 ) * ( ( zexpz( w ) - z ) * zexpz_d( w ) ) / ( T( 2 ) * pow( zexpz_d( w ) , T( 2 ) ) - ( zexpz( w ) - z ) * zexpz_dd( w ) );
		iter++;
		
	} while( abs( w - wprev ) > std::numeric_limits< decltype( z.real() ) >::epsilon() && iter < maxiter );
	
	return w;
}

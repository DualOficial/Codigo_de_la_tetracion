#include"ortogonals.hpp"
#include<algorithm>

template< typename T >
T branch( T angle ){
	
	T x = floor( ( angle + constants::pi< T >() ) / constants::tau< T >() );
	
	if( angle + constants::pi< T >() == x * constants::tau< T >() ){
		
		return x - T( 1 );
		
	}
	
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
	if( k > 3 ) return INFINITY;
	
	return -1.l;
}

template< typename Real , typename Complex >
bool ortogonal< Real , Complex >::overpased_sing() const{
	
	return type == Tetration ? info.sing > 3 : false;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > ortogonal< Real , Complex >::make_sing( int k ){
	
	ortogonal< Real , Complex > w;
	
	w.info.sing = k;
	
	if( k >= 0 ){
		
		w.type = ortogonal< Real , Complex >::Tetration;
		
	}
	else{
		
		w.type = ortogonal< Real , Complex >::Sing;
		
	}
	
	return w;
}

template< typename Real , typename Complex >
ortogonal< Real , Complex >::operator Complex() const{
	
	if( type ){
		
		return type == Tetration ? value_tetration< Real >( info.sing ) : Complex( std::numeric_limits< Real >::quiet_NaN() , std::numeric_limits< Real >::quiet_NaN() );
		
	}
	
	return info.z;
}

template< typename Real , typename Complex >
int ortogonal< Real , Complex >::sing() const{
	
	if( !type ){
		
		cerr<<"class ortogonal -> Erorr sing: a normal ortogonal can't be a singularity"<<endl;
		
		return 0;
	}

	return info.sing;
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > collapse( const ortogonal< Real , Complex > & w ){
	
	return ortogonal< Real , Complex >( w.z() );

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

template< typename Real , typename Complex >
ortogonal< Real , Complex > e_tetration_positive( ortogonal< Real , Complex > w , unsigned int n ){
	
	if( w.getType() ){
		
		return ortogonal< Real ,  Complex >::make_sing( w.sing() + n );

	}

	while( n ){
		
		w = exp< Real , Complex >( w );
		n--;

	}

	return w;
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > e_tetration_negative( ortogonal< Real , Complex >  w , unsigned int n ){
	
	if( w.getType() ){
		
		return ortogonal< Real ,  Complex >::make_sing( w.sing() - n );

	}

	while( n ){
		
		w = log< Real , Complex >( w );
		n--;

	}

	return w;
}

template< typename T >
T e_tetration_integer( T w , int n ){
	
	return n < 0 ? e_tetration_negative< T >( w , -n ) : e_tetration_positive< T >( w , n );

}

template< typename Real , typename Complex >
ortogonal< Real , Complex > e_tetration_integer( ortogonal< Real , Complex > w , int n ){
	
	return n < 0 ? e_tetration_negative< Real , Complex >( w , -n ) : e_tetration_positive< Real , Complex >( w , n );

}

template< typename Real , typename Complex >
ortogonal< Real , Complex > collapse( const ortogonal< Real , Complex > & w , int level ){
	
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

template< typename Real , typename Complex >
ortogonal< Real , Complex > kproduct( int n , ortogonal< Real , Complex > z , ortogonal< Real , Complex > w ){
	
	if( n < 0 ){
		
		for( unsigned int i = 0; i < -n; i++ ){
		
			z = exp( z );
			w = exp( w );
		
		}
	
		ortogonal< Real , Complex > result = z + w;
	
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
	
	ortogonal< Real , Complex > result = z * w;
	
	for( unsigned int i = 0; i < n - 1; i++ ){
		
		result = exp( result );
		
	}
	
	return result;
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > kinverse( int n , ortogonal< Real , Complex > w ){
	
	if( n < 0 ){
		
		for( unsigned int i = 0; i < -n; i++ ){
		
			w = exp( w );
		
		}
	
		ortogonal< Real , Complex > result = -w;
	
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
	
	ortogonal< Real , Complex > result = inverse( w );
	
	for( unsigned int i = 0; i < n - 1; i++ ){
		
		result = exp( result );
		
	}
	
	return result;
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > inverse( const ortogonal< Real , Complex > & w ){
	
	return exp< Real , Complex >( -log< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > operator+( Real x , const ortogonal< Real , Complex > & w ){
	
	return w + x;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > operator-( Real x , const ortogonal< Real , Complex > & w ){
	
	return -w + x;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > operator*( Real x , const ortogonal< Real , Complex > & w ){
	
	return w * x;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > operator/( Real x , const ortogonal< Real , Complex > & w ){
	
	return inverse< Real , Complex >( w ) * x;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > exp( const ortogonal< Real , Complex > & w ){
	
	if( w.type ){
		
		if( w.type == ortogonal< Real , Complex >::Sing ) return ortogonal< Real , Complex >::make_sing( w.info.sing + 1 );
		
		ortogonal< Real , Complex > result = ortogonal< Real , Complex >::make_sing( w.info.sing + 1 );
		
		for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
			
			result.branchs.insert( make_pair( i->first + 1 , i->second ) );
			
		}
		
		return result;
	}
	
	Real angle = w.info.z.imag();
	int new_branch = branch( angle );
	
	ortogonal< Real , Complex > result( exp( w.info.z ) );
	
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

template< typename Real , typename Complex >
ortogonal< Real , Complex > log( const ortogonal< Real , Complex > & w ){
	
	if( w.type ){
		
		if( w.type == ortogonal< Real , Complex >::Sing ) return ortogonal< Real , Complex >::make_sing( w.info.sing - 1 );
		if( w.info.sing == 0 ) return ortogonal< Real , Complex >::make_sing( -1 );
		
		if( w.branch( 0 ) == 0 ){
			
			ortogonal< Real , Complex > result = ortogonal< Real , Complex >::make_sing( w.info.sing - 1 );
			
			for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
				
				if( i->first != 0 ){
					
					result.branchs.insert( make_pair( i->first - 1 , i->second ) );
					
				}
				
			}
			
			return result;
		}
		
		Real angle = arg( w );
		
		ortogonal< Real , Complex > result( log( abs< Real , Complex >( value_tetration< Real >( w.info.sing ) ) ) , angle );
		
		for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
			
			if( i->first != 0 ){
				
				result.branchs.insert( make_pair( i->first - 1 , i->second ) );
				
			}
			
		}
		
		return result;
	}
	
	ortogonal< Real , Complex > result( log( abs< Real , Complex >( w ) ) , arg( w ) );
	
	for( map< unsigned int , int >::const_iterator i = w.branchs.begin(); i != w.branchs.end(); i++ ){
		
		if( i->first != 0 ){
			
			result.branchs.insert( make_pair( i->first - 1 , i->second ) );
			
		}
		
	}
	
	return result;
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > pow( const ortogonal< Real , Complex > & u , const ortogonal< Real , Complex > & v ){
	
	return exp< Real , Complex >( v * log< Real , Complex >( u ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > cos( const ortogonal< Real , Complex > & w ){
	
	return ( exp< Real , Complex >( w * ortogonal< Real , Complex >::I ) + exp( -w * ortogonal< Real , Complex >::I ) ) / Real( 2 );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > sin( const ortogonal< Real , Complex > & w ){
	
	return ( exp< Real , Complex >( w * ortogonal< Real , Complex >::I ) - exp< Real , Complex >( -w * ortogonal< Real , Complex >::I ) ) / Complex( 0 , 2 );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > tan( const ortogonal< Real , Complex > & w ){
	
	return sin< Real , Complex >( w ) / cos< Real , Complex >( w );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > sec( const ortogonal< Real , Complex > & w ){
	
	return inverse< Real , Complex >( cos< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > csc( const ortogonal< Real , Complex > & w ){
	
	return inverse< Real , Complex >( sin< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > cot( const ortogonal< Real , Complex > & w ){
	
	return cos< Real , Complex >( w ) / sin< Real , Complex >( w );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > cosh( const ortogonal< Real , Complex > & w ){
	
	return ( exp< Real , Complex >( w ) + exp< Real , Complex >( -w ) ) / Real( 2 );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > sinh( const ortogonal< Real , Complex > & w ){
	
	return ( exp< Real , Complex >( w ) - exp< Real , Complex >( -w ) ) / Real( 2 );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > tanh( const ortogonal< Real , Complex > & w ){
	
	return sinh< Real , Complex >( w ) / cosh< Real , Complex >( w );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > sech( const ortogonal< Real , Complex > & w ){
	
	return inverse< Real , Complex >( cosh< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > csch( const ortogonal< Real , Complex > & w ){
	
	return inverse< Real , Complex >( sinh< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > coth( const ortogonal< Real , Complex > & w ){
	
	return inverse< Real , Complex >( tanh< Real , Complex >( w ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > sqrt( const ortogonal< Real , Complex > & w ){
	
	return pow< Real , Complex >( w , ortogonal< Real , Complex >( 0.5 ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > cbrt( const ortogonal< Real , Complex > & w ){
	
	return pow< Real , Complex >( w , Real( 1 ) / Real( 3 ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > root( const ortogonal< Real , Complex > & u ,const ortogonal< Real , Complex > & v ){
	
	return pow< Real , Complex >( u , inverse< Real , Complex >( v ) );
	
}

template< typename Real , typename Complex >
Real arg( const ortogonal< Real , Complex > & w ){
	
	return arg( w.z() ) + w.branch( 0 ) * constants::tau< Real >();
	
}

template< typename Real , typename Complex >
Real abs( const ortogonal< Real , Complex > & w ){
	
	return abs( w.z() );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > wlambert( const ortogonal< Real , Complex > & w ){
	
	return wlambert( Complex( w ) , w.branch( 0 ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > wave( const ortogonal< Real , Complex > & w ){
	
	return exp< Real , Complex >( wlambert< Real , Complex >( log< Real , Complex >( w ) ) );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex >::ortogonal() : type( Sing ) , branchs(){
	
	info.sing = -1;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex >::ortogonal( const Complex & z ) : branchs(){
	
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

template< typename Real , typename Complex >
ortogonal< Real , Complex >::ortogonal( Real r ) : branchs(){
	
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

template< typename Real , typename Complex >
ortogonal< Real , Complex >::ortogonal( Real r , Real i ) : ortogonal( Complex( r , i ) ){
	
	//nothing
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex >::ortogonal( const ortogonal & other ) : info( other.info ) , type( other.type ) , branchs( other.branchs ){
	
	//nothing
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex >::~ortogonal(){
	
	//nothing
	
}

template< typename Real , typename Complex >
const ortogonal< Real , Complex > ortogonal< Real , Complex >::I = ortogonal( Real( 1 ) , Real( 0 ) );

template< typename Real , typename Complex >
const ortogonal< Real , Complex > ortogonal< Real , Complex >::NaN = ortogonal( std::numeric_limits< Real >::quiet_NaN() , std::numeric_limits< Real >::quiet_NaN() );

template< typename Real , typename Complex >
ortogonal< Real , Complex > & ortogonal< Real , Complex >::operator=( const ortogonal & other ){
	
	type = other.type;
	info = other.info;
	branchs = other.branchs;

	return *this;
}

template< typename Real , typename Complex >
void ortogonal< Real , Complex >::add_branch( unsigned int index , int value ){
	
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

template< typename Real , typename Complex >
ortogonal< Real , Complex > ortogonal< Real , Complex >::operator-() const{
	
	if( type ){
		
		if( type == Sing ){
			
			return info.sing + 1 ? ortogonal::NaN : *this;
			
		}
		
		return make_orto( Complex( -value_tetration< Real >( info.sing ) ) , 0 , -branch( 0 ) );
	}
	
	return make_orto( -info.z , -branch( 0 ) );
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > ortogonal< Real , Complex >::operator+( const ortogonal & other ) const{
	
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

template< typename Real , typename Complex >
ortogonal< Real , Complex > ortogonal< Real , Complex >::operator*( const ortogonal & other ) const{
	
	if( !type && !other.type ){
		
		Real angle1 = arg( info.z ) + ( Real )( branch( 0 ) ) * constants::pi< Real >();
		Real angle2 = arg( other.info.z ) + ( Real )( other.branch( 0 ) ) * constants::tau< Real >();
		int new_branch = branch( angle1 + angle2 );
		
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
	int new_branch = branch( angle1 + angle2 );
	
	return make_orto( a * b , new_branch , branch( 1 ) + other.branch( 1 ) );
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > ortogonal< Real , Complex >::operator-( const ortogonal & other ) const{
	
	return *this + -other;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > ortogonal< Real , Complex >::operator/( const ortogonal & other ) const{
	
	return *this * inverse( other );
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > operator+( const Complex & z , const ortogonal< Real , Complex > & other ){
	
	return other + z;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > operator-( const Complex & z , const ortogonal< Real , Complex > & other ){
	
	return -other + z;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > operator*( const Complex & z , const ortogonal< Real , Complex > & other ){
	
	return other * z;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > operator/( const Complex & z , const ortogonal< Real , Complex > & other ){
	
	return inverse( other ) * z;
	
}

template< typename Real , typename Complex >
int ortogonal< Real , Complex >::branch( unsigned int index ) const{
	
	if( type == Sing ){
		
		return -1;
		
	}
	
	if( branchs.find( index ) != branchs.end() ){
		
		return branchs.at( index );
		
	}
	
	return 0;
}

template< typename Real , typename Complex >
int ortogonal< Real , Complex >::complexity() const{
	
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

template< typename Real , typename Complex >
ortogonal< Real , Complex > & ortogonal< Real , Complex >::operator+=( const ortogonal & other ){
	
	return *this = *this + other;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > & ortogonal< Real , Complex >::operator-=( const ortogonal & other ){
	
	return *this = *this - other;
	
}
template< typename Real , typename Complex >
ortogonal< Real , Complex > & ortogonal< Real , Complex >::operator*=( const ortogonal & other ){
	
	return *this = *this * other;
	
}

template< typename Real , typename Complex >
ortogonal< Real , Complex > & ortogonal< Real , Complex >::operator/=( const ortogonal & other ){
	
	return *this = *this / other;
	
}

template< typename Real , typename Complex >
bool ortogonal< Real , Complex >::operator==( const ortogonal & other ) const{
	
	return ( type ? info.sing == other.info.sing : info.z == other.info.z ) && type == other.type && branchs == other.branchs;

}

template< typename Real , typename Complex >
bool ortogonal< Real , Complex >::operator!=( const ortogonal & other ) const{
	
	return !( *this == other );

}

template< typename Real , typename Complex >
const ortogonal< Real , Complex >::Type & ortogonal< Real , Complex >::getType() const{
	
	return type;
	
}

template< typename Real , typename Complex >
Complex ortogonal< Real , Complex >::z() const{
	
	if( type == Sing ){
		
		if( info.sing == -1 ) return 0;
		
		cout<<"class ortogonal -> Error in z part : Can't exists the z part of a singularity minor that -1"<<endl;
		
		return Complex( std::numeric_limits< Real >::quiet_NaN() , std::numeric_limits< Real >::quiet_NaN() );
	}
	
	return type == Tetration ? value_tetration< Real >( info.sing ) : info.z;
}

template< typename Real , typename Complex >
Real ortogonal< Real , Complex >::real() const{
	
	if( type == Sing ){
		
		if( info.sing == -1 ) return 0;
		
		cout<<"class ortogonal -> Error in real part : Can't exists the real part of a singularity minor that -1"<<endl;
		
		return std::numeric_limits< Real >::quiet_NaN();
	}
	
	return type == Tetration ? value_tetration< Real >( info.sing ) : info.z.real();
}

template< typename Real , typename Complex >
Real ortogonal< Real , Complex >::imag() const{
	
	if( type == Sing ){
		
		if( info.sing == -1 ) return 0;
		
		cout<<"class ortogonal -> Error in imaginary part : Can't exists the imaginary part of a singularity minor that -1"<<endl;
		
		return std::numeric_limits< Real >::quiet_NaN();
	}
	
	return type == Tetration ? 0 : info.z.imag();
}

template< typename Real , typename Complex >
std::ostream & operator<<( std::ostream & o , const ortogonal< Real , Complex > & w ){
	
	if( w.type == ortogonal< Real , Complex >::Sing ){
		
		if( w.info.sing == -1 ) return o<<Complex( 0 )<<endl;

		o<<"singularity("<<w.info.sing<<")";
		
		return o;
	}
	
	if( w.type == ortogonal< Real , Complex >::Tetration ){
		
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
	if( z == T( 0 ) ) return ( k == 0 ) ? 0.l : -INFINITY;
	if( z == -exp( -T( 1 ) ) && ( k == 0 || k == -1 ) ) return -T( 1 );
	if( z == exp( T( 1 ) ) && k == 0 ) return T( 1 );
	
	//Halley method begins
	T w( InitPoint( z , k ) ) , wprev; // intermediate values in the Halley method
	const unsigned int maxiter = 30; // max number of iterations. This eliminates improbable infinite loops
	unsigned int iter = 0; // iteration counter
	
	do{
		
		wprev = w;
		w -= T( 2 ) * ( ( zexpz( w ) - z ) * zexpz_d( w ) ) / ( T( 2 ) * pow( zexpz_d( w ) , T( 2 ) ) - ( zexpz( w ) - z ) * zexpz_dd( w ) );
		iter++;
		
	} while( abs( w - wprev ) > std::numeric_limits< decltype( z.real() ) >::epsilon() && iter < maxiter );
	
	return w;
}
